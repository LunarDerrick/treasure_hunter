#define SDL_MAIN_USE_CALLBACKS 1 // replace main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

typedef struct {
    SDL_Window*     window;
    SDL_Renderer*   renderer;
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
    
    // Create window and renderer
    if (!SDL_CreateWindowAndRenderer("Treasure Hunter", 800, 600, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
        SDL_Log("Window or renderer creation failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    return SDL_APP_CONTINUE;
}

// Main loop - called every frame
SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* state = (AppState*)appstate;
    
    // Clear screen
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state->renderer);
    
    // Draw a simple rectangle
    SDL_FRect rect = {100.0f, 100.0f, 200.0f, 150.0f};
    SDL_SetRenderDrawColor(state->renderer, 235, 168, 52, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(state->renderer, &rect);

    SDL_RenderPresent(state->renderer);
    
    // Frame rate control
    SDL_Delay(16); // ~60 FPS
    
    return SDL_APP_CONTINUE;
}

// Handle events
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN: // press ESC key to close
            if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
                return SDL_APP_SUCCESS;
            }
            break;
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

// Clean up; ensure no memory leaks
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    if (appstate) {
        AppState* state = (AppState*)appstate;
        if (state->renderer) {
            SDL_DestroyRenderer(state->renderer);
        }
        if (state->window) {
            SDL_DestroyWindow(state->window);
        }
        SDL_free(state);
    }
    SDL_Quit();
    SDL_Log("SDL quit successfully!");
}