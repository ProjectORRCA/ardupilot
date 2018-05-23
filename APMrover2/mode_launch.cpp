#include "mode.h"
#include "Rover.h"

bool ModeLaunch::_enter()
{
    // sets current location as home 
    set_home_to_current_location(true);
        
    // steering and throttle variabls
    float desired_steering, desired_throttle;
    
    // wait for reverse command from TX System To start Program
    while (true) {
    get_pilot_desired_steering_and_throttle(desired_steering, desired_throttle); // read throttle stick
    if(is_negative(desired_throttle) {
        return true;
        break;
    }
    }
}

void ModeLaunch::update()
{
    float throttle_BACK = -40; // creates throttle variable
    float throttle_TURN = 20; // creates throttle variable
    float steering = 4500; // creates throttle variable
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
    } // timer system (6 seconds)
    
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
