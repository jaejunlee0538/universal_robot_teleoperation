//
// Created by ub1404 on 16. 11. 15.
//

#include <haptics/haptic_devices/Button.h>

Button::Button() {
    reset();
}

void Button::reset(){
    btn = BUTTON_UNKNOWN;
    btn_changes = NO_CHANGE;
}

void Button::update(bool pressed) {
    ButtonStates state =pressed ? BUTTON_ON : BUTTON_OFF;
    if (btn != BUTTON_UNKNOWN) {
        //Do not run at first time
        if (btn == state)
            btn_changes = NO_CHANGE;
        else {
            if (state == BUTTON_ON)
                btn_changes = OFF_TO_ON;
            else
                btn_changes = ON_TO_OFF;
        }
    }
    this->btn = state;
}

bool Button::isPressed() const{
    return btn == BUTTON_ON;
}

int Button::edge() const{
    return btn_changes;
}


int Button::state() const{
    return btn;
}