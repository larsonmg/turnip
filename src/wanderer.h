#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 

#include "enviro.h"

using namespace enviro;


class MovingForward : public State, public AgentInterface {
    void entry(const Event& e) {
        std::cout << "MOVING FORWARD" << "\n";
    }
    void during() {
        if ( sensor_value(1) >= 10 and sensor_value(0) >= 10) {
                emit(Event("right"));
        }
        if (sensor_value(0) < 15) {
                emit(Event("left"));
        }
        track_velocity(10, 0);
    }
    void exit(const Event& e) {}
};

class RotatingRight : public State, public AgentInterface {
    void entry(const Event& e) {
        std::cout << "Right" << "\n";
        cycles = 0;
    }
    void during() {
        if (sensor_value(1) <= 12 and sensor_value(0) >= 20) {
                emit(Event("tick"));
        }
        if (sensor_value(0) < 8) {
                emit(Event("left"));
        }
        
        track_velocity(1,2);
        cycles++;
    }
    void exit(const Event& e) {}
    int cycles;
};

class RotatingLeft : public State, public AgentInterface {
    void entry(const Event& e) {
        std::cout << "Left" << "\n";
        cycles = 0;
    }
    void during() {
        if (sensor_value(1) <= 12 and sensor_value(0) >= 20) {
                emit(Event("tick"));
        }
        if ( sensor_value(1) >= 15 and sensor_value(0) >= 20) {
                emit(Event("right"));
        }
        track_velocity(1,-3);
        cycles++;
    }
    void exit(const Event& e) {}
    int cycles;
};
class WandererController : public StateMachine, public AgentInterface {

    public:
        WandererController() : StateMachine() {
            set_initial(moving_forward);
            add_transition("right", moving_forward, right);
            add_transition("left", moving_forward, left);
            add_transition("tick", left, moving_forward);
            add_transition("tick", right, moving_forward);
            add_transition("left", right, left);
            add_transition("right", left, right);
        }

        void update() {
            
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