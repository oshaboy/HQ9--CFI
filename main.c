#include <stdio.h>
#include "HQ9+.h"
int main(int argc, char * argv[]){
    HQ9P_State * state_p;
    char code[2048];
    FILE * stream;
    if (argc<=1){
        stream=stdin;
    }
    else{
        stream=fopen(argv[1], "rt");
    }
    fgets(code,2048,stream);
    state_p=HQ9P_initialize(code);
    while(!HQ9P_is_at_end(state_p)){
        HQ9P_parse_next_char(state_p);
    }
    return 0;
}