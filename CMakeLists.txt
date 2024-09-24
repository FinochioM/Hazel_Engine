cmake_minimum_required(VERSION 3.28)
project(HazelEngine)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE "C:/libs_programming/SDL2/include")
set(SDL2_LIB "C:/libs_programming/SDL2/lib/x64")
set(Glew_INCLUDE "C:/libs_programming/Glew/include/GL")
set(Glew_LIB "C:/libs_programming/Glew/lib/Release/x64")
set(GLM_INCLUDE "C:/libs_programming")
set(TTF_INCLUDE "C:/libs_programming/sdl_ttf/include")
set(TTF_LIB "C:/libs_programming/sdl_ttf/lib/x64")
set(SDL_IMAGE_LIB "C:/libs_programming/sdl_image/lib/x64")
set(SDL_IMAGE_INCLUDE "C:/libs_programming/sdl_image/include")

include_directories(${SDL2_INCLUDE})
include_directories(${Glew_INCLUDE})
include_directories(${GLM_INCLUDE})
include_directories(${TTF_INCLUDE})
include_directories(${SDL_IMAGE_INCLUDE})

include_directories(${CMAKE_SOURCE_DIR}/Core/ComponentSystem)
include_directories(${CMAKE_SOURCE_DIR}/Core/ComponentSystem/Viewport)
include_directories(${CMAKE_SOURCE_DIR}/Core/ComponentSystem/Components)
include_directories(${CMAKE_SOURCE_DIR}/Core/ComponentSystem/Animations)
include_directories(${CMAKE_SOURCE_DIR}/Core/Managers)
include_directories(${CMAKE_SOURCE_DIR}/Core/Shaders/Classes)
include_directories(${CMAKE_SOURCE_DIR}/Core/GUI/Layout)
include_directories(${CMAKE_SOURCE_DIR}/Core/GUI/Renderer)
include_directories(${CMAKE_SOURCE_DIR}/Core/GUI/Widgets)
include_directories(${CMAKE_SOURCE_DIR}/Core/GUI/Widgets/Handlers)
include_directories(${CMAKE_SOURCE_DIR}/Core/GUI/lib)
include_directories(${CMAKE_SOURCE_DIR}/Core)
include_directories(${CMAKE_SOURCE_DIR}/Core/Global)
include_directories(${CMAKE_SOURCE_DIR}/Core/Interfaces)
include_directories(${CMAKE_SOURCE_DIR}/Core/Scene)

link_directories(${SDL2_LIB})
link_directories(${Glew_LIB})
link_directories(${TTF_LIB})
link_directories(${SDL_IMAGE_LIB})

add_executable(HazelEngine main.cpp
        Core/ComponentSystem/Entity.cpp
        Core/Shaders/Classes/Shader.cpp
        Core/Managers/FontManager.cpp
        Core/GUI/lib/TextRenderer.cpp
        Core/Global/Global.cpp
        Core/Global/Application.cpp
        Core/GUI/Widgets/Handlers/WidgetManager.cpp
        Core/GUI/Widgets/Widget.cpp
        Core/GUI/Widgets/Button.cpp
        Core/Scene/Node.cpp
        Core/Scene/Scene.cpp
        Core/Scene/SceneManager.cpp
        Core/ComponentSystem/Component.cpp
        Core/ComponentSystem/Components/Transform.cpp
        Core/ComponentSystem/Components/Renderer.cpp
        Core/ComponentSystem/Components/BoxCollider.cpp
        Core/ComponentSystem/Components/SpriteRenderer.cpp
        Core/ComponentSystem/Animations/AnimationLoader.cpp
        Core/ComponentSystem/Animations/Animator.cpp
        Core/GUI/lib/yyjson.c
)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_ttf SDL2_image)
target_link_libraries(${PROJECT_NAME} glew32s glew32 opengl32 glu32)