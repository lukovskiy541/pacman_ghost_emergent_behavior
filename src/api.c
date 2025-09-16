#include "lib/api.h"
#include <string.h>

int to_1d( const int row, const int col, const int cols ) {
    return row * cols + col;
}

char* get_address(Entity* entity, Levels* level, const int level_index, const int direction, const int style){
    char* address = malloc(sizeof(char) * 100); address[0] = '\0';

    if(level->coop == 1 && entity->type == 'p')
        address = strcat(address, "res/characters/p/coop");
    else{
        address = strcat(address, "res/characters/");
    
        char type[2];
        if(direction == 4 || direction == 5){
            type[0] = 'g'; type[1] = '\0';
        }else{
            type[0] = entity->type; type[1] = '\0';
        }
        address = strcat(address, type);
    }

    if(entity->type != 'p')
        address = strcat(address, "/npc_");
    else{
        if(level->coop == 1){
            if( level->entities[level_index][level->coop_pl_index[level->current_level]]->pos_x == entity->pos_x && 
                level->entities[level_index][level->coop_pl_index[level->current_level]]->pos_y == entity->pos_y){
                address = strcat(address, "/coplayer_");
            }else
                address = strcat(address, "/player_");
        }else
            address = strcat(address, "/player_");
    }
    if(direction == -1)
        address = strcat(address, "stop");
    else if(direction == 0)
        address = strcat(address, "left");
    else if(direction == 1)
        address = strcat(address, "right");
    else if(direction == 2)
        address = strcat(address, "up");
    else if(direction == 3)
        address = strcat(address, "down");
    else if(direction == 4)
        address = strcat(address, "blue");
    else
        address = strcat(address, "white");

    char animation[2]; animation[0] = (style + 1) + '0'; animation[1] = '\0';
    address = strcat(address, animation);
    address = strcat(address, ".png");
    return address;
}

void get_args(int argc, char** argv, int* coop,int* move_speed, int* levels_count, int* debug){
    // Keep legacy positional parsing only for pure numeric trailing args
    int n_numeric = 0;
    for(int i=argc-1; i>=1 && n_numeric < 4; i--){ if(is_numeric_str(argv[i])) n_numeric++; else break; }
    if(n_numeric >= 1){
        int idx = argc - n_numeric;
        if(n_numeric >= 1 && atoi(argv[idx]) != 0) { *coop = atoi(argv[idx]); idx++; }
        if(n_numeric >= 2 && atoi(argv[idx]) != 0) { *move_speed = atoi(argv[idx]); idx++; }
        if(n_numeric >= 3 && atoi(argv[idx]) != 0) { *levels_count = atoi(argv[idx]); idx++; }
        if(n_numeric >= 4) { *debug = atoi(argv[idx]); }
    }
}

// Optional: parse feature toggles of the form --vision=0/1 --memory=0/1 --pher=0/1
int parse_flag(const char* arg, const char* key){
    size_t klen = strlen(key);
    if(strncmp(arg, key, klen) == 0){
        const char* v = arg + klen;
        if(*v == '=') v++;
        return atoi(v);
    }
    return -1;
}

int is_numeric_str(const char* s){
    if(!s || !*s) return 0;
    const char* p = s; if(*p=='+'||*p=='-') p++;
    int has_digit = 0;
    while(*p){ if(*p<'0'||*p>'9') return 0; has_digit=1; p++; }
    return has_digit;
}

void check_texture_error(SDL_Texture* self){
    if(!self){
        fprintf(stderr, "Texture create error: %s\n", SDL_GetError());
        exit(1);
    }
}
void check_font_error(TTF_Font* self){
    if(!self){
        fprintf(stderr, "Font create error: %s\n", SDL_GetError());
        exit(1);
    }
}