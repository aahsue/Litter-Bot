#include <stdio.h>

#define en 12
#define in1 32
#define in2 33

void main(void){
    int user_inp;
    while(1){
        gpio_set_direction(en, 1);
        scanf("%d", user_inp);
        if(user_inp == 1){
            forward();
        }
        else if(){
            backward();
        }
        else{
            return;
        }
    }
    gpio_set_direction(en, 0);
}

void forward(){
    gpio_set_direction(in1, 1);
    gpio_set_direction(in2, 0);
}

void backward(){
    gpio_set_direction(in1, 0);
    gpio_set_direction(in2, 1);
}