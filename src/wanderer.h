#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 

#include "enviro.h"

using namespace enviro;

// The below class dictates the behavior of the wall following bot in its "Forward Moving" state
// Behavior is determined by using the front and right facing sensors.
class MovingForward : public State, public AgentInterface {
    void entry(const Event& e) {
        std::cout << "MOVING FORWARD" << "\n";
    }
    void during() {
        // Check for if the bot is too far from the wall and not about to hit the wall in the front
        if ( sensor_value(1) >= 10 and sensor_value(0) >= 10) {
                emit(Event("right"));
        }
        // Check if the bot is about to hit a wall in front
        if (sensor_value(0) < 15) {
                emit(Event("left"));
        }
        track_velocity(10, 0);
    }
    void exit(const Event& e) {}
};


// The below class dictates the behavior of the wall following bot in its "Right rotation" state
class RotatingRight : public State, public AgentInterface {
    void entry(const Event& e) {
        std::cout << "Right" << "\n";
    }
    void during() {
        // Check if the wall is sufficiently close
        if (sensor_value(1) <= 12 and sensor_value(0) >= 20) {
                emit(Event("tick"));
        }
        // Check if the wall is in front of the bot
        if (sensor_value(0) < 8) {
                emit(Event("left"));
        }
        
        track_velocity(1,2);
    }
    void exit(const Event& e) {}
};

// The below class dictates the behavior of the wall following bot in its "Left rotation" state
class RotatingLeft : public State, public AgentInterface {
    void entry(const Event& e) {
        std::cout << "Left" << "\n";
    }
    void during() {
        // Check if the bot is sufficiently far from the wall to the right and in front
        if (sensor_value(1) <= 12 and sensor_value(0) >= 20) {
                emit(Event("tick"));
        }
        // Check if the bot is too far from the wall and there is space in front
        if ( sensor_value(1) >= 15 and sensor_value(0) >= 20) {
                emit(Event("right"));
        }
        track_velocity(1,-3);
    }
    void exit(const Event& e) {}
};
class WandererController : public StateMachine, public AgentInterface {

    public:
        WandererController() : StateMachine() {
            set_initial(moving_forward);
            // Set all state transitions
            add_transition("right", moving_forward, right);
            add_transition("left", moving_forward, left);
            add_transition("tick", left, moving_forward);
            add_transition("tick", right, moving_forward);
            add_transition("left", right, left);
            add_transition("right", left, right);
        }
        
        void update() {
            // Say "you win!" and reset the robot when it completes the maze
            if(position().x > 160 and position().y < -160) {
                std::cout << "You win!" << "\n";
                teleport(-180,180,-1.6);
            }
            StateMachine::update();
        }
        MovingForward moving_forward;
        RotatingRight right;
        RotatingLeft left;
        

};

class Wanderer : public Agent {
    public:
    Wanderer(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    WandererController c;
};


DECLARE_INTERFACE(Wanderer)

#endif