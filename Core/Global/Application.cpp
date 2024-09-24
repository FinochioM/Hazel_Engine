#include "Application.h"
#include "Button.h"
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Animator.h"

float deltaTime = 0.0f;
bool isItRunning = false;

Application::Application() : textRenderer(nullptr), window(nullptr) {}

Application::~Application() {
    Shutdown();
}

bool Application::Init()
{
    bool isRunning = isItRunning;

    if (!InitSDL() || !InitOpenGL() || !InitTTF()) {
        return false;
    }

    if (!fontManager.LoadFont("../Core/GUI/assets/fonts/Inconsolata_L.ttf", 23)) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return false;
    }

    AnimationTransition idleToRun;
    idleToRun.from = "idle";
    idleToRun.to = "run";
    idleToRun.transitionDuration = 0.05f;
    idleToRun.condition = [](){
        return isItRunning;
    };

    AnimationTransition runToIdle;
    runToIdle.from = "run";
    runToIdle.to = "idle";
    runToIdle.transitionDuration = 0.05f;
    runToIdle.condition = [](){
        return !isItRunning;
    };

    textRenderer = new TextRenderer(&fontManager);
    AnimationLoader* loader = new AnimationLoader();
    loader->LoadAnimation("../Core/ComponentSystem/Animations/CsaFiles/player_animation.csa");

    Entity* entity = new Entity("Entity");
    Transform* transform = new Transform(entity);
    SpriteRenderer* renderer = new SpriteRenderer(entity, "../Core/GUI/assets/animations/player_animation.png", TextureFilter::Point);
    BoxCollider* collider = new BoxCollider(entity, glm::vec2(100.0, 100.0));
    Animator* animator = new Animator(entity, renderer, loader);

    animator->PlayAnimation("idle");
    animator->AddTransition(idleToRun);
    animator->AddTransition(runToIdle);
    animator->SetManualControl(true);

    transform->position = glm::vec3(200.0);
    transform->scale = glm::vec3(2.0);

    entity->AddComponent(animator);
    entity->AddComponent(transform);
    entity->AddComponent(renderer);
    entity->AddComponent(collider);

    Scene* testScene = new Scene("TestScene");

    Button* buttonNode = new Button(glm::vec2(100.0, 100.0), glm::vec2(200.0,50.0), "Swap", textRenderer);

    buttonNode->RegisterEvent(WidgetEventType::LeftClick, [&isRunning] (){
        isRunning = false;
    });

    buttonNode->RegisterEvent(WidgetEventType::RightClick, [&isRunning] (){
        isRunning = true;
    });


    testScene->AddChild(entity);
    testScene->AddChild(buttonNode);


    sceneManager.AddScene(testScene);
    sceneManager.SetCurrentScene("TestScene");


    return true;
}

bool Application::InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Hazel Engine",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1280, 720, SDL_WINDOW_OPENGL);

    if (!window) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Error al crear el contexto OpenGL: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

bool Application::InitOpenGL() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW: " << glewGetErrorString(err) << std::endl;
        return false;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1280, 720, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (SDL_GL_MakeCurrent(window, glContext) != 0) {
        std::cerr << "Error al activar el contexto OpenGL: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Application::InitTTF() {
    if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void Application::GameLoop() {
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            sceneManager.GetCurrentScene()->HandleEvents(event);

            auto entity = sceneManager.GetCurrentScene()->GetEntity("Entity");
            if (entity) {
                auto animator = static_cast<Animator *>(entity->GetComponent("Animator"));
                if (animator) {
                    if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_n) {
                            std::cout << "Next Frame" << std::endl;
                            animator->SetManualControl(true);
                            animator->NextFrame();
                        } else if (event.key.keysym.sym == SDLK_p) {
                            std::cout << "Previous Frame" << std::endl;
                            animator->SetManualControl(true);
                            animator->PreviousFrame();
                        }
                    }
                }
            }
        }

        sceneManager.Update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sceneManager.Render();

        SDL_GL_SwapWindow(window);
    }
}

void Application::Run() {
    GameLoop();
}

void Application::Shutdown() {
    if (textRenderer) {
        delete textRenderer;
        textRenderer = nullptr;
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}