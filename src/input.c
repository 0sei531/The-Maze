#include "../headers/header.h"

/**
 * handleInput - process input from the keyboard
*/
void handleInput(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                GameRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        GameRunning = false;
                        break;
                    case SDLK_UP:
                        player.walkDirection = +1;
                        break;
                    case SDLK_DOWN:
                        player.walkDirection = -1;
                        break;
                    case SDLK_RIGHT:
                        player.turnDirection = +1;
                        break;
                    case SDLK_LEFT:
                        player.turnDirection = -1;
                        break;
                    case SDLK_w:
                        player.walkDirection = +1;
                        break;
                    case SDLK_s:
                        player.walkDirection = -1;
                        break;
                    case SDLK_a:
                        player.turnDirection = -1;
                        break;
                    case SDLK_d:
                        player.turnDirection = +1;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                        player.walkDirection = 0;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                        player.turnDirection = 0;
                        break;
                    case SDLK_w:
                    case SDLK_s:
                        player.walkDirection = 0;
                        break;
                    case SDLK_a:
                    case SDLK_d:
                        player.turnDirection = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}
