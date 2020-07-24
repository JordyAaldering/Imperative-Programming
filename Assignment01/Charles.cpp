#include "Robot.h"
/*
	Karel is a framework for manipulating with Karel the robot.
	Karel is a subclass of ROBOT from the library Robot.
	Last Modified:	September 16 2006, by Pieter Koopman, RU Nijmegen
	With some additions: September 12 2007, by Ger Paulussen & Peter Achten
	More additions: August 21 2013, by Peter Achten
*/


// =========================================================================

// Here are the examples that have been explained during the lecture
void take_3_steps ()
{
    step () ;
    step () ;
    step () ;
}

void swap_ball ()
{
    if (on_ball ())
        get_ball () ;
    else
	    put_ball () ;
    step () ;
}

// put_a_ball_somewhere adds a single ball to Charles' world on a random location
void put_a_ball_somewhere ()
{
    int lane   = 1 + rand () % (WereldHoogte  - 2) ;
    int street = 1 + rand () % (WereldBreedte - 2) ;
    create_ball (street, lane) ;
}

// make_church creates a Church-like shape of walls
void make_church ()
{
    place_rectangle (10,10,20,8) ;
    place_rectangle (10,18, 4,4) ;
    place_walls (12,22,4,false) ;
    place_walls (11,25,2,true) ;
}

// make_block creates an arbitrary block inside Charles' world and places a ball
// on the 'north' most lane at the 'west' most street corner.
void make_block ()
{
    const int left   = rand () % (WereldBreedte / 3) + 5;
    const int bottom = rand () % (WereldHoogte  / 4) + 5;
    const int width  = rand () % (WereldBreedte / 2) + 5;
    const int height = rand () % (WereldHoogte  / 2) + 2;
    place_rectangle (left,bottom,width,height) ;
    create_ball (left, WereldHoogte-2) ;
}
// turn_north makes Charles look north
void turn_north ()
{
    while (!north())
        turn_left();
}

void turn_around ()
{
    turn_left() ;
    turn_left() ;
}
// walk_to_wall makes Charles walk ahead and stop immediately before the wall
void walk_to_wall ()
{
    while (!in_front_of_wall())
        step () ;
}

// go_to_north_west_corner makes Charles move to north-west corner and look to the east
// it is assumed that that there are only the exterior walls
void go_to_north_west_corner ()
{
    turn_north() ;
    walk_to_wall() ;
    turn_left() ;
    walk_to_wall() ;
    turn_around() ;
}

// sweep_lane makes Charles walk ahead until it is on top of a ball or immediately before a wall
void sweep_lane ()
{
    while (!on_ball() && !in_front_of_wall())
        step () ;
}

// go_down_east_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing east and is not on the southernmost lane
void go_down_east_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_right() ;
        step() ;
        turn_right() ;
    }
}

// go_down_west_if_not_on_ball moves Charles one lane to the south if he is not on a ball.
// it is assumed that Charles is facing west and is not on the southernmost lane
void go_down_west_if_not_on_ball ()
{
    if (!on_ball())
    {
        turn_left () ;
        step () ;
        turn_left () ;
    }
}

// sweep_lanes makes Charles move to the east and find the ball, followed by
// going on lane south and moving to the west to find the ball.
// Assumptions: Charles is standing at the north-west corner and is looking east, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball
void sweep_lanes ()
{
    while (!on_ball())
    {
        sweep_lane () ;
        go_down_east_if_not_on_ball () ;
        sweep_lane () ;
        go_down_west_if_not_on_ball () ;
    }
}

// This example has been discussed during the lecture
// The effect of this function is that Charles will search for a ball in its universe.
// Assumptions: Charles is standing on its base position, there are only the exterior walls, and a ball is present.
// Result:      Charles is standing on the ball.
void find_ball ()
{
    sweep_lanes () ;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Jordy Aaldering / s1004292 / study student 1 :
// Thomas van Harskamp / s1007576 / study student 2 :

//Function to be called upon to pick up a ball if there is one
void safe_pick_up_ball ()
    {
        if (on_ball ())                 //Check if on a ball
            get_ball ();                //Pick up the ball if there is one
    }

//Function to be called upon to check if there is a wall and to turn if there is a wall
void check_for_wall_and_rotate ()
{
        if (in_front_of_wall())         //Check if in front of a wall
            turn_right();               //Turn right if on a wall
}

void clean_string_with_balls ()
{
	make_string_with_balls () ;

//Repeat the code while there are still balls
	while (on_ball ())
	{
        safe_pick_up_ball();            //Pick up a ball if there is one
        step();                         //Move after picking up a ball, there can never be a wall at this point so there is no need to check for this.
        check_for_wall_and_rotate();    //Rotate if necessary
	}
}

bool stop_now;                          //Boolean used to stop the while loop in "clean_chaos_with_balls.

//Function for when Charles has reached the end
void reached_end ()
{
    turn_around();                      //Turn around to face north
    while (!in_front_of_wall())         //Repeat while not in front of a wall
        step();
    turn_right();                       //Turn right to face east again
    stop_now = true;                    //Boolean is set to true to stop the while loop
}

//Function to check for a wall and to turn in the right direction
void check_for_wall_and_turn ()
{
    if (in_front_of_wall())             //Check if in front of a wall
    {
        turn_left();
        if (north()){                   //Check to see if Charles is facing north, if not he must be facing south
            turn_around();              //Turn to face south
            step();
            turn_right();               //Turn right to point towards the other wall
        }
        else if (in_front_of_wall()){   //If Charles is in front of a wall after turning left he must be at the end
        reached_end();
        }
        else {                          //If Charles is already facing south he can make one step
            step();
            turn_left();                //Turn left to point towards the other wall
        }
    }
}

void clean_chaos_with_balls ()
{
	make_chaos_with_balls () ;

	stop_now = false;                   //Set boolean to false by default
    //Repeat while Charles is not looking north, this only happens at the end.
	while (stop_now == false)
    {
        safe_pick_up_ball();            //Pick up a ball if there is one
        step ();
        safe_pick_up_ball();            //Pick up a ball if there is one
        check_for_wall_and_turn();
	}
}


// this is the initial set-up for the tracing Charles assignment
void tracing_Charles ()
{
    reset () ;
    create_ball (WereldBreedte - 5, WereldHoogte - 3) ;
    steps (WereldBreedte - 5) ;
}
//This is the answer for the tracing Charles assignment
//.OC.OX    <>
//.OC.OX    <4,true>
//.OC.OX    <5>
//.OC.OX    <1,true>
//.OC.OX    <2>
//.Oc.OX    <6>
//.O.cOX    <4,true>
//.O.cOX    <5>
//.O.cOX    <1,false>
//.O.cOX    <3>
//.O.COX    <6>
//.O.OCX    <4,false>

void reach_block () {
    while (!on_ball())
        step();
    turn_right();
    while (!in_front_of_wall())
        step();
    turn_left();
}

//Function to place balls and move around
void place_balls_around_block (){
    put_ball();
    step();

    turn_right();                           //Turn right to face towards the wall
    if (in_front_of_wall())                 //Check if there is a wall or not
        turn_left();                        //Turn left if there is a wall to continue moving along that wall
}

void return_to_start () {
    turn_left();
    while (!in_front_of_wall())
        step();
    turn_left();
    while (!in_front_of_wall())
        step();
    turn_around();
}

void around_the_block ()
{
    make_block () ;

    reach_block();
    while (!on_ball())                      //Function keeps repeating while not on a ball, the function stops when Charles has reached its starting point around the block
        place_balls_around_block();
    return_to_start ();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Charles searches for the ball and remains there
void search_the_ball ()
{
	put_a_ball_somewhere () ;
	find_ball () ;
}

// For testing purposes, you can define your own function here:
void test ()
{
    // enter your Charles code here
}

// end of part with code to be completed by students
// =========================================================================


void quick  () { rest(    1); };
void normal () { rest(dInit); };
void slow   () { rest(  250); };
void very_slow  () { rest( 1000); };

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    Menu charles_menu ((char*)"Charles") ;
    charles_menu.add ((char*)"Clean", reset)
                .add ((char*)"Stop",  stop) ;

	Menu l1_menu ((char*)"Examples Lecture 1");
	l1_menu.add ((char*)"Steps",take_3_steps)
	       .add ((char*)"Swap ball",swap_ball)
	       .add ((char*)"Find ball",search_the_ball);

	Menu a1_menu ((char*)"Assignment 1");
	a1_menu.add ((char*)"Balls: a string...", clean_string_with_balls )
		   .add ((char*)"Balls: chaos...", clean_chaos_with_balls )
		   .add ((char*)"Balls: tracing Charles...", tracing_Charles )
		   .add ((char*)"Bonus: around the block...", around_the_block )
	       .add ((char*)"Test a function",test);

	Menu sn_menu ((char*)"Velocity");
	sn_menu.add ((char*)"Quick", quick)
		   .add ((char*)"Normal",normal)
		   .add ((char*)"Slow",slow)
		   .add ((char*)"Very slow",very_slow);

	try
	{
		karelsWereld().Run (charles_menu,WINARGS(hInstance, hPrevInstance, szCmdLine, iCmdShow));
	}
	catch (IllegaleActie dezeIllegaleActie )
	{
		dezeIllegaleActie.report ();
	}
	catch (...)
	{
		makeAlert ("Something went terribly wrong!");
	}

	return 0;
}
