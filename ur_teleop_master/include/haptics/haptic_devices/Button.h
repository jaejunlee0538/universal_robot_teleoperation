/*
 * Created by JaeJunLee 2016.11.15
 */

#ifndef UR_TELEOP_MASTER_BUTTON_H
#define UR_TELEOP_MASTER_BUTTON_H

class Button {
public:
    enum ButtonStates {
        BUTTON_ON = 1,
        BUTTON_OFF = 0,
        BUTTON_UNKNOWN = 100
    };

    enum Changes {
        NO_CHANGE = 0,
        ON_TO_OFF = -1,
        OFF_TO_ON = 1,
    };

    Button();

    /*
     * reset button state.
     * set button state to BUTTON_UNKNOWN and edge to NO_CHANGE
     */
    void reset();

    /*
     * Update button state(Pressed or Released)
     */
    void update(bool pressed);

    /*
     * return transition of the button's state.
     *   On->Off : ON_TO_OFF
     *   Off->On : OFF_TO_ON
     *   On->On  : NO_CHANGE
     *   Off->Off: NO_CHANGE
     */
    int edge() const;

    /*
     * return current state of the button(ON or OFF).
     * return BUTTON_UNKNOWN before the first update call.
     */
    int state() const;
protected:
    ButtonStates btn;
    Changes btn_changes;
};

#endif //UR_TELEOP_MASTER_BUTTON_H
