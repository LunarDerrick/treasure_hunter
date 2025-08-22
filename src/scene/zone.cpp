#include "zone.h"

Zone::Zone(float x, float y, float width, float height)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_solid(true)
{
    // Default color - green semi-transparent
    m_color = {24, 94, 23, 128};
}

Zone::~Zone()
{
    // No resources to clean up
}

void Zone::Update()
{
    // Update zone logic here if needed
    // For example, animations, state changes, etc.
}

void Zone::Render(SDL_Renderer* renderer, float scale, int offset_x, int offset_y)
{
    // Scale up variables first
    float scaled_x = offset_x + m_x * scale;
    float scaled_y = offset_y + m_y * scale;
    float scaled_width = m_width * scale;
    float scaled_height = m_height * scale;

    // Save current renderer state
    SDL_Color previousColor;
    SDL_GetRenderDrawColor(renderer, &previousColor.r, &previousColor.g, 
                          &previousColor.b, &previousColor.a);
    
    // Set zone color
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    
    // Draw zone as a rectangle
    SDL_FRect rect = {scaled_x, scaled_y, scaled_width, scaled_height};
    SDL_RenderFillRect(renderer, &rect);
    
    // Restore previous renderer state
    SDL_SetRenderDrawColor(renderer, previousColor.r, previousColor.g, 
                          previousColor.b, previousColor.a);
}

bool Zone::CheckCollision(float x, float y, float width, float height) const {
    // Check if rectangles overlap
    return (m_x < x + width &&
            m_x + m_width > x &&
            m_y < y + height &&
            m_y + m_height > y);
}

bool Zone::IsPointInside(float x, float y) const {
    return (x >= m_x && x <= m_x + m_width &&
            y >= m_y && y <= m_y + m_height);
}

void Zone::HandleEvent(const SDL_Event* event)
{
    // Process events related to the zone
    // For example, mouse clicks or hover effects
}