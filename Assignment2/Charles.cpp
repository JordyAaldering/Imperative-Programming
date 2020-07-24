#include "Robot.h"
/*
	Karel is a framework for manipulating with Karel the robot.
	Karel is a subclass of ROBOT from the library Robot.
	Last Modified:	September 16 2006, by Pieter Koopman, RU Nijmegen
	With some additions: September 12 2007, by Ger Paulussen & Peter Achten
	More additions: August 21 2013, by Peter Achten
*/


// =========================================================================

// make_church creates a Church-like shape of walls
void make_church ()
{
    const int lane   = 2 + rand () % (WereldHoogte / 5) ;
    const int street = 2 + rand () % (WereldBreedte / 5) ;
    const int width  = 3 + rand () % (WereldBreedte / 2) ;
    const int height = 2 + rand () % (WereldHoogte / 3) ;
    place_rectangle (street,lane,width,height) ;
    place_rectangle (street + 2,lane + height, 2 + width / 3, 2 + height / 3) ;
    place_walls (street + 3 + width / 6,lane + height + height / 3 + 3,4,false) ;
    place_walls (street + 2 + width / 6,lane + height + height / 3 + 5,2,true) ;
    create_ball (street, WereldHoogte - 2) ;
}

// safe_put_ball makes Charles put a ball on his current location if it is empty
void safe_put_ball ()
{
    if (!on_ball ())
        put_ball () ;
}

// safe_step makes Charles move one step ahead if not blocked by a wall
void safe_step ()
{
    if (!in_front_of_wall())
        step () ;
}

// balls (n) makes Charles place at most n balls straight ahead (if not blocked by a wall)
// in a safe way (putting balls only on empty spots)
void balls (int no_of_balls)
{
    for (int i = 1 ; i < no_of_balls ; i++)
    {
        safe_put_ball () ;
        safe_step () ;
    }
    if (no_of_balls > 0)
        safe_put_ball () ;
}


////////////////////////////////////////////////////////////////////////// Hansl and Gretl //////////////////////////////////////////////////////////////////////////

// Jordy Aaldering / s1004292 / Informatica                 //I accidentally made Charles pick up the balls in the first assignment because I misunderstood the assignment. We moved this code to the test function if you still want to see it.
// Thomas van Harskamp / s1007576 / Informatica


bool end_reached(false);                                    //a boolean value to determine where the path following function has to stop

void turn_around ()
{
    turn_left();
    turn_left();
}

void face_east ()                                           //a simple function to make Charles face east
{
    while (!north())
        turn_right();
    turn_right();
}

void check_for_ball ()                                      //a function to make Charles check if there is a ball in front of him and, if not so, turn him around
{
    step();
        if (!on_ball())
        {
            turn_around();
            step();
        } else                                              //the else statement is to prevent Charles from taking two steps to the left at once, this could prevent Charles from taking a U-turn to the left
        {
            turn_around();
            step();
            turn_around();
        }
}

void find_path ()
{
    if (in_front_of_wall())                                 //when entering this function, Charles has already faced a wall or is standing on an empty spot
        turn_left();                                        // the first if and else make Charles look to the left of the path at the end of a turn
    else
    {
        turn_around();
        step();
        turn_right();
    }

    if (in_front_of_wall())                                 //consecutively, if Charles faces a wall on the left, his only option left is to the right, therefore Charles is turned around
        turn_around();
    else
        check_for_ball();                                   //likewise, if Charles stands on an empty spot when walking to the left, his only option is to go to the right

    if (in_front_of_wall())                                 //if there is a wall on the right this means Charles has nowhere to go and his path ends here
        end_reached = true;
    else
        step();

    if (!on_ball())                                         //if there is no ball on the right this means Charles has nowhere to go and his path ends here
    {
        turn_around();
        step();
        end_reached = true;
    }
}

void follow_straight_path ()
{
    if (!in_front_of_wall() && on_ball())                   //Charles will continue his straight path until he runs up to a wall or steps on a spot with no ball
        step();
    else
        find_path();                                        //Then he will find the path again with this function, or determine that he reached the end
}

void follow_path ()                                         //in this function Charles will follow the path until he reaches the end  of the balls
{
    while (!end_reached)
        follow_straight_path ();
    face_east();                                           //then he will face east with this function
}

void hansl_and_gretl ()
{
	make_path_with_balls();
	follow_path ();
}


////////////////////////////////////////////////////////////////////////// Cave //////////////////////////////////////////////////////////////////////////


int cycles_done = 0;                                        //integer to see how many cycles have been done

void switch_sides ()                                        //function to switch over to the other side of the cave
{
    cycles_done++;                                          //increase the amount of cycles that have been done by 1
    turn_right();
    while (!in_front_of_wall())                             //keep repeating whilst not in front of a wall
        step();
    turn_right();
    step();
}

void move_to_next ()                                        //function to move over to the next vertical line
{
    step();
    if (in_front_of_wall())                                 //go to switch_sides if Charles has reached the side
        switch_sides();
    turn_right();
}

void make_line ()                                           //function to fill a vertical line with balls
{
    while (!in_front_of_wall())                             //keep repeating whilst not in front of a wall
    {
        put_ball();
        step();
    }
    put_ball();                                             //place one ball next to the wall
}

void return_to_wall ()                                      //function to return to the top or bottom wall afer placing a line of balls
{
    turn_around();                                          //make a 180 degrees turn
    while (!in_front_of_wall())
        step();
    turn_right();
}

void fill_cave_with_balls (int num_of_cycle)                //main function with an integer that indicates on which cycle Charles iss
{
    if (cycles_done == 0)                                   //get Charles in position when no cycles have been done yet
    {
        step();
        turn_right();
    }

    while (cycles_done < num_of_cycle)                      //repeat for one side of the cave
    {
        make_line();
        return_to_wall();
        move_to_next();
    }
}

void cave ()
{
	fill_cave_with_balls (1) ;
	fill_cave_with_balls (2) ;
}

void start_cave ()
{
    make_cave ();
    cave ();
}


////////////////////////////////////////////////////////////////////////// Church /////////////////////////////////////////////////////////////////////////


void walk_to_church ()
{
    while (!on_ball())                                      //move towards the ball that indicates the corner of the church
        step();
    turn_right();                                           //turn right to face towards the church
    while (!in_front_of_wall())                             //move towards the church
        step();
}

void put_ball_down ()                                       //function to place a ball to remember where Charles started
{
    put_ball();
    turn_left();
    if (in_front_of_wall())                                 //turn left if the church is so thin that Charles is immediately in front of a wall
        turn_left();
    step();

}

void walk_around_church ()                                  //function to make Charles walk around the church
{
    while (!on_ball())                                      //keep moving until Charles has reached the ball where he started
    {
        turn_right();
        while (in_front_of_wall())                          //keep turning left if Charles is in front of a wall
            turn_left();
        step();
    }
}

void back_to_start ()                                       //function to get Charles back to where he started
{
    get_ball();
    turn_left();
    while (!in_front_of_wall())                             //make Charles move towards the top wall
        step();
    turn_left();
    while (!in_front_of_wall())                             //make Charles move towards the left wall
        step();
    turn_around();                                          //turn around to face east
}

void rondje_om_de_kerk ()
{
    make_church();
    walk_to_church();
    put_ball_down();
    walk_around_church();
    back_to_start();
}


////////////////////////////////////////////////////////////////////////// Hansl and Gretl Bonus /////////////////////////////////////////////////////////////////////////


bool reached_end_of_line;                                   //boolean to indicate if the end of the line has been reached
int num_of_turn_tries;                                      //integer to see how many times Charles has turned
int steps_to_take;                                          //integer to see how far away Charles is from the last ball
int steps_taken;                                            //integer to see how many steps Charles has already taken back towards the last ball

void safe_get_ball ()                                       //function to only pick up a ball if there is one
{
    if (on_ball())                                          //continue if Charles is on a ball
        get_ball();                                         //pick up the ball
}

void pick_up_line ()                                        //function to pick up a whole line of balls
{
    while (on_ball() && !in_front_of_wall())                //continue whilst Charles is on a ball and not in front of a wall
    {
        safe_get_ball ();
        step();
    }
}

void return_to_line ()                                      //function to return to the last point of the line after checking for a new line
{
    turn_around();
    step();
    turn_around();
}

void check_for_return_to_line ()                            //function to check if return_to_line has to be used
{
    if (on_ball() && in_front_of_wall())                    //check if Charles in on a ball and in front of a wall
        safe_get_ball();
    else                                                    //else it is okay to use the function return_to_line
        return_to_line();
}

void cross_hole ()                                          //function to check if there is a hole in the line
{
    steps_to_take = 0;                                      //set steps_to_take to 0 by default
    turn_right();                                           //turn right to face the right direction after checking for a new line

    while (!on_ball() && !reached_end_of_line)              //continue while Charles is not on a ball and has not reached the end
    {
        step();
        steps_to_take++;                                    //increase steps_to_take by 1 (used for returning to the last point if necessary
        if (in_front_of_wall())                             //continue whilst Charles is not in front of a wall
            reached_end_of_line = true;                     //if Charles has reached a wall this means he has reached the end of the whole line
    }
}

void make_turn ()                                           //function used to make a turn and check in which direction the line continues
{
    num_of_turn_tries = 0;                                  //set num_of_turn_tries to 0 by default

    while (!on_ball() && !reached_end_of_line)              //continue trying while Charles is not on a ball and has not reached the end of the line
    {
        if (num_of_turn_tries < 3)                          //continue whilst Charles has not yet tried all other 3 directions
        {
            turn_right();
            if (!in_front_of_wall())                        //continue if Charles is not in front of a wall, the line can't continue through a wall
            {
                step();
                if (!on_ball())                             //continue if Charles is still not on a ball after turning
                {
                    return_to_line();
                    num_of_turn_tries++;                    //increase the number of tries by 1
                }
            }
        }
        if (num_of_turn_tries == 3)                         //if Charles has tried 3 times there must be a hole or Charles must have reached the end of the whole line
            cross_hole();
    }
}

void goto_end_pos ()                                        //function to send Charles to the position where he is supposed to end (on the last ball facing east)
{
    steps_taken = 0;
    turn_around();                                          //turn around to face towards the last ball

    while (steps_taken < steps_to_take)                     //continue whilst Charles has not yet taken enough steps
    {
        step();
        steps_taken++;                                      //increase steps_taken by 1
    }

    while (!north())                                        //after reaching the right position check if Charles is facing north
        turn_right();                                       //keep turning right until Charles is facing north
    turn_right();                                           //turn 1 more time to face east
}

void follow_path_bonus ()                                   //main function
{
    reached_end_of_line = false;                            //set reached_end_of_line to false by default

    while (!reached_end_of_line)                            //repeat whilst Charles has not yet reached the end of the line
    {
        pick_up_line();
        check_for_return_to_line();
        make_turn();
    }

    goto_end_pos();
}

void test ()
{
    make_path_with_balls() ;
	follow_path_bonus() ;
}


////////////////////////////////////////////////////////////////////////// End //////////////////////////////////////////////////////////////////////////


void quick  () { rest(    0.001); };
void normal () { rest(dInit); };
void slow   () { rest(  250); };
void very_slow  () { rest( 1000); };

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    Menu charles_menu ((char*)"Charles") ;
    charles_menu.add ((char*)"Clean", reset)
                .add ((char*)"Stop",  stop) ;

	Menu a1_menu ((char*)"Assignment 2");
	a1_menu.add ((char*)"Hansl and Gretl", hansl_and_gretl )
		   .add ((char*)"Cave", start_cave )
		   .add ((char*)"Bonus: rondje om de kerk...", rondje_om_de_kerk )
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
