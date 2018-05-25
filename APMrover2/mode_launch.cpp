#include "mode.h"
#include "Rover.h"

/*
Essentially: On the GCS you enter "LAUNCH MODE" or "LAUNCH CONTROL"
The craft will set the current BEACHED location as "GPS_HOME" 
The craft will then wait for stick input
REVERSE the throttle stick while also input RUDDER direction
The craft will automaticaly reverse, and then 360 turn in the direction of stick input
*/

// CLASS LEVEL steering and throttle variables
float desired_steering, desired_throttle;

bool ModeLaunch::_enter()
{
    // sets current location as home 
    set_home_to_current_location(true);
    
    // wait for reverse command from TX System To start Program
    while (true) {
        get_pilot_desired_steering_and_throttle(desired_steering, desired_throttle); // read throttle stick 
        if(is_negative(desired_throttle)) {
            return true;
        }
    }
}

void ModeLaunch::update()
{
    get_pilot_desired_steering_and_throttle(desired_steering, desired_throttle); // read steering
    float throttle_BACK = -30; // creates throttle variable
    float throttle_TURN = 12; // creates throttle variable
    float steering; // creates throttle variable
    if(is_negative(desired_steering)) {
         steering = -4500;
    }
    else if (!is_negative(desired_steering)) {
         steering = 4500;
    }
    else {
         steering = 0.0;
    }
    time_t start, end, elapsed, count; // creates necessary time objects
    
    //boat runs in reverse at first during Launch mode
    rover.set_reverse(true);
    
    // reverse throttle runs for 6 seconds
    g2.motors.set_throttle(throttle_BACK); // set throttle
    while (elapsed < 6) {
        start = time(0);
        end = time(0);
        count = end - start;
        elapsed = elapsed + count;
    } // timer system (6 seconds) 
   
    //boat runs in forward second during Launch mode
    rover.set_reverse(false);
    
    g2.motors.set_steering(steering, false);
    g2.motors.set_throttle(throttle_TURN);
    while (elapsed < 3) {
        start = time(0);
        end = time(0);
        count = end - start;
        elapsed = elapsed + count;
    } // timer system (3 seconds)
    
    control_mode(&mode_manual); //switches to manual control
    
}

void ModeLaunch::_exit()
{
    // stops vehicle all together & centers steering
    stop_vehicle();
    g2.motors.set_steering(0.0f);
    
    // sets rover back to forward
    rover.set_reverse(false);
}
