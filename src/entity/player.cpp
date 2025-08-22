#include "../entity/player.h"
#include "../scene/zone.h"
#include "../core/game.h"

Player::Player(float x, float y) 
    : m_x(x), m_y(y), m_speed(5.0f), m_size(30), m_sprite(nullptr),
      m_moveUp(false), m_moveDown(false), m_moveLeft(false), m_moveRight(false) {
    // m_speed use 'f' notation to use single precision value (32-bit), more resource-saving
    // Set player color to blue
    m_color = {0, 0, 255, 255};
}

Player::~Player() {
    // We don't own the sprite texture, so don't delete it
}

void Player::SetSprite(SDL_Texture* sprite) {
    m_sprite = sprite;
}

void Player::Update() {
    // Store old position for collision resolution
    float oldX = m_x;
    float oldY = m_y;

    // Update position based on movement flags
    if (m_moveUp) m_y -= m_speed;
    if (m_moveDown) m_y += m_speed;
    if (m_moveLeft) m_x -= m_speed;
    if (m_moveRight) m_x += m_speed;
    
    // Simple boundary checking to keep player on screen
    if (m_x < 0) m_x = 0;
    if (m_x > Game::VIRTUAL_WIDTH - m_size) m_x = Game::VIRTUAL_WIDTH - m_size;
    if (m_y < 0) m_y = 0;
    if (m_y > Game::VIRTUAL_HEIGHT - m_size) m_y = Game::VIRTUAL_HEIGHT - m_size;
}

void Player::CheckZoneCollision(Zone* zone) {
    if (!zone) return;
    
    // Get current bounds
    SDL_FRect playerBounds = GetBounds();
    
    // Check for collision
    if (zone->CheckCollision(playerBounds.x, playerBounds.y, 
                            playerBounds.w, playerBounds.h)) {
        // Handle collision by pushing player out of zone
        
        // Simple resolution: Check each edge and push out from closest one
        // Calculate overlap on all sides
        float leftOverlap = (zone->GetBounds().x + zone->GetBounds().w) - m_x;
        float rightOverlap = (m_x + m_size) - zone->GetBounds().x;
        float topOverlap = (zone->GetBounds().y + zone->GetBounds().h) - m_y;
        float bottomOverlap = (m_y + m_size) - zone->GetBounds().y;
        
        // Find minimum overlap
        float minOverlap = leftOverlap;
        int direction = 0; // 0=left, 1=right, 2=top, 3=bottom
        
        if (rightOverlap < minOverlap) {
            minOverlap = rightOverlap;
            direction = 1;
        }
        if (topOverlap < minOverlap) {
            minOverlap = topOverlap;
            direction = 2;
        }
        if (bottomOverlap < minOverlap) {
            minOverlap = bottomOverlap;
            direction = 3;
        }
        
        // Push player out based on minimum overlap
        switch (direction) {
            case 0: // Left
                m_x = zone->GetBounds().x + zone->GetBounds().w;
                break;
            case 1: // Right
                m_x = zone->GetBounds().x - m_size;
                break;
            case 2: // Top
                m_y = zone->GetBounds().y + zone->GetBounds().h;
                break;
            case 3: // Bottom
                m_y = zone->GetBounds().y - m_size;
                break;
        }
    }
}

void Player::Render(SDL_Renderer* renderer, float scale, int offset_x, int offset_y) {
    // Scale up variables first
    float scaled_x = offset_x + m_x * scale;
    float scaled_y = offset_y + m_y * scale;
    float scaled_size = m_size * scale;
    
    if (m_sprite) {
        // Draw player sprite
        SDL_FRect dest = {scaled_x, scaled_y, scaled_size, scaled_size};
        SDL_RenderTexture(renderer, m_sprite, NULL, &dest);
    } else {
        // Fallback: Draw player as a rectangle if no sprite
        SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
        SDL_FRect rect = {scaled_x, scaled_y, scaled_size, scaled_size};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Player::HandleEvent(const SDL_Event* event) {
    // Handle keyboard events
    // key pressed events
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.scancode) {
            case SDL_SCANCODE_UP:
                m_moveUp = true;
                break;
            case SDL_SCANCODE_DOWN:
                m_moveDown = true;
                break;
            case SDL_SCANCODE_LEFT:
                m_moveLeft = true;
                break;
            case SDL_SCANCODE_RIGHT:
                m_moveRight = true;
                break;
        }
    }
    // key released events
    else if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.scancode) {
            case SDL_SCANCODE_UP:
                m_moveUp = false;
                break;
            case SDL_SCANCODE_DOWN:
                m_moveDown = false;
                break;
            case SDL_SCANCODE_LEFT:
                m_moveLeft = false;
                break;
            case SDL_SCANCODE_RIGHT:
                m_moveRight = false;
                break;
        }
    }
}