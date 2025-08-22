#include "game.h"

Game::Game() : m_window(nullptr), m_renderer(nullptr), m_player(nullptr), 
               m_zone(nullptr), m_running(true), 
               m_imgTexture(nullptr), m_backgroundTexture(nullptr) {
    // m_running is boolean to check whether application is active or offline.
}

Game::~Game() {
    Cleanup();
}

bool Game::Initialize() {
    // Create window and renderer
    SDL_CreateWindowAndRenderer("Treasure Hunter", 1280, 720, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
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

    // Create zone
    m_zone = new Zone(200, 200, 200, 150);

    // Load SDL_image functionality
    // 1. player sprite
    if (!m_assetLoader.load_texture("asset/image/book.png", m_renderer)) {
        SDL_Log("Failed to load test image, but continuing...");
        // will resume even if failure
    } else {
        m_imgTexture = m_assetLoader.get_texture("asset/image/book.png");
        SDL_Log("Image loaded successfully!");

        // Set the book sprite for the player
        m_player->SetSprite(m_imgTexture);
    }

    // 2. background asset
    if (!m_assetLoader.load_texture("asset/image/forest.png", m_renderer)) {
        SDL_Log("Failed to load background image, but continuing...");
    } else {
        m_backgroundTexture = m_assetLoader.get_texture("asset/image/forest.png");
        SDL_Log("Background image loaded successfully!");
    }
    
    return true;
}

bool Game::Update() {
    if (!m_running) return false;
    
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Get window size for fullscreen background
    int width, height;
    SDL_GetWindowSize(m_window, &width, &height);

    // Scale factor
    float scale = std::min(
        width / static_cast<float>(VIRTUAL_WIDTH),
        height / static_cast<float>(VIRTUAL_HEIGHT)
    );

    // Determine actual game size without window
    int render_width = static_cast<int>(VIRTUAL_WIDTH * scale);
    int render_height = static_cast<int>(VIRTUAL_HEIGHT * scale);

    // Shifts game to center of screen
    int offset_x = (width - render_width) / 2;
    int offset_y = (height - render_height) / 2;

    // Draw background image
    if (m_backgroundTexture) {
        SDL_FRect dest = {(float)offset_x, (float)offset_y, (float)render_width, (float)render_height};
        SDL_RenderTexture(m_renderer, m_backgroundTexture, NULL, &dest);
    }

    if (m_zone) {
        // Check for collisions with zone
        m_player->CheckZoneCollision(m_zone);
        
        // Update and render zone first (so it appears behind player)
        m_zone->Update();
        m_zone->Render(m_renderer, scale, offset_x, offset_y);
    }

    // Update and render player
    m_player->Update();
    m_player->Render(m_renderer, scale, offset_x, offset_y);

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

    // Let zone handle events
    if (m_zone) {
        m_zone->HandleEvent(event);
    }
    
    return true;
}

void Game::Cleanup() {
    if (m_zone) {
        delete m_zone;
        m_zone = nullptr;
    }

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