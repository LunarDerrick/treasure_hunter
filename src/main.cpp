#define SDL_MAIN_USE_CALLBACKS 1 // replace main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core/game.h"

typedef struct {
    Game* game;
} AppState;

// Initialize the application
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    AppState* state = (AppState*)SDL_calloc(1, sizeof(AppState));
    if (!state) {
        SDL_Log("Failed to allocate app state");
        return SDL_APP_FAILURE;
    }
    *appstate = state;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    SDL_Log("SDL initialized successfully!");
    
    // Create and initialize game
    state->game = new Game();
    if (!state->game->Initialize()) {
        SDL_Log("Game initialization failed");
        return SDL_APP_FAILURE;
    }
    
    return SDL_APP_CONTINUE;
}

// Main loop - called every frame
SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* state = (AppState*)appstate;
    return state->game->Update() ? SDL_APP_CONTINUE : SDL_APP_SUCCESS;
}

// Handle events
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    
    AppState* state = (AppState*)appstate;
    
    // Forward ALL events to Game class and let it decide what to do
    if (!state->game->HandleEvent(event)) {
        return SDL_APP_SUCCESS; // Game signaled quit
    }

    return SDL_APP_CONTINUE;
}

// Clean up; ensure no memory leaks
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    if (appstate) {
        AppState* state = (AppState*)appstate;
        if (state->game) {
            state->game->Cleanup();
            delete state->game;
        }
        SDL_free(state);
    }
    SDL_Quit();
}