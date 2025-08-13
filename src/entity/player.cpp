// #include "player.h"

// Player::Player(float x, float y) 
//     : m_x(x), m_y(y), m_speed(5.0f), m_size(30), 
//       m_moveUp(false), m_moveDown(false), m_moveLeft(false), m_moveRight(false) {
//     // Set player color to blue
//     m_color = {0, 0, 255, 255};
// }

// Player::~Player() {
//     // Nothing to clean up
// }

// void Player::Update() {
//     // Update position based on movement flags
//     if (m_moveUp) m_y -= m_speed;
//     if (m_moveDown) m_y += m_speed;
//     if (m_moveLeft) m_x -= m_speed;
//     if (m_moveRight) m_x += m_speed;
    
//     // Simple boundary checking to keep player on screen
//     if (m_x < 0) m_x = 0;
//     if (m_x > 800 - m_size) m_x = 800 - m_size;
//     if (m_y < 0) m_y = 0;
//     if (m_y > 600 - m_size) m_y = 600 - m_size;
// }

// void Player::Render(SDL_Renderer* renderer) {
//     // Set draw color to player color
//     SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    
//     // Draw player as a rectangle
//     SDL_FRect rect = {m_x, m_y, (float)m_size, (float)m_size};
//     SDL_RenderFillRect(renderer, &rect);
// }

// void Player::HandleEvent(const SDL_Event* event) {
//     // Handle keyboard events
//     if (event->type == SDL_EVENT_KEY_DOWN) {
//         switch (event->key.keysym.sym) {
//             case SDLK_UP:
//                 m_moveUp = true;
//                 break;
//             case SDLK_DOWN:
//                 m_moveDown = true;
//                 break;
//             case SDLK_LEFT:
//                 m_moveLeft = true;
//                 break;
//             case SDLK_RIGHT:
//                 m_moveRight = true;
//                 break;
//         }
//     }
//     else if (event->type == SDL_EVENT_KEY_UP) {
//         switch (event->key.keysym.sym) {
//             case SDLK_UP:
//                 m_moveUp = false;
//                 break;
//             case SDLK_DOWN:
//                 m_moveDown = false;
//                 break;
//             case SDLK_LEFT:
//                 m_moveLeft = false;
//                 break;
//             case SDLK_RIGHT:
//                 m_moveRight = false;
//                 break;
//         }
//     }
// }