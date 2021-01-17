#include<iostream>
#include<fstream>

#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>

#include"classes.h"
#include"Location.h"

int set_dir(const Snake& snake, ALLEGRO_EVENT pressed_key);

void place_point(Point &point, Board brd);

int main(){


    std::fstream log;
    log.open("log.txt", std::fstream::out | std::fstream::app);
    
//*####### INITIALIZING ALLEGRO ########
//    timer, queue, display, font, redraw, event

    if(!al_init()){
        printf("no al\n");
        return 0;
    }
    if(!al_install_keyboard()){
        printf("no keyboard\n");
        return 0;
    }
    if(!al_init_image_addon()){
        printf("no image\n");
        return 0;
    }

    if(!al_init_primitives_addon()){
        printf("no primitives\n");
        return 0;
    }

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    if(!timer){
        printf("no timer\n");
        return 0;
    }
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if(!queue){
        printf("no queue\n");
        return 0;
    }
    ALLEGRO_DISPLAY* display = al_create_display(640, 400);
    if(!display){
        printf("no display\n");
        return 0;
    }

    ALLEGRO_FONT* font = al_create_builtin_font();
    if(!font){
        printf("no font\n");
        return 0;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    
    al_start_timer(timer);

//*###### GAME SET UP ###########

    srand(time(NULL));

    Board board;
    board.w = 10;//test values
    board.h = 7;
    board.a = 60;

    float speed=1.5f;

    int FPS=60;

    Location sn_loc;

    Point point;
    place_point(point, board);

//### LOADING SETTINGS ###
/*
    std::ifstream settings;
    settings.open("settings.txt");
    settings>>sn_loc.x>>sn_loc.y>>speed;
*/

    sn_loc.x=4;
    sn_loc.y=3;
    Snake snake(sn_loc, speed, FPS);

    bool redraw= true;
    ALLEGRO_EVENT event;

    board.disp_h=al_get_display_height(display);
    board.disp_w=al_get_display_width(display);

    snake.draw(&board);
    
    int wait=1;
    while(wait){
        al_wait_for_event(queue, &event);
        if(event.type == ALLEGRO_KEY_SPACE) wait=0;
    }
    
    

    int move_timer=0;

//*###### MAIN GAME LOOP ########
    while(1){

        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        else if(event.type == ALLEGRO_EVENT_TIMER){
            snake.step();
        }
        else if(redraw && al_is_event_queue_empty(queue)){
            snake.draw(&board);
            redraw=false;
        }
        
        else{
           switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                snake.set_dir(parse_dir(0));
                break;
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D:
                snake.set_dir(parse_dir(1));
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                snake.set_dir(parse_dir(2));
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                snake.set_dir(parse_dir(3));
                break;                     
            }
        }
        
        if(snake.game_over(board))break;
        
        if(snake.get_head_loc()== point.loc){
            snake.grow();
            place_point(point, board);
        }


        al_wait_for_event(queue, &event);
    }

//*###### CLEANING UP ########
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    return 0;
}


void place_point(Point &point, Board brd){
    point.loc.x= rand()%brd.w;
    point.loc.y= rand()%brd.h;
}