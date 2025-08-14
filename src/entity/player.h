#pragma once
#include <SDL3/SDL.h>

class Player {
public:
    Player(float x, float y);
    ~Player();
    
    void Update();
    void Render(SDL_Renderer* renderer);
    void HandleEvent(const SDL_Event* event);
    
private:
    float m_x, m_y;
    float m_speed;
    int m_size;
    SDL_Color m_color;
    
    // Movement direction flags
    bool m_moveUp;
    bool m_moveDown;
    bool m_moveLeft;
    bool m_moveRight;
};