#include"classes.h"
#include"Location.h"
#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>

//test diplay: 960X600
void Board::draw_board(){

    float halfx = w*a/2.0;
    float halfy = h*a/2.0;
    float x1= disp_w/2-halfx;
    float y1 = disp_h/2 - halfy;

    float x2 = disp_w/2 + halfx;
    float y2 = disp_h/2 + halfy;

    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(153, 255, 51));

    float x1h=x1;
    for(int i=0; i<w;i++){
        x1h+=i*a;

        al_draw_line(x1h,y1, x1h,y2, al_map_rgb(1,1,1), 3);
    }

    for(int i=0; i<h;i++){
        y1+=i*a;

        al_draw_line(x1, y1, x2, y1, al_map_rgb(1,1,1), 3);
    }
}

/*
    Location* segments - tablica z koordynatami wszystkich segmentów węża, segments[0] to głowa
    int nSegments - liczba segmentów
    float progress - liczba z zakersu 0-1, która określa, w jakim stopniu głowa węża (a konkretnie jej środek) pokonała
        odległość od "wejściowej" krawędzi kratki do krawędzi "wyjściowej", ma znaczenie również dla końcówki ogona
    Location* directions - wektor określający w którą stronę skierowany jest każdy segment
*/  
void Board::draw_snake(Location* segments, int nSegments, float progress, Location* directions){
	
}

/*
    Każdy segment ma dwie zmienne określające jego położenie: loc (location) i dir (direction)
    Zmienna loc określa po której kratce porusza się głowa węża, ale nie precyzuje jej pozycji co do piksela. 
    Aby obliczyć dokładną pozycję głowy należy wykorzystać parametr progress.
*/