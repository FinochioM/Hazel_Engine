#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

int main(int argc, char* args[])
{
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Inicializar SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Crear la ventana
    SDL_Window* window = SDL_CreateWindow("Renderizar Texto con SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (!window) {
        std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Crear el renderer de SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error al crear el renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Cargar la fuente
    TTF_Font* font = TTF_OpenFont("../Core/GUI/assets/fonts/Roboto_R.ttf", 24);
    if (!font) {
        std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Establecer el color del texto
    SDL_Color white = {255, 255, 255, 255};  // Blanco

    // Renderizar el texto en una superficie SDL
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Texto de Prueba", white);
    if (!textSurface) {
        std::cerr << "Error al renderizar el texto: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Convertir la superficie a una textura de SDL
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);  // Liberar la superficie, ya no es necesaria

    // Obtener el tamaño del texto para posicionarlo
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Ciclo principal
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fondo negro
        SDL_RenderClear(renderer);

        // Definir el rectángulo donde dibujar el texto
        SDL_Rect textRect = { 100, 100, textWidth, textHeight };

        // Dibujar el texto
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Presentar la ventana
        SDL_RenderPresent(renderer);
    }

    // Limpiar recursos
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
