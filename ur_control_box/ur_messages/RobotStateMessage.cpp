//
// Created by ub1404 on 15. 8. 18.
//
#include "RobotStateMessage.h"
#include "cmd_utils.h"

namespace ur5_message {

#define BITS_IS_POWER_ON_ROBOT          0
#define BITS_IS_SECURITY_STOPPED        1
#define BITS_IS_EMERGENCY_STOPPED       2
#define BITS_IS_EXTRA_BUTTON_PRESSED    3
#define BITS_IS_POWER_BUTTON_PRESSED    4
#define BITS_IS_SAFETY_SIGNAL_XXX       5
#define BITS_IS_ROBOT_CONNECTED         6

    bool RobotStateMessage::serialize(ByteBuffer *msg_out) {
        //load robot mode
        msg_out->load(robot_mode);
        msg_out->load(robot_time);
        //load safety signals
        uint8_t safety_flags_bits;
        safety_flags_bits = this->get_flags_in_byte();
        msg_out->load(safety_flags_bits);

        //
        msg_out->load(tcp_force_scalar);
        msg_out->load(tcp_power);
        msg_out->load(tcp_payload);
        msg_out->load(tcp_payload_cog[0]);
        msg_out->load(tcp_payload_cog[1]);
        msg_out->load(tcp_payload_cog[2]);
        msg_out->load(power);

        //
        msg_out->load(digital_inputs);
        msg_out->load(digital_outpus);

        //
        for (int i = 0; i < 6; i++) {
            msg_out->load(joint_modes[i]);
            msg_out->load(q_actual[i]);
            msg_out->load(qd_actual[i]);
            msg_out->load(i_actual[i]);
            msg_out->load(q_target[i]);
            msg_out->load(qd_target[i]);
            msg_out->load(qdd_target[i]);
            msg_out->load(i_target[i]);
            msg_out->load(moment_target[i]);
            msg_out->load(tcp_force[i]);
            msg_out->load(tcp_speed[i]);
            msg_out->load(tcp_wrench[i]);
            msg_out->load(tcp_pose[i]);
        }
        return true;
    }

    bool RobotStateMessage::__deserialize(ByteBuffer *msg_in) {
        if (msg_in->getRemainedBufferSize() != this->getByteLength()) {
            return false;
        }
        //load robot mode
        msg_in->unload(robot_mode);
        msg_in->unload(robot_time);

        //load safety signals
        uint8_t safety_flags_bits;
        msg_in->unload(safety_flags_bits);
        unload_flags(safety_flags_bits);

        //
        msg_in->unload(tcp_force_scalar);
        msg_in->unload(tcp_power);
        msg_in->unload(tcp_payload);
        msg_in->unload(tcp_payload_cog[0]);
        msg_in->unload(tcp_payload_cog[1]);
        msg_in->unload(tcp_payload_cog[2]);
        msg_in->unload(power);

        //
        msg_in->unload(digital_inputs);
        msg_in->unload(digital_outpus);

        //
        for (int i = 0; i < 6; i++) {
            msg_in->unload(joint_modes[i]);
            msg_in->unload(q_actual[i]);
            msg_in->unload(qd_actual[i]);
            msg_in->unload(i_actual[i]);
            msg_in->unload(q_target[i]);
            msg_in->unload(qd_target[i]);
            msg_in->unload(qdd_target[i]);
            msg_in->unload(i_target[i]);
            msg_in->unload(moment_target[i]);
            msg_in->unload(tcp_force[i]);
            msg_in->unload(tcp_speed[i]);
            msg_in->unload(tcp_wrench[i]);
            msg_in->unload(tcp_pose[i]);
        }
        return true;
    }

    uint8_t RobotStateMessage::get_flags_in_byte() {
        uint8_t temp = 0x00;
        SET_BIT_COND(temp, is_power_on_robot, BITS_IS_POWER_ON_ROBOT);
        SET_BIT_COND(temp, is_security_stopped, BITS_IS_SECURITY_STOPPED);
        SET_BIT_COND(temp, is_emergency_stopped, BITS_IS_EMERGENCY_STOPPED);
        SET_BIT_COND(temp, is_extra_button_pressed, BITS_IS_EXTRA_BUTTON_PRESSED);
        SET_BIT_COND(temp, is_power_button_pressed, BITS_IS_POWER_BUTTON_PRESSED);
        SET_BIT_COND(temp, is_safety_signal_such_that_we_should_stop, BITS_IS_SAFETY_SIGNAL_XXX);
        SET_BIT_COND(temp, is_robot_connected, BITS_IS_ROBOT_CONNECTED);
        return temp;
    }

    void RobotStateMessage::unload_flags(uint8_t data) {
        is_power_on_robot = GET_BIT(data, BITS_IS_POWER_ON_ROBOT);
        is_security_stopped = GET_BIT(data, BITS_IS_SECURITY_STOPPED);
        is_emergency_stopped = GET_BIT(data, BITS_IS_EMERGENCY_STOPPED);
        is_extra_button_pressed = GET_BIT(data, BITS_IS_EXTRA_BUTTON_PRESSED);
        is_power_button_pressed = GET_BIT(data, BITS_IS_POWER_BUTTON_PRESSED);
        is_safety_signal_such_that_we_should_stop = GET_BIT(data, BITS_IS_SAFETY_SIGNAL_XXX);
        is_robot_connected = GET_BIT(data, BITS_IS_ROBOT_CONNECTED);
    }

    void RobotStateMessage::initAttributes() {
        this->robot_mode = ROBOT_NO_POWER_MODE;
        this->robot_time = 0.0;
        this->is_robot_connected = false;
        this->is_power_on_robot = false;
        this->is_security_stopped = false;
        this->is_emergency_stopped = false;
        this->is_extra_button_pressed = false;
        this->is_power_button_pressed = false;
        this->is_safety_signal_such_that_we_should_stop = false;

        for (int i = 0; i < 6; i++) {
            this->joint_modes[i] = JOINT_POWER_OFF_MODE;
            this->q_actual[i] = 0.0;
            this->qd_actual[i] = 0.0;
            this->i_actual[i] = 0.0;
            this->q_target[i] = 0.0;
            this->qd_target[i] = 0.0;
            this->qdd_target[i] = 0.0;
            this->i_target[i] = 0.0;
            this->moment_target[i] = 0.0;
            this->tcp_force[i] = 0.0;
            this->tcp_speed[i] = 0.0;
            this->tcp_wrench[i] = 0.0;
            this->tcp_pose[i] = 0.0;
        }

        this->tcp_force_scalar = 0.0;
        this->tcp_power = 0.0;
        this->tcp_payload = 0.0;
        this->tcp_payload_cog[0] = 0.0;
        this->tcp_payload_cog[1] = 0.0;
        this->tcp_payload_cog[2] = 0.0;
        this->power = 0.0;
        this->digital_inputs = 0;
        this->digital_outpus = 0;
    }

    RobotStateMessage RobotStateMessage::makeDummy() {
        this->robot_mode = 10;
        this->robot_time = 0.124;
        this->is_robot_connected = true;
        this->is_emergency_stopped = false;
        this->is_power_on_robot = false;
        this->is_security_stopped = true;
        this->is_power_button_pressed = true;
        this->is_safety_signal_such_that_we_should_stop = false;
        for (int i = 0; i < 6; i++) {
            this->joint_modes[i] = i + 1.23456;
            this->q_actual[i] = i + 5.23456;
            this->qd_actual[i] = i + 2.23456;
            this->i_actual[i] = i - 0.1234;
            this->q_target[i] = i;
            this->qd_target[i] = i + 1.2;
            this->qdd_target[i] = i * 1.234;
            this->i_target[i] = 5.0;
            this->moment_target[i] = 6.0;
            this->tcp_force[i] = 1.234 * i;
            this->tcp_speed[i] = 3.141592;
            this->tcp_wrench[i] = i * i;
            this->tcp_pose[i] = i + i;
        }
        this->tcp_force_scalar = 1.0;
        this->tcp_power = 3.141592;
        this->tcp_payload = 1.033333;
        this->tcp_payload_cog[0] = 1.0;
        this->tcp_payload_cog[1] = 2.0;
        this->tcp_payload_cog[2] = 3.0;
        this->power = 1.234;
        this->digital_inputs = 3;
        this->digital_outpus = 0x17;
    }

    bool RobotStateMessage::operator!=(const RobotStateMessage &A) {
        return !operator==(A);
    }

    bool RobotStateMessage::operator==(const RobotStateMessage &A) {
        if (robot_mode != A.robot_mode) {
            return false;
        }
        if (!compareDoubles(robot_time, A.robot_time)) {
            return false;
        }
        if (is_robot_connected != A.is_robot_connected) {
            return false;
        }
        if (is_power_on_robot != A.is_power_on_robot) {
            return false;
        }
        if (is_security_stopped != A.is_security_stopped) {
            return false;
        }
        if (is_emergency_stopped != A.is_emergency_stopped) {
            return false;
        }
        if (is_extra_button_pressed != A.is_extra_button_pressed) {
            return false;
        }
        if (is_power_button_pressed != A.is_power_button_pressed) {
            return false;
        }
        if (is_safety_signal_such_that_we_should_stop != A.is_safety_signal_such_that_we_should_stop) {
            return false;
        }
        if (digital_inputs != A.digital_inputs) {
            return false;
        }
        if (digital_outpus != A.digital_outpus) {
            return false;
        }

        for (int i = 0; i < 6; i++) {
            if (joint_modes[i] != A.joint_modes[i]) {
                return false;
            }
            if (!compareDoubles(q_actual[i], A.q_actual[i])) {
                return false;
            }
            if (!compareDoubles(qd_actual[i], A.qd_actual[i])) {
                return false;
            }
            if (!compareDoubles(i_actual[i], A.i_actual[i])) {
                return false;
            }
            if (!compareDoubles(q_target[i], A.q_target[i])) {

                return false;
            }
            if (!compareDoubles(qd_target[i], A.qd_target[i])) {
                return false;
            }
            if (!compareDoubles(qdd_target[i], A.qdd_target[i])) {
                return false;
            }
            if (!compareDoubles(i_target[i], A.i_target[i])) {
                return false;
            }
            if (!compareDoubles(moment_target[i], A.moment_target[i])) {
                return false;
            }
            if (!compareDoubles(tcp_force[i], A.tcp_force[i])) {
                return false;
            }
            if (!compareDoubles(tcp_speed[i], A.tcp_speed[i])) {
                return false;
            }
            if (!compareDoubles(tcp_wrench[i], A.tcp_wrench[i])) {
                return false;
            }
            if (!compareDoubles(tcp_pose[i], A.tcp_pose[i])) {
                return false;
            }
        }
        if (!compareDoubles(tcp_force_scalar, A.tcp_force_scalar)) {
            return false;
        }
        if (!compareDoubles(tcp_power, A.tcp_power)) {
            return false;
        }
        if (!compareDoubles(tcp_payload, A.tcp_payload)) {
            return false;
        }
        if (!compareDoubles(tcp_payload_cog[0], A.tcp_payload_cog[0])) {
            return false;
        }
        if (!compareDoubles(tcp_payload_cog[1], A.tcp_payload_cog[1])) {
            return false;
        }
        if (!compareDoubles(tcp_payload_cog[2], A.tcp_payload_cog[2])) {
            return false;
        }
        if (!compareDoubles(power, A.power)) {
            return false;
        }
        return true;
    }
}
