#pragma once
#include <SDL3/SDL.h>
#include "../entity./player.h"
#include "../scene/zone.h"
#include "../util/asset_loader.h"

class Game {
public:
    Game();
    ~Game();
        
    static constexpr int VIRTUAL_WIDTH = 1280;
    static constexpr int VIRTUAL_HEIGHT = 720;

    bool Initialize();
    bool Update();
    bool HandleEvent(const SDL_Event* event);
    void Cleanup();
    
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    // entity
    Player* m_player;
    bool m_running;
    // scene
    Zone* m_zone;
    // util
    asset_loader m_assetLoader;
    // asset texture
    SDL_Texture* m_imgTexture;
    SDL_Texture* m_backgroundTexture;
};