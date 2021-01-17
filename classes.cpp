#include "classes.h"

#include<assert.h>
#include<cmath>
#include<time.h>
#include<cstdlib>
#include<stdio.h>
#include<assert.h>
#include<stddef.h>
#include<fstream>

Snake::Snake(Location loc, float spd, int FPS)
{
	srand(time(NULL));// create a snake and place it in the center of the board facing a random direction
	
	speed = spd;
	set_steps(speed, FPS);
	steps_i = steps/2;

	head.InitHead(loc);
	Location shift = parse_dir(rand()%4);
	head.set_dir(shift);
	
	for(int i=0; i<3;i++){
		segments[i].InitBody(loc+shift*i*(-1), shift);
	}
}



void Snake::set_steps(float speed, int FPS){
	steps = FPS/speed;
	step_threshold = steps*0.75;
}

void Snake::step(){
	steps_i++;
	if(steps_i>steps) {
		move();
		steps_i=1;
	}
	else if(steps_i==step_threshold) head.set_dest(head.getLoc()+head.get_dir());
}

void Snake::grow()
{
	if (nSegments < nSegmentsMax)
	{	
		segments[nSegments].InitBody(segments[nSegments-1].getLoc(), segments[nSegments-1].get_dir());
		
		nSegments++;
	}
}

int Snake::game_over(Board brd){
	int over=0;
	Location headLoc=head.getLoc();//TODO: account for head and body size

	if(headLoc.x<0 || headLoc.y<0) over=1;
	else if (headLoc.x>brd.w-1 || headLoc.y>brd.h-1) over=1;
	else {
		for(int i =3; i<nSegments;i++){
			if(headLoc==segments[i].getLoc()) over =1;
		}
	}

	return over;

}

void Snake::draw(Board* brd) 
{
	Location *coords = new Location [nSegments];
	Location *directions = new Location [nSegments];

	directions[0]=head.get_dir();
	coords[0]= head.getLoc();


	for(int i=1; i<nSegments;i++){
		coords[i]= segments[i].getLoc();
		directions[i]= segments[i].get_dir();
	}

	brd->draw_board();
	brd->draw_snake(coords, nSegments, (float)(steps_i/steps), directions);
}

void Snake::move(){
	if(segments[nSegments-1].getLoc()+segments[nSegments-1].get_dir()*(-1)!=segments[nSegments-2].getLoc()){
		segments[nSegments-1].set_dir(segments[nSegments-2].get_dir()*(-1));
	}
	
	for(int i=nSegments-1; i>0;i--){
		segments[i].Follow(segments[i-1]);
	}

	segments[0].Follow(head);
	head.go_to_dest();

	segments[0].set_dir(head.get_dir());

	for(int i =1; i<nSegments-1; i++){
		segments[i].set_dir(segments[i-1].get_dir());
	}
	
}


void Snake::Segment::set_dir(Location dir){
	

}
//*####### HEAD METHODS #######

void Snake::Head::set_dest(Location delta_dest)
{
	assert(fabs(delta_dest.x) + fabs(delta_dest.y) == 1);
	dest = dest + delta_dest;
}

void Snake::Head::go_to_dest(){
	loc = dest;
}

void Snake::Head::InitHead(Location in_loc)
{
	loc = in_loc;
	// c = Snake::headColor;
}




//* ###### BODY METHODS ######

void Snake::Body::InitBody(Location in_loc, Location in_dir)
{
	loc = in_loc;
	// c = Snake::bodyColor;

	direction=in_dir;
}

void Snake::Body::Follow(Segment next){
	loc = next.getLoc();
}

Location parse_dir(int d){

	Location direction;
		switch (d)
	{
	case 0:
		direction.y=-1;
		break;
	case 1:
		direction.x=1;
		break;
	case 2:
		direction.y = 1;
		break;
	case 3:
		direction.x=-1;
		break;
	default:
		printf("Something went wrong");
		exit(-1);
		break;
	}

	return direction;
}