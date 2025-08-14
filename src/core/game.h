#pragma once
#include <SDL3/SDL.h>
#include "../entity./player.h"

class Game {
public:
    Game();
    ~Game();
    
    bool Initialize();
    bool Update();
    bool HandleEvent(const SDL_Event* event);
    void Cleanup();
    
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    Player* m_player;
    bool m_running;
};