#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

class asset_loader {
public:
    asset_loader();
    ~asset_loader();

    bool load_texture(const std::string& file_path, SDL_Renderer* renderer);
    void unload_texture(const std::string& file_path);
    void clear();

private:
    std::unordered_map<std::string, SDL_Texture*> m_textures;
};