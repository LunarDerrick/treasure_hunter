#pragma once
#include <SDL3/SDL.h>
class Zone;

class Player {
public:
    Player(float x, float y);
    ~Player();
    
    void Update();
    void Render(SDL_Renderer* renderer, float scale, int offset_x, int offset_y);
    void HandleEvent(const SDL_Event* event);
    void SetSprite(SDL_Texture* sprite);

    // Add collision handling
    void CheckZoneCollision(Zone* zone);
    // Add getter for bounds
    SDL_FRect GetBounds() const { return {m_x, m_y, (float)m_size, (float)m_size}; }
    
private:
    float m_x, m_y;
    float m_speed;
    int m_size;
    SDL_Color m_color;
    SDL_Texture* m_sprite;
    
    // Movement direction flags
    bool m_moveUp;
    bool m_moveDown;
    bool m_moveLeft;
    bool m_moveRight;
};