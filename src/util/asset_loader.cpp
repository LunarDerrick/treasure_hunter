#include "asset_loader.h"
#include <SDL3_image/SDL_image.h> // Requires SDL_image library

asset_loader::asset_loader()
{
    // Initialize the texture map
}

asset_loader::~asset_loader()
{
    // Clean up all textures
    clear();
}

bool asset_loader::load_texture(const std::string& file_path, SDL_Renderer* renderer)
{
    // Check if texture is already loaded
    if (m_textures.find(file_path) != m_textures.end()) {
        return true; // Already loaded
    }
    
    // Load the image from file
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    if (!surface) {
        SDL_Log("Failed to load image %s: %s", file_path.c_str(), SDL_GetError());
        return false;
    }
    
    // Create texture from surface using the provided renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    
    if (!texture) {
        SDL_Log("Failed to create texture from %s: %s", file_path.c_str(), SDL_GetError());
        return false;
    }
    
    // Store in our map
    m_textures[file_path] = texture;
    return true;
}

void asset_loader::unload_texture(const std::string& file_path)
{
    auto it = m_textures.find(file_path);
    if (it != m_textures.end()) {
        SDL_DestroyTexture(it->second);
        m_textures.erase(it);
    }
}

void asset_loader::clear()
{
    // Destroy all textures
    for (auto& pair : m_textures) {
        SDL_DestroyTexture(pair.second);
    }
    m_textures.clear();
}