#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "entity.h"

typedef struct{
    char** maps;                // Arr of level maps
    int* maps_size_x; 
    int* maps_size_y; 
    int maps_len;               // Size of arr of maps len
    int current_level;

    Entity*** entities;
    int* entities_len;

    SDL_Texture** textures;     // Textures
    int textures_len;           // Size arr of textures
    TTF_Font** fonts;           // Fonts
    int fonts_len;              // Size arr of fonts

    int score;                  // Player score
    int coop_score;             // Coplayer score
    int lives;                  // Player lives
    int charge_time;            // Charge is active 0,1
    int charge_start_time;      // start of charge 
    int charge_count;           // Remaning charges
    int game_running;
    int game_win;

    int coop;
    int* coop_pl_index;
    int* pl_index;

    // Pheromone fields per level (2D stored as 1D arrays)
    float** pheromone_player;   // attraction to Pacman (deposited by Pacman)
    float pheromone_evap_ms;    // evaporation interval in ms
    Uint32* pheromone_last_update_ms; // per-level last evaporation timestamp

    // AI feature toggles
    int ai_enable_vision;       // 1 to use line-of-sight chasing
    int ai_enable_memory;       // 1 to use short-term memory bias
    int ai_enable_pheromones;   // 1 to use pheromone gradient
    int ai_enable_ghost_vision; // 1 to avoid other ghosts on LOS
} Levels;

Levels* levels_new( const int maps_len, const int textures_len, const int fonts_len);
void levels_free(Levels** level);

#endif