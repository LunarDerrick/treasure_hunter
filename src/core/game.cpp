#include "game.h"

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_player(nullptr), m_running(true) {
    // m_running is boolean to check whether application is active or offline.
}

Game::~Game() {
    Cleanup();
}

bool Game::Initialize() {
    // Create window and renderer
    SDL_CreateWindowAndRenderer("Treasure Hunter", 800, 600, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
    if (!m_window || !m_renderer) {
        SDL_Log("Window or renderer creation failed: %s", SDL_GetError());
        return false;
    }
    /**
     * m_variable is a naming convention to state it's instanced variable and NOT global variable.
     * m implies "member".
     */
    
    // Create player
    m_player = new Player(400, 300);
    
    return true;
}

bool Game::Update() {
    if (!m_running) return false;
    
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    
    // Update and render player
    m_player->Update();
    m_player->Render(m_renderer);
    
    // Present rendered frame
    SDL_RenderPresent(m_renderer);

    // Frame rate control
    SDL_Delay(16); // ~60 FPS
    
    return true;
}

bool Game::HandleEvent(const SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            m_running = false;
            return false;
        case SDL_EVENT_KEY_DOWN: // press ESC key to close
            if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
                m_running = false;
                return false;
            }
            break;
        default:
            break;
    }
    
    // Let player handle events
    m_player->HandleEvent(event);
    
    return true;
}

void Game::Cleanup() {
    if (m_player) {
        delete m_player;
        m_player = nullptr;
    }
    
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}