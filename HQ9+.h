#ifndef HQ9P_H
#define HQ9P_H
#include <stddef.h>
struct HQ9P_State;
typedef struct HQ9P_State HQ9P_State;
HQ9P_State * HQ9P_initialize(char * code);
void HQ9P_destroy(HQ9P_State *);
void HQ9P_parse_char(HQ9P_State * state,char c);
void HQ9P_parse_next_char(HQ9P_State * state);
int HQ9P_is_at_end(HQ9P_State * state);
char * HQ9P_parse_char_buf( char * buf, size_t n, HQ9P_State * state,char c);
char * HQ9P_parse_next_char_buf(char * buf, size_t n, HQ9P_State * state);

extern HQ9P_State * HQ9P_default_state; /*internal*/
#define H HQ9P_parse_char(HQ9P_default_state,'h')
#define Q HQ9P_parse_char(HQ9P_default_state,'q')
#define N HQ9P_parse_char(HQ9P_default_state,'9')
#define P HQ9P_parse_char(HQ9P_default_state,'+')
#define S HQ9P_parse_char(HQ9P_default_state,'s')



#endif