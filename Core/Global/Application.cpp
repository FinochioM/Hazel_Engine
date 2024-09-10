#include "Application.h"
#include "Button.h"
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"
#include "Renderer.h"
#include "BoxCollider.h"

float deltaTime = 0.0f;

Application::Application() : textRenderer(nullptr), window(nullptr) {}

Application::~Application() {
    Shutdown();
}

bool Application::Init()
{
    if (!InitSDL() || !InitOpenGL() || !InitTTF()) {
        return false;
    }

    if (!fontManager.LoadFont("../Core/GUI/assets/fonts/Inconsolata_L.ttf", 23)) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return false;
    }

    textRenderer = new TextRenderer(&fontManager);

    Entity* entity = new Entity("Entity");
    Transform* transform = new Transform(entity);
    Renderer* renderer = new Renderer(entity);
    BoxCollider* collider = new BoxCollider(entity, glm::vec2(50.0, 50.0));

    transform->position = glm::vec3(200.0);

    entity->AddComponent(transform);
    entity->AddComponent(renderer);
    entity->AddComponent(collider);

    Scene* testScene = new Scene("TestScene");

    Button* buttonNode = new Button(glm::vec2(100.0, 100.0), glm::vec2(200.0,50.0), "Test", textRenderer);

    buttonNode->RegisterEvent(WidgetEventType::LeftClick, [] (){
        std::cout << "Boton clickeado en la escena :" << std::endl;
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