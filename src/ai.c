#include "lib/ai.h"

void go_left(Entity** entity, Levels* level, const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq){
    if( to_left != '#' || ( (((int)(round(((*entity)->pos_x - (move_speed * (1 / (double)scale))) * 100))) >= (int)(round((*entity)->pos_x) * 100)) && to_left == '#')){
        if(level->charge_time == 0 || (*entity)->type == 'p'){
            if ((*entity)->type == 'p')
                (*entity)->pos_x -= move_speed * (1 / (double)scale);
            else
                (*entity)->pos_x -= move_speed * ((1 / (double)scale) * 7 / 8);
        }else
            (*entity)->pos_x -= move_speed * ((1 / (double)scale) * 1 / 2);
        (*entity)->pos_y = round((*entity)->pos_y);

        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if ( ( (((int)(round(((*entity)->pos_x - (move_speed * (1 / (double)scale))) * 100))) < (int)(round((*entity)->pos_x) * 100)) && to_left == '#') &&
            ( ((int)(((*entity)->pos_x) * 100) > (int)(round((*entity)->pos_x) * 100)) ) ){
        (*entity)->pos_x = round((*entity)->pos_x);

        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if( (int)(*entity)->pos_x * 100 > (int)(round((*entity)->pos_x) * 100) && to_left == '#' ){
        (*entity)->pos_x = round((*entity)->pos_x);
    }
    (*entity)->pos_y = round((*entity)->pos_y);

    // printf("%.2f %i %i\n", move_speed * (1 / (double)scale), move_speed, scale);
}
void go_right(Entity** entity, Levels* level, const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq){
    if(to_right != '#' || ( (((int)(round(((*entity)->pos_x + (move_speed * (1 / (double)scale))) * 100))) <= (int)(round((*entity)->pos_x) * 100)) && to_right == '#')){
        if(level->charge_time == 0 || (*entity)->type == 'p'){
            if ((*entity)->type == 'p')
                (*entity)->pos_x += move_speed * (1 / (double)scale);
            else
                (*entity)->pos_x += move_speed * ((1 / (double)scale) * 7 / 8);
        }else
            (*entity)->pos_x += move_speed * ((1 / (double)scale) * 1 / 2);
        (*entity)->pos_y = round((*entity)->pos_y);

        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if ( ( (((int)(round(((*entity)->pos_x + (move_speed * (1 / (double)scale))) * 100))) > (int)(round((*entity)->pos_x) * 100)) && to_right == '#') &&
            ( ((int)(((*entity)->pos_x) * 100) < (int)(round((*entity)->pos_x) * 100)) ) ){
        (*entity)->pos_x = round((*entity)->pos_x);

        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if( (int)(*entity)->pos_x * 100 < (int)(round((*entity)->pos_x) * 100) && to_right == '#' ){
        (*entity)->pos_x = round((*entity)->pos_x);
    }
    (*entity)->pos_y = round((*entity)->pos_y);
}
void go_up(Entity** entity, Levels* level, const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq){
        // Allow ghosts (non-player) to pass through pen door '-' above like empty space
        int is_player_u = ((*entity)->type == 'p');
        int is_wall_u = (to_up == '#');
        int is_door_u = (to_up == '-');
        int is_blocking_for_entity_u = is_wall_u || (is_player_u && is_door_u);

        if( (!is_blocking_for_entity_u) || ( (((int)(round(((*entity)->pos_y - (move_speed * (1 / (double)scale))) * 100))) >= (int)(round((*entity)->pos_y) * 100)) && is_blocking_for_entity_u) ){
        if(level->charge_time == 0 || (*entity)->type == 'p'){
            if ((*entity)->type == 'p')
                (*entity)->pos_y -= move_speed * (1 / (double)scale);
            else
                (*entity)->pos_y -= move_speed * ((1 / (double)scale) * 7 / 8);
        }else
            (*entity)->pos_y -= move_speed * ((1 / (double)scale) * 1 / 2);
        (*entity)->pos_x = round((*entity)->pos_x);
        
        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if ( ( (((int)(round(((*entity)->pos_y - (move_speed * (1 / (double)scale))) * 100))) < (int)(round((*entity)->pos_y) * 100)) && (is_blocking_for_entity_u) ) &&
            ( ((int)(((*entity)->pos_y) * 100) > (int)(round((*entity)->pos_y) * 100)) ) ){
        (*entity)->pos_y = round((*entity)->pos_y);
        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if( (int)(*entity)->pos_y * 100 < (int)(round((*entity)->pos_y) * 100) && (is_blocking_for_entity_u) ){
        (*entity)->pos_y = round((*entity)->pos_y);
    }
    (*entity)->pos_x = round((*entity)->pos_x);
}
void go_down(Entity** entity, Levels* level,const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq){
    // Allow ghosts (non-player) to pass through the pen door '-' like empty space
    int is_player = ((*entity)->type == 'p');
    int is_wall = (to_down == '#');
    int is_door = (to_down == '-');
    int is_blocking_for_entity = is_wall || (is_player && is_door);

    if((!is_blocking_for_entity) || ( (((int)(round(((*entity)->pos_y + (move_speed * (1 / (double)scale))) * 100))) <= (int)(round((*entity)->pos_y) * 100)) && is_blocking_for_entity )){
        if(level->charge_time == 0 || (*entity)->type == 'p'){
            if ((*entity)->type == 'p')
                (*entity)->pos_y += move_speed * (1 / (double)scale);
            else
                (*entity)->pos_y += move_speed * ((1 / (double)scale) * 7 / 8);
        }else
            (*entity)->pos_y += move_speed * ((1 / (double)scale) * 1 / 2);
        (*entity)->pos_x = round((*entity)->pos_x);
        
        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if ( ( (((int)(round(((*entity)->pos_y + (move_speed * (1 / (double)scale))) * 100))) > (int)(round((*entity)->pos_y) * 100)) && (is_blocking_for_entity) ) &&
            ( ((int)(((*entity)->pos_y) * 100) < (int)(round((*entity)->pos_y) * 100)) ) ){
        (*entity)->pos_y = round((*entity)->pos_y);
        
        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if( (int)(*entity)->pos_y * 100 < (int)(round((*entity)->pos_y) * 100) && (is_blocking_for_entity)){
        (*entity)->pos_y = round((*entity)->pos_y);
    }
    (*entity)->pos_x = round((*entity)->pos_x);

    // No special door-side effects beyond passability
}

void choose_way_pom(Entity** entity, int way, char to_left, char to_right, char to_up, char to_down){
    char left, right, up, down;
    int left_w, right_w, up_w, down_w;

    if(way == 0){
        left = to_down; right = to_up; up = to_left; down = to_right;
        left_w = 3; right_w = 2; up_w = 0; down_w = 1;
    }else if(way == 1){
        left = to_up; right = to_down; up = to_right; down = to_left;
        left_w = 2; right_w = 3; up_w = 1; down_w = 0;
    }else if(way == 2){
        left = to_left; right = to_right; up = to_up; down = to_down;
        left_w = 0; right_w = 1; up_w = 2; down_w = 3;
    }else if(way == 3){
        left = to_right; right = to_left; up = to_down; down = to_up;
        left_w = 1; right_w = 0; up_w = 3; down_w = 2;
    }else if (way != -1){
        fprintf(stderr, "Wrong input to choose_way_pom\n"); exit(1);
    }

    if((*entity)->type != 'p'){
        if(left != '#' && right != '#'){
            // printf("C-%c Try 1\n", (*entity)->type);
            if(up != '#'){
                do{
                    (*entity)->direction_next = rand() % 4;
                }while ((*entity)->direction_next == down_w);
            }else{
                do{
                    (*entity)->direction_next = rand() % 4;
                }while ((*entity)->direction_next == up_w || (*entity)->direction_next == down_w);
            }
        }else if(left != '#'){
            // printf("C-%c Try 2\n", (*entity)->type);
            if(up != '#'){
                do{
                    (*entity)->direction_next = rand() % 4;
                }while ((*entity)->direction_next == right_w || (*entity)->direction_next == down_w);
            }else{
                do{                
                    (*entity)->direction_next = rand() % 4;
                }while ((*entity)->direction_next == up_w || (*entity)->direction_next == right_w || (*entity)->direction_next == down_w);
            }
        }else if(right != '#'){
            // printf("C-%c Try 3\n", (*entity)->type);
            if(up != '#'){
                do{
                    (*entity)->direction_next = rand() % 4;
                }while ((*entity)->direction_next == left_w || (*entity)->direction_next == down_w);
            }else{
                do{
                    (*entity)->direction_next = rand() % 4;
                }while ((*entity)->direction_next == up_w || (*entity)->direction_next == left_w || (*entity)->direction_next == down_w);
            }
        }else if(left == '#' && right == '#' && up != '#'){
            (*entity)->direction_next = way;
        }else if(down != '#' && left == '#' && right == '#' && up == '#'){
            //printf("C-%c Try 4\n", (*entity)->type);
            (*entity)->direction_next = down_w;
        }
    }else{
        switch ((*entity)->direction_wanted){
        case -1:
            break;
        case 0:
            if(to_left != '#')  { (*entity)->direction_next = (*entity)->direction_wanted; } break;
        case 1:
            if(to_right != '#') { (*entity)->direction_next = (*entity)->direction_wanted; } break;
        case 2:
            if(to_up != '#')    { (*entity)->direction_next = (*entity)->direction_wanted; } break;
        case 3:
            if(to_down != '#' && to_down != '-')  { (*entity)->direction_next = (*entity)->direction_wanted; } break;
        default:
            fprintf(stderr, "Wrong input to choose_way_pom - direction_wanted\n"); exit(1); break;
        }
    }    
    // if((*entity)->type == 'y')
        // printf("x%.2f\ty%.2f\t w%i\t wN%i [%c|%c][%c|%c]\n", ((*entity)->pos_x), ((*entity)->pos_y), (*entity)->direction, (*entity)->direction_next, left, right, up, down);
}
void choose_way(Entity** entity, Levels** level, char to_left, char to_right, char to_up, char to_down){

    if( /* (*entity)->direction == (*entity)->direction_next && */
        !((fabs((*entity)->last_change_x - round((*entity)->pos_x)) < 0.00001) && (fabs((*entity)->last_change_y - round((*entity)->pos_y)) < 0.00001))){
        // Local, simple rules with N-cell vision to bias choices
        if((*entity)->type != 'p'){
            int current_level_index = (*level)->current_level;
            int player_index = (*level)->pl_index[current_level_index];
            Entity* player = (*level)->entities[current_level_index][player_index];

            int ex = (int)round((*entity)->pos_x);
            int ey = (int)round((*entity)->pos_y);
            // (Removed) door-exit suppression state update
            int px = (int)round(player->pos_x);
            int py = (int)round(player->pos_y);

            int vision_range = 6; // N cells
            int charge = (*level)->charge_time; // 0 normal, 1 power-up
            Uint32 now_ms = SDL_GetTicks();

            // Candidate directions and their passability
            int dirs[4] = {0,1,2,3};
            int passable_down = (to_down != '#');
            // Allow ghosts to pass through door '-' when moving down out of the pen
            if((*entity)->type == 'p'){
                passable_down = (to_down != '#' && to_down != '-');
            }
            int passable[4] = { (to_left  != '#'), (to_right != '#'), (to_up    != '#'), passable_down };

            // Utilities initialized to small noise to avoid ties
            double util[4] = { (rand()%3)*0.01, (rand()%3)*0.01, (rand()%3)*0.01, (rand()%3)*0.01 };

            // Penalty for immediate reversal to reduce jitter
            int opposite = ((*entity)->direction == 0) ? 1 : ((*entity)->direction == 1) ? 0 : ((*entity)->direction == 2) ? 3 : 2;
            util[opposite] -= 0.05;

            // Bias using N-cell straight-line vision
            Uint32 memory_duration_ms = 1000; // short-term memory duration
            if((*level)->ai_enable_vision && ex == px){
                int dy = (py > ey) ? 1 : -1;
                int steps = 0; int blocked = 0;
                for(int y = ey + dy; y != py && steps < vision_range; y += dy, steps++){
                    char cell = (*level)->maps[current_level_index][to_1d(ex, y, (*level)->maps_size_y[current_level_index])];
                    if(cell == '#'){ blocked = 1; break; }
                }
                if(!blocked && steps <= vision_range){
                    // Player within vision vertically
                    int toward = (py < ey) ? 2 : 3;
                    int away   = (py < ey) ? 3 : 2;
                    util[toward] += (charge == 0) ? 1.0 : -1.0;
                    util[away]   += (charge == 0) ? 0.0 : 0.5;
                    // Update short-term memory
                    (*entity)->last_seen_dir = toward;
                    (*entity)->last_seen_until_ms = now_ms + memory_duration_ms;
                }
            }
            if((*level)->ai_enable_vision && ey == py){
                int dx = (px > ex) ? 1 : -1;
                int steps = 0; int blocked = 0;
                for(int x = ex + dx; x != px && steps < vision_range; x += dx, steps++){
                    char cell = (*level)->maps[current_level_index][to_1d(x, ey, (*level)->maps_size_y[current_level_index])];
                    if(cell == '#'){ blocked = 1; break; }
                }
                if(!blocked && steps <= vision_range){
                    // Player within vision horizontally
                    int toward = (px < ex) ? 0 : 1;
                    int away   = (px < ex) ? 1 : 0;
                    util[toward] += (charge == 0) ? 1.0 : -1.0;
                    util[away]   += (charge == 0) ? 0.0 : 0.5;
                    // Update short-term memory
                    (*entity)->last_seen_dir = toward;
                    (*entity)->last_seen_until_ms = now_ms + memory_duration_ms;
                }
            }

            // If Pacman not currently visible, bias by recent memory
            if((*level)->ai_enable_memory && (*entity)->last_seen_until_ms > now_ms){
                int mdir = (*entity)->last_seen_dir;
                if(mdir >= 0 && mdir <= 3){
                    util[mdir] += (charge == 0) ? 0.4 : -0.2; // small bias to keep moving toward last seen
                }
            } else if((*entity)->last_seen_dir != -1){
                (*entity)->last_seen_dir = -1;
            }

            // Removed door-specific biases; treat '-' as passable for ghosts only in movement

            // Ghost-vs-ghost avoidance (enabled only outside spawn area)
            if((*level)->ai_enable_ghost_vision){
                // Only enable when sufficiently far from own spawn and not near door '-'
                int spawn_x = (int)round((*entity)->start_pos_x);
                int spawn_y = (int)round((*entity)->start_pos_y);
                int dist_from_spawn = abs(ex - spawn_x) + abs(ey - spawn_y);
                char here_cell2 = (*level)->maps[current_level_index][to_1d(ex, ey, (*level)->maps_size_y[current_level_index])];
                int sy_sz = (*level)->maps_size_y[current_level_index];
                int sx_sz = (*level)->maps_size_x[current_level_index];
                int near_door = (here_cell2 == '-') || (to_down == '-') || (to_up == '-');
                if(!near_door){
                    for(int dy=-2; dy<=2 && !near_door; dy++){
                        for(int dx=-2; dx<=2 && !near_door; dx++){
                            if(abs(dx)+abs(dy) > 2) continue;
                            int cx = ex + dx;
                            int cy = ey + dy;
                            if(cx<0||cy<0||cx>=sx_sz||cy>=sy_sz) continue;
                            if((*level)->maps[current_level_index][to_1d(cx, cy, sy_sz)] == '-') near_door = 1;
                        }
                    }
                }
                if(dist_from_spawn > 3 && !near_door){
                    int nents = (*level)->entities_len[current_level_index];
                    for(int e = 0; e < nents; e++){
                        if(e == player_index) continue;
                        Entity* other = (*level)->entities[current_level_index][e];
                        if(other == *entity) continue;
                        if(other->type == 'p') continue;

                        int ox = (int)round(other->pos_x);
                        int oy = (int)round(other->pos_y);
                        int blocked = 0;
                        int steps = 0;
                        if(oy == ey && ox != ex){
                            int dx = (ox > ex) ? 1 : -1;
                            for(int x = ex + dx; x != ox && steps < vision_range; x += dx, steps++){
                                char cell = (*level)->maps[current_level_index][to_1d(x, ey, (*level)->maps_size_y[current_level_index])];
                                if(cell == '#'){ blocked = 1; break; }
                            }
                            if(!blocked && steps <= vision_range){
                                int away = (ox > ex) ? 0 : 1;
                                util[away] += 0.5;
                                int toward = (away == 0) ? 1 : 0;
                                util[toward] -= 0.5;
                                break;
                            }
                        } else if(ox == ex && oy != ey){
                            int dy = (oy > ey) ? 1 : -1;
                            for(int y = ey + dy; y != oy && steps < vision_range; y += dy, steps++){
                                char cell = (*level)->maps[current_level_index][to_1d(ex, y, (*level)->maps_size_y[current_level_index])];
                                if(cell == '#'){ blocked = 1; break; }
                            }
                            if(!blocked && steps <= vision_range){
                                int away = (oy > ey) ? 2 : 3;
                                util[away] += 0.5;
                                int toward = (away == 2) ? 3 : 2;
                                util[toward] -= 0.5;
                                break;
                            }
                        }
                    }
                }
            }

            // Ghost-vs-ghost repulsion removed entirely

            // Pheromone gradient bias (attract to higher values unless power-up)
            if((*level)->ai_enable_pheromones){
                int cll = (*level)->current_level;
                int gx = (int)round((*entity)->pos_x);
                int gy = (int)round((*entity)->pos_y);
                int sx = (*level)->maps_size_x[cll];
                int sy = (*level)->maps_size_y[cll];
                float* ph = (*level)->pheromone_player[cll];
                float here = 0.0f;
                if(gx>=0 && gy>=0 && gx<sx && gy<sy){ here = ph[to_1d(gx,gy,sy)]; }
                float lv = 0.0f, rv = 0.0f, uv = 0.0f, dv = 0.0f;
                if(gx-1>=0) lv = ph[to_1d(gx-1,gy,sy)] - here;
                if(gx+1<sx) rv = ph[to_1d(gx+1,gy,sy)] - here;
                if(gy-1>=0) uv = ph[to_1d(gx,gy-1,sy)] - here;
                if(gy+1<sy) dv = ph[to_1d(gx,gy+1,sy)] - here;
                float scale_bias = 0.2f * (charge==0 ? 1.0f : -1.0f);
                util[0] += scale_bias * lv;
                util[1] += scale_bias * rv;
                util[2] += scale_bias * uv;
                util[3] += scale_bias * dv;
            }

            // Prefer directions that are passable; heavily penalize non-passable
            for(int i=0;i<4;i++){
                if(!passable[i]) util[i] -= 100.0;
            }

            // Choose best utility among passable moves
            int best_dir = (*entity)->direction;
            double best_val = -1e9;
            for(int i=0;i<4;i++){
                if(util[i] > best_val){ best_val = util[i]; best_dir = i; }
            }
            (*entity)->direction_next = best_dir;
        }else{
            choose_way_pom(entity, (*entity)->direction, to_left, to_right, to_up, to_down);
        }
    }

    // if((*entity)->type == 'p')
        // printf("x%.2f\ty%.2f\t w%i\t wN%i\t lcx%i\t lcy%i\n", ((*entity)->pos_x), ((*entity)->pos_y), (*entity)->direction, (*entity)->direction_next, (*entity)->last_change_x, (*entity)->last_change_y);

    if((*entity)->type != 'p'){
        if( ((*entity)->direction != (*entity)->direction_next) && 
            ( (int)((round((*entity)->pos_x) - 0.02) * 100) <= (int)((*entity)->pos_x * 100) && (int)((*entity)->pos_x * 100) <= (int)((round((*entity)->pos_x) + 0.02) * 100)) ||
            ( (int)((round((*entity)->pos_y) - 0.02) * 100) <= (int)((*entity)->pos_y * 100) && (int)((*entity)->pos_x * 100) <= (int)((round((*entity)->pos_y) + 0.02) * 100)) ){

            if( ( !((fabs((*entity)->last_change_x - round((*entity)->pos_x)) < 0.00001) && (fabs((*entity)->last_change_y - round((*entity)->pos_y)) < 0.00001)) ) ){
                (*entity)->direction = (*entity)->direction_next;
                if((*entity)->type != 'p'){
                    (*entity)->last_change_x = (int)round((*entity)->pos_x);
                    (*entity)->last_change_y = (int)round((*entity)->pos_y);      
                }
            }
        }
    }else{
        if( ((*entity)->direction != (*entity)->direction_next) ){
            (*entity)->direction = (*entity)->direction_next;

        }
    }

    if((*entity)->type == 'p'){
        game_score( entity, level);
    }
    
    game_teleport(entity, *level);

    // if((*entity)->type == 'p')
    //    printf("x%.2f\ty%.2f\t lx%i\tly%i\n", ((*entity)->pos_x), ((*entity)->pos_y), (*entity)->last_change_x, (*entity)->last_change_y);
        
}

