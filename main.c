/**
 * Docs: http://wiki.libsdl.org/FrontPage
 * Tutorial: http://lazyfoo.net/tutorials/SDL/index.php
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>

#include "src/lib/sdl_playground.h"
#include "src/lib/draw.h"
#include "src/lib/entity.h"
#include "src/lib/level.h"
#include "src/lib/api.h"
#include "src/lib/ai.h"
#include "src/lib/game.h"


int main(int argc, char** argv) {
    int debug = 0, counter = 0, last_score = 0, last_coop_score = 0, last_lives = 0, last_win = 0, last_charge = 0, game_started = 0;

    //Settings    
    int win_width = 810, win_height = 505; double win_scale = 1.6;
    int scale = 60, move_speed = 4, fps = 0; //, move_scale = scale/move_speed
    int animation_count = 0, animation_freq = scale/6/2;
    int levels_count = 4, coop = 0;

    //Args
    for(int a=1;a<argc;a++){
        if(strcmp(argv[a], "-h") == 0 || strcmp(argv[a], "--help") == 0){
            printf("Usage: pacman [options] [coop] [move_speed] [levels_count] [debug]\n\n");
            printf("Options (flags):\n");
            printf("  -h, --help            Show this help and exit\n");
            printf("  --vision=0|1         Enable/disable ghost line-of-sight to player (default 1)\n");
            printf("  --gvision=0|1        Enable/disable ghost-vs-ghost avoidance (default 1, gated near spawn)\n");
            printf("  --pher=0|1           Enable/disable pheromone gradient (default 1)\n");
            printf("  -vision=0|1, -gvision=0|1, -pher=0|1 are also accepted\n\n");
            printf("Positional (legacy, optional numeric):\n");
            printf("  coop                 0 single player (default), 1 coop\n");
            printf("  move_speed           Movement speed (default 4)\n");
            printf("  levels_count         Number of levels to load (default 4)\n");
            printf("  debug                0 normal (default), 1 verbose\n\n");
            printf("In-game controls:\n");
            printf("  SPACE start/pause, R restart, ESC pause\n");
            printf("  Arrows move P1; WASD move P2 (coop)\n");
            printf("  +/- change window scale, L next level (debug)\n");
            return 0;
        }
    }
    get_args( argc, argv, &coop, &move_speed, &levels_count, &debug);
    
    SDL_Window * win = NULL;
    SDL_Renderer * ren = NULL;
    SDL_Texture* score_texture = NULL; SDL_Texture* win_texture = NULL; SDL_Texture* continue_texture = NULL;

    bool initialized = sdl_playground_init( &win, &ren, win_width, win_height);

    if ( !initialized ){
        sdl_playground_destroy( win, ren );
        return -1;
    }
    
    // Load Level
    Levels* my_levels = NULL;
    load_levels(&my_levels, levels_count, coop, debug);
    // Parse optional AI feature toggles
    for(int a=1;a<argc;a++){
        int v;
        if((v = parse_flag(argv[a], "--vision")) != -1 || (v = parse_flag(argv[a], "-vision")) != -1){ my_levels->ai_enable_vision = v ? 1 : 0; }
        else if((v = parse_flag(argv[a], "--pher")) != -1 || (v = parse_flag(argv[a], "-pher")) != -1){ my_levels->ai_enable_pheromones = v ? 1 : 0; }
        else if((v = parse_flag(argv[a], "--gvision")) != -1 || (v = parse_flag(argv[a], "-gvision")) != -1){ my_levels->ai_enable_ghost_vision = v ? 1 : 0; }
    }
    // Memory follows vision automatically
    my_levels->ai_enable_memory = my_levels->ai_enable_vision;
    printf("Level Loaded\n");

    // Find Player Location in Level
    find_player(&my_levels);
    if(my_levels->coop == 1)
        printf("Coop is enabled\n");

    if(debug == 1){
        for (int i = 0; i < my_levels->maps_len; i++){
            printf("P1: %i\tP2: %i\n", my_levels->pl_index[i], my_levels->coop_pl_index[i]);
        }
    }
    

    // Setting window size
    change_window_size(win, &my_levels, &win_width, &win_height, win_scale);

    // Texture load
    load_texture(&ren, &my_levels, debug);
    printf("Textures Loaded\n");  

    SDL_Event e;
    bool quit = false;
    SDL_PixelFormat * fmt;
    Uint32 format = SDL_GetWindowPixelFormat(win);
    fmt = SDL_AllocFormat(format);

    printf("Starting game ...\n\n");
    while ( !quit ) {
        int tick_start_time = SDL_GetTicks();
        float render_start_time = SDL_GetPerformanceCounter();
        while ( SDL_PollEvent( &e ) ) {
            if ( e.type == SDL_QUIT ) {
                quit = true;
            }
            else if ( e.type == SDL_KEYDOWN ) { // key pressed down
                if ( e.key.keysym.sym == SDLK_r ) {
                    game_restart( win, &ren, &my_levels, &(my_levels->pl_index[my_levels->current_level]), &win_width, &win_height, win_scale,levels_count, coop, debug);
                    game_started = 0;
                }else if(e.key.keysym.sym == SDLK_SPACE){
                    if (my_levels->game_win == 0){                   
                        my_levels->game_running = 1;
                        game_started = 1;
                    }
                }else if(e.key.keysym.sym == SDLK_ESCAPE){
                    my_levels->game_running = 0;
                }else if(e.key.keysym.sym == SDLK_l){
                    change_level( win,&my_levels, &win_width, &win_height, win_scale);
                }else if(e.key.keysym.sym == SDLK_EQUALS){
                    win_scale += 0.2;
                    change_window_size(win, &my_levels, &win_width, &win_height, win_scale);
                }else if(e.key.keysym.sym == SDLK_MINUS){
                    win_scale -= 0.2; 
                    change_window_size(win, &my_levels, &win_width, &win_height, win_scale);
                }

                if( e.key.keysym.sym == SDLK_LEFT ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index[my_levels->current_level]]->direction_wanted = 0;
                    if (my_levels->game_win == 0){                   
                        my_levels->game_running = 1;
                        game_started = 1;
                    }
                }else if( e.key.keysym.sym == SDLK_RIGHT ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index[my_levels->current_level]]->direction_wanted = 1;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                        game_started = 1;
                }else if( e.key.keysym.sym == SDLK_UP ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index[my_levels->current_level]]->direction_wanted = 2;
                    if (my_levels->game_win == 0){                   
                        my_levels->game_running = 1;
                        game_started = 1;
                    }
                }else if( e.key.keysym.sym == SDLK_DOWN ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index[my_levels->current_level]]->direction_wanted = 3;
                    if (my_levels->game_win == 0){                   
                        my_levels->game_running = 1;
                        game_started = 1;
                    }
                }else if( e.key.keysym.sym == SDLK_a && my_levels->coop_pl_index[my_levels->current_level] != -1 && my_levels->coop == 1){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index[my_levels->current_level]]->direction_wanted = 0;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                        game_started = 1;
                }else if( e.key.keysym.sym == SDLK_d &&  my_levels->coop_pl_index[my_levels->current_level] != -1 && my_levels->coop == 1 ){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index[my_levels->current_level]]->direction_wanted = 1;
                    if (my_levels->game_win == 0){                   
                        my_levels->game_running = 1;
                        game_started = 1;
                    }
                }else if( e.key.keysym.sym == SDLK_w &&  my_levels->coop_pl_index[my_levels->current_level] != -1 && my_levels->coop == 1 ){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index[my_levels->current_level]]->direction_wanted = 2;
                    if (my_levels->game_win == 0){                   
                        my_levels->game_running = 1;
                        game_started = 1;
                    }
                }else if( e.key.keysym.sym == SDLK_s &&  my_levels->coop_pl_index[my_levels->current_level] != -1 && my_levels->coop == 1 ){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index[my_levels->current_level]]->direction_wanted = 3;
                    if (my_levels->game_win == 0){                   
                        my_levels->game_running = 1;
                        game_started = 1;
                    }
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) { // mouse button released
                // x: e.button.button.x
                // y: e.button.button.y
            }else if (e.type == SDL_MOUSEBUTTONDOWN){
                // if(e.button.button == SDL_BUTTON_RIGHT){}
            }else if (e.type == SDL_MOUSEMOTION) { // mouse movement
                // x: e.motion.x
                // y: e.motion.y
            }
        }

        int counter_time = (int)((SDL_GetTicks() - counter)/1000.0f);
        SDL_RenderClear(ren);
        if(my_levels->game_win == 0){
            if(game_started != 0){
                draw_background(&ren, win_width, win_height);
                draw_level(&ren, my_levels->entities[my_levels->current_level], my_levels->entities_len[my_levels->current_level], &my_levels, win_width, win_scale, 1);
            }else if(game_started == 0){
                draw_start_screen(&ren, my_levels, win_width, win_height, counter_time,1);
            }
        }else{
            int continue_time = 4 - counter_time;
            draw_finish_screen(&ren, &score_texture, &win_texture, &continue_texture, my_levels, win_width, win_height, continue_time, 1);
        }

        if(my_levels->game_running == 1){
            game_run( &ren, &my_levels, animation_count, animation_freq, my_levels->pl_index[my_levels->current_level] , my_levels->coop_pl_index[my_levels->current_level], scale, move_speed, win_scale, debug);
        }

        if(counter_time >= 4 || my_levels->score != last_score || my_levels->coop_score != last_coop_score || my_levels->lives != last_lives || my_levels->charge_time != last_charge || my_levels->game_win != last_win){
            if(my_levels->game_win == 0 && game_started != 0)
                draw_hud(&ren, &score_texture, &win_texture, my_levels, win_width, 1);            

            if(last_win == my_levels->game_win && my_levels->game_win == 1 && counter_time >= 4){
                if (my_levels->current_level != my_levels->maps_len - 1){
                    game_win(win, &my_levels, &win_width, &win_height, win_scale);    
                }
                counter = SDL_GetTicks();
            }
            if(last_win != my_levels->game_win && my_levels->game_win != 0)
                my_levels->game_running = 0;
            if(last_win == my_levels->game_win && my_levels->game_win != 1){
                counter = SDL_GetTicks();
            }
            
            last_win = my_levels->game_win;
            last_coop_score = my_levels->coop_score;
            last_score = my_levels->score;
            last_lives = my_levels->lives;
            last_charge = my_levels->charge_time;
            
            if(debug != 1){
                printf("\e[1;1H\e[2J");
                printf("Info:\n");
                if(my_levels->coop == 0)
                    printf(" Score: %i\n Lives: %i\n Charge %i\n FPS: %i\n\n", my_levels->score, my_levels->lives, my_levels->charge_time, fps);
                else
                    printf(" P1 Score: %i\n P2 Score: %i\n Lives: %i\n Charge %i\n FPS: %i\n\n", my_levels->score, my_levels->coop_score, my_levels->lives, my_levels->charge_time, fps);
            }else
                printf(" Score: %i\t Lives: %i\t Charge %i\t FPS: %i\n", my_levels->score, my_levels->lives, my_levels->charge_time, fps);
        }else{
            if(my_levels->game_win == 0 && game_started != 0)
                draw_hud(&ren, &score_texture, &win_texture, my_levels, win_width, 0);
        }
        
        SDL_RenderPresent(ren);   
        
        if(animation_count >= animation_freq)
            animation_count = 0;
        else
            animation_count++;

        float elapsed = (SDL_GetPerformanceCounter() - render_start_time) / (float)SDL_GetPerformanceFrequency();
        fps = (int)(1.0/elapsed); //move_scale = scale/move_speed; animation_freq = scale/6/2;        
        SDL_Delay((1000 - ((SDL_GetTicks() - tick_start_time) / 1000.0f))/ scale);
    }
    printf("Turning game off ...\n");

    levels_free(&my_levels);

    SDL_DestroyTexture(score_texture);
    SDL_DestroyTexture(win_texture);
    //SDL_DestroyTexture(texture);
    SDL_FreeFormat(fmt);
    sdl_playground_destroy( win, ren );

    return 0;
}
