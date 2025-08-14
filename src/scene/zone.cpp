#include "zone.h"

Zone::Zone(float x, float y, float width, float height)
    : m_x(x), m_y(y), m_width(width), m_height(height)
{
    // Default color - green semi-transparent
    m_color = {0, 255, 0, 128};
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

void Zone::Render(SDL_Renderer* renderer)
{
    // Save current renderer state
    SDL_Color previousColor;
    SDL_GetRenderDrawColor(renderer, &previousColor.r, &previousColor.g, 
                          &previousColor.b, &previousColor.a);
    
    // Set zone color
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    
    // Draw zone as a rectangle
    SDL_FRect rect = {m_x, m_y, m_width, m_height};
    SDL_RenderFillRect(renderer, &rect);
    
    // Restore previous renderer state
    SDL_SetRenderDrawColor(renderer, previousColor.r, previousColor.g, 
                          previousColor.b, previousColor.a);
}

void Zone::HandleEvent(const SDL_Event* event)
{
    // Process events related to the zone
    // For example, mouse clicks or hover effects
}