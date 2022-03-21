/*
 * StateMachne.c
 *
 * Created: 21/03/2022 14:53:05
 * Author : SS7U9741
 */ 

#include <avr/io.h>

void fn_STATE1(void);
void fn_STATE2(void);
void fn_STATE3(void);
void fn_STATE4(void);
void fn_STATE5(void);

typedef enum {STATE1, STATE2, STATE3, STATE4 , STATE5}State_Type;

void (*state_table[])(void) = {&fn_STATE1, &fn_STATE2, &fn_STATE3, &fn_STATE4, &fn_STATE5};

State_Type current_state;

void fn_STATE1(void){
	current_state = STATE2;
}
void fn_STATE2(void){
	current_state = STATE3;
}

void fn_STATE3(void){
	current_state = STATE4;
}

void fn_STATE4(void){
	current_state = STATE5;
}

void fn_STATE5(void){
	current_state = STATE1;
}

int main(void)
{
    /* Replace with your application code */
	current_state = STATE1;
    while (1) 
    {
		state_table[current_state](); 
    }
}

