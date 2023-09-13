#include "MainGame.h"

using namespace Mido;

static void sdl_failure(const std::string& error){
    std::cerr << error << "\n" << SDL_GetError();
    SDL_Quit();
    std::exit(-1);
}

MainGame::MainGame()
    : m_renderer{nullptr},
      m_window{nullptr},
      m_height{constants::DEFAULT_HEIGHT},
      m_width{constants::DEFAULT_WIDTH},
      m_env{},
      m_proj{},
      m_canvas{m_width, m_height}
{
}

void MainGame::run(){
    initSystems();
    gameLoop();
}

void MainGame::initSystems(){
    // initalize SDL
    if( SDL_Init(SDL_INIT_EVERYTHING) < 0){
        sdl_failure("SDL could not initialize! SDL_Error:");
    }

    m_window = SDL_CreateWindow("MidoTracer (WIP!)",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_width, m_height,
                                SDL_WINDOW_SHOWN);

    if( m_window == NULL ){
        sdl_failure("SDL could not create a window! SDL_Error:");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if( m_renderer == NULL ){
        sdl_failure("SDL could not create a Render! SDL_Error:");
    }

    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderPresent(m_renderer);
    SDL_RenderClear(m_renderer);

    m_gameState = GameState::PLAY;
    m_proj = Entity::Projectile(
                          create_point(35, 1, 0),
                          tuple_normalize(create_vector(1.0, 1.8, 0.0))*17);
    m_env  = Entity::Environemt(create_vector(0, -0.1, 0),
                                create_vector(-0.01, 0, 0));
}

// ((m_canvas.getHeight() - m_proj.position.y) <= (m_canvas.getHeight() - 1))

void MainGame::update(){
    if(m_proj.position.get_y() >= 0.0){
        if(m_proj.position.get_x() <= 0.0 ||
           m_proj.position.get_x() >= m_canvas.getWidth() - 1)
        {
            m_proj.velocity.set_x() = -m_proj.velocity.get_x();
        }

        if(m_proj.position.set_y() >= m_canvas.getHeight() - 1){
            m_proj.velocity.set_y() = -m_proj.velocity.get_y();
        }

        Entity::proj_update(m_env, m_proj);
        int x = static_cast<int>(
            std::clamp(m_proj.position.get_x(),
                       0.0f,
                       static_cast<float>(m_canvas.getWidth() - 1))
            );
        int y = static_cast<int>(
            std::clamp(m_canvas.getHeight() - m_proj.position.get_y(),
                       0.0f,
                       (float)m_canvas.getHeight() - 1.0f)
            );
        m_canvas(x,y) = Color(0.2, 0.3, 0.5);
    }

}

void MainGame::gameLoop(){
    while(m_gameState != GameState::QUIT){
        // input
        processInput();

        // update
        update();

        // render
        SDL_RenderDrawPoint(m_renderer, 400, 300);
        SDL_RenderClear(m_renderer);
    }
    m_canvas.to_ppm();
}

void MainGame::processInput(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                m_gameState = GameState::QUIT;
                break;
        }
    }
}

MainGame::~MainGame(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
