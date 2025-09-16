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
        if( to_up != '#' || ( (((int)(round(((*entity)->pos_y - (move_speed * (1 / (double)scale))) * 100))) >= (int)(round((*entity)->pos_y) * 100)) && to_up == '#')){
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
    }else if ( ( (((int)(round(((*entity)->pos_y - (move_speed * (1 / (double)scale))) * 100))) < (int)(round((*entity)->pos_y) * 100)) && to_up == '#') &&
            ( ((int)(((*entity)->pos_y) * 100) > (int)(round((*entity)->pos_y) * 100)) ) ){
        (*entity)->pos_y = round((*entity)->pos_y);
        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if( (int)(*entity)->pos_y * 100 < (int)(round((*entity)->pos_y) * 100) && to_up == '#' ){
        (*entity)->pos_y = round((*entity)->pos_y);
    }
    (*entity)->pos_x = round((*entity)->pos_x);
}
void go_down(Entity** entity, Levels* level,const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq){
    if(((to_down != '#' && to_down != '-') || ( (((int)(round(((*entity)->pos_y + (move_speed * (1 / (double)scale))) * 100))) <= (int)(round((*entity)->pos_y) * 100))) && (to_down == '#' || to_down == '-'))){
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
    }else if ( ( (((int)(round(((*entity)->pos_y + (move_speed * (1 / (double)scale))) * 100))) > (int)(round((*entity)->pos_y) * 100)) && (to_down == '#' || to_down == '-') ) &&
            ( ((int)(((*entity)->pos_y) * 100) < (int)(round((*entity)->pos_y) * 100)) ) ){
        (*entity)->pos_y = round((*entity)->pos_y);
        
        if(animation_count == animation_freq)
            entity_swap_style(entity);
    }else if( (int)(*entity)->pos_y * 100 < (int)(round((*entity)->pos_y) * 100) && (to_down == '#' || to_down == '-')){
        (*entity)->pos_y = round((*entity)->pos_y);
    }
    (*entity)->pos_x = round((*entity)->pos_x);

    if(to_down == '-'){
        (*entity)->pos_y = round((*entity)->pos_y);
        (*entity)->last_change_x = 0;
        (*entity)->last_change_y = 0;
        if((*entity)->type != 'p')
            (*entity)->direction = rand() % 4; 
    }
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
            int px = (int)round(player->pos_x);
            int py = (int)round(player->pos_y);

            int vision_range = 6; // N cells
            int charge = (*level)->charge_time; // 0 normal, 1 power-up

            // Candidate directions and their passability
            int dirs[4] = {0,1,2,3};
            int passable[4] = { (to_left  != '#'), (to_right != '#'), (to_up    != '#'), (to_down  != '#' && to_down != '-') };

            // Utilities initialized to small noise to avoid ties
            double util[4] = { (rand()%3)*0.01, (rand()%3)*0.01, (rand()%3)*0.01, (rand()%3)*0.01 };

            // Penalty for immediate reversal to reduce jitter
            int opposite = ((*entity)->direction == 0) ? 1 : ((*entity)->direction == 1) ? 0 : ((*entity)->direction == 2) ? 3 : 2;
            util[opposite] -= 0.05;

            // Bias using N-cell straight-line vision
            if(ex == px){
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
                    (*entity)->last_seen_frames = 2;
                }
            }
            if(ey == py){
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
                    (*entity)->last_seen_frames = 2;
                }
            }

            // If Pacman not currently visible, bias by recent memory
            if((*entity)->last_seen_frames > 0){
                int mdir = (*entity)->last_seen_dir;
                if(mdir >= 0 && mdir <= 3){
                    util[mdir] += (charge == 0) ? 0.4 : -0.2; // small bias to keep moving toward last seen
                }
                (*entity)->last_seen_frames--;
                if((*entity)->last_seen_frames == 0) (*entity)->last_seen_dir = -1;
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

