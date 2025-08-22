#pragma once
#include <SDL3/SDL.h>

class Zone {
public:
    Zone(float x, float y, float width, float height);
    ~Zone();

    void Update();
    void Render(SDL_Renderer* renderer, float scale, int offset_x, int offset_y);
    void HandleEvent(const SDL_Event* event);

    // Add collision detection
    bool CheckCollision(float x, float y, float width, float height) const;
    bool IsPointInside(float x, float y) const;

    // Add getters
    SDL_FRect GetBounds() const { return {m_x, m_y, m_width, m_height}; }

private:
    float m_x, m_y;
    float m_width, m_height;
    SDL_Color m_color;
    bool m_solid;
};