#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "HQ9+.h"

void bottles();
char * bottles_buf( char * s,size_t n);
void linedemo();
struct HQ9P_State{
    char * code;
    char * code_ptr;
    int accumulator;
    int code_length;
};
HQ9P_State * HQ9P_default_state=NULL;
HQ9P_State * HQ9P_initialize(char * code){
    time_t t;
    srand((unsigned) time(&t));
    HQ9P_default_state = malloc(sizeof(HQ9P_State));
    HQ9P_default_state->accumulator=0;
    HQ9P_default_state->code_length=strlen(code);
    HQ9P_default_state->code_ptr=HQ9P_default_state->code=malloc(HQ9P_default_state->code_length+1);
    strcpy(HQ9P_default_state->code,code);
    SDL_Init(SDL_INIT_EVERYTHING);
    return HQ9P_default_state;
}
void HQ9P_destroy(HQ9P_State * state_p){
    free(state_p->code);
    state_p->accumulator=rand(); /* Data Hiding */
    free(state_p);

}
int HQ9P_is_at_end(HQ9P_State * state_p){
    return state_p->code_ptr>state_p->code+state_p->code_length;
}
void HQ9P_parse_next_char(HQ9P_State * state_p){
    HQ9P_parse_char(state_p,*(state_p->code_ptr++));
}
char * HQ9P_parse_next_char_buf(char * buf, size_t n,HQ9P_State * state_p){
    return HQ9P_parse_char_buf(buf, n,state_p,*(state_p->code_ptr++));
}
char * HQ9P_parse_char_buf(char * buf, size_t n, HQ9P_State * state,char c){
    switch (c){
        case 'h':
        case 'H':
            strncpy(buf, "Hello, World!\n", n); 
        case 'q':
        case 'Q':
            strncpy(buf, state->code, n); 
            break;
        case '9':
            bottles_buf( buf, n);
            break;
        case 's':
        case 'S':
            linedemo();
            if (n>0) *buf='\0';
            break;

        case '+':
            state->accumulator++;
        default:
            if (n>0) *buf='\0';
            break;

    } 
    return buf;
}
void HQ9P_parse_char(HQ9P_State * state, char c){
    switch (c){
        case 'h':
        case 'H':
            puts("Hello, World!"); 
            break;
        case 'q':
        case 'Q':
            puts(state->code);
            break;
        case '9':
            bottles();
            break;
        case '+':
            state->accumulator++;
            break;
        case 's':
        case 'S':
            linedemo();
            break;
    }
}
void linedemo(){
    SDL_Window * the_window=SDL_CreateWindow("HQ9+ with Function Interface", 0,0,1024,768,SDL_WINDOW_OPENGL);
    SDL_Renderer * the_renderer=SDL_CreateRenderer(the_window, -1, SDL_RENDERER_SOFTWARE);

    SDL_SetRenderDrawColor(the_renderer, 255,255,255,255);
    SDL_RenderClear(the_renderer);
    
    SDL_RenderPresent(the_renderer);
    bool quit=false;
    while (!quit){
        uint8_t r=(uint8_t)rand();
        uint8_t g=(uint8_t)rand();
        uint8_t b=(uint8_t)rand();

        SDL_SetRenderDrawColor(the_renderer, r,g,b,255);
        int x1=rand()%1024;
        int y1=rand()%768;
        int x2=rand()%1024;
        int y2=rand()%768;
        SDL_RenderDrawLine(the_renderer,x1, y1,x2,y2);

        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if (e.type==SDL_QUIT){
                quit=true;
            }
        } 

        SDL_RenderPresent(the_renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(the_renderer);
    SDL_DestroyWindow(the_window);


}
void bottles(){
    int bottles=99;
    while (1){
        printf("%d bottle%s of beer on the wall\n",bottles,bottles==1?"":"s");
        printf("%d bottle%s of beer\n",bottles,bottles==1?"":"s");
        printf("Take one down, pass it around\n"); bottles--;
        if (bottles<=0) break;
        printf("%d bottle%s of beer on the wall\n\n",bottles,bottles==1?"":"s");
        

    }
    printf("no more bottles of beer on the wall\n\n");
    
    printf("no more bottles of beer on the wall\n");
    
    printf("no more bottles of beer\n");
    
    printf("go to the store, buy some more\n");
    
    printf("99 bottles of beer on the wall\n");

}
char * bottles_buf(char * buf, size_t n){
    int bottles=99;
    int remove_amount;
    while (1){
        remove_amount=snprintf(buf,n,"%d bottle%s of beer on the wall\n",bottles,bottles==1?"":"s");
        buf+=remove_amount; n-=remove_amount;
        remove_amount=snprintf(buf,n,"%d bottle%s of beer\n",bottles,bottles==1?"":"s");
        buf+=remove_amount; n-=remove_amount;
        remove_amount=snprintf(buf,n,"Take one down, pass it around\n"); bottles--;
        buf+=remove_amount; n-=remove_amount;
        if (bottles<=0) break;
        remove_amount=snprintf(buf,n,"%d bottle%s of beer on the wall\n\n",bottles,bottles==1?"":"s");
        buf+=remove_amount; n-=remove_amount;
        

    }
    remove_amount=snprintf(buf,n,"no more bottles of beer on the wall\n\n");
    buf+=remove_amount; n-=remove_amount;
    
    remove_amount=snprintf(buf,n,"no more bottles of beer on the wall\n");
    buf+=remove_amount; n-=remove_amount;
    
    remove_amount=snprintf(buf,n,"no more bottles of beer\n");
    buf+=remove_amount; n-=remove_amount;
    
    remove_amount=snprintf(buf,n,"go to the store, buy some more\n");
    buf+=remove_amount; n-=remove_amount;
    
    remove_amount=snprintf(buf,n,"99 bottles of beer on the wall\n");
    return buf;
    
}