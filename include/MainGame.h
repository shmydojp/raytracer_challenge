#ifndef _MAIN_GAME_H
#define _MAIN_GAME_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "projectile.h"
#include "canvas.h"
#include "color.h"

namespace Mido{
    enum class GameState {PLAY, QUIT};

    namespace constants{
        constexpr int DEFAULT_WIDTH             = 1280;
        constexpr int DEFAULT_HEIGHT            = 720;
    }

    class MainGame
    {
    public:
        MainGame();

        ~MainGame();

        void run();

        void gameLoop();

        void processInput();

        void update();

    private:
        void initSystems();

        GameState       m_gameState;
        SDL_Renderer   *m_renderer;
        SDL_Window     *m_window;
        int             m_height;
        int             m_width;

        Entity::Environemt m_env;
        Entity::Projectile m_proj;
        Canvas             m_canvas;
    };
}

#endif
