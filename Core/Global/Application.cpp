#include "Application.h"
#include "Button.h"
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "ResourceManager.h"

float deltaTime = 0.0f;
bool isItRunning = false;

Application::Application() : textRenderer(nullptr), windowManager(nullptr), sceneManager(nullptr), isRunning(false) {}

Application::~Application() {
    Shutdown();
}

bool Application::Init()
{
    bool isRunning = isItRunning;

    windowManager = std::make_unique<WindowManager>();
    if (!windowManager->Init("Hazel Engine", 1280, 720)) {
        std::cerr << "Failed to initialize WindowManager." << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }

    auto font = ResourceManager::GetInstance().Load<Font>("GenericName","../Core/GUI/assets/fonts/Roboto_R.ttf", 24);
    if (!font){
        std::cerr << "Failed to load font" << std::endl;
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

    textRenderer = new TextRenderer(font);
    sceneManager = std::make_unique<SceneManager>();

    auto loader = std::make_shared<AnimationLoader>();
    loader->LoadAnimation("../Core/ComponentSystem/Animations/CsaFiles/player_animation.csa");

    Entity* entity = new Entity("Entity");
    auto texture = ResourceManager::GetInstance().Load<Texture>("player_texture", "../Core/GUI/assets/animations/player_animation.png");

    entity->AddComponent(std::make_unique<Transform>(entity));


    auto spriteRenderer = std::make_unique<SpriteRenderer>(entity, texture, TextureFilter::Point);
    entity->AddComponent(std::move(spriteRenderer));


    auto spriteRendererFromEntity = entity->GetComponent<SpriteRenderer>();

    entity->AddComponent(std::make_unique<Animator>(entity, spriteRendererFromEntity, loader.get()));
    auto animator = entity->GetComponent<Animator>();
    animator->PlayAnimation("idle");

    auto testScene = std::make_shared<Scene>("Test Scene");

    Button* buttonNode = new Button(glm::vec2(100.0, 100.0), glm::vec2(200.0,50.0), "Swap", textRenderer);

    testScene->AddChild(entity);
    testScene->AddChild(buttonNode);

    sceneManager->AddScene(testScene);
    sceneManager->SetCurrentScene("Test Scene");

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

            sceneManager->GetCurrentScene()->HandleEvents(event);

            auto entity = sceneManager->GetCurrentScene()->GetEntity("Entity");
            if (entity) {
                auto animator = static_cast<Animator *>(entity->GetComponent<Animator>());
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

        sceneManager->Update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sceneManager->Render();

        SDL_GL_SwapWindow(windowManager->GetWindow());
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

    if (windowManager) {
        windowManager->ShutDown();
    }

    TTF_Quit();
}