#pragma once
#include <SDL3/SDL.h>

class Zone {
public:
    Zone(float x, float y, float width, float height);
    ~Zone();

    void Update();
    void Render(SDL_Renderer* renderer);
    void HandleEvent(const SDL_Event* event);

private:
    float m_x, m_y;
    float m_width, m_height;
    SDL_Color m_color;
};