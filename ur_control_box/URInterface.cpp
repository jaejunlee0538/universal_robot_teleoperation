//
// Created by ub1404 on 15. 8. 18.
//

#include "URInterface.h"
#include "RobotinterfaceWrapper.h"
#include "ConfigurationWrapper.h"
#include "ur_c_api/microprocessor_commands.h"
#include "ur_c_api/microprocessor_definitions.h"

#include <unistd.h>
#include <sched.h>
#include <errno.h>

#include <sys/time.h>
#define USE_MATH_DEFINES
#include <math.h>

namespace ur_control_box {
    const double HOME_POSITION[6] = {0.0, -1.570796, 0.0, -1.570796, 0.0, 0.0};
    const double ZERO_VECTOR[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    const double MAX_Q[6] = {2*M_PI, 2*M_PI, 2*M_PI, 2*M_PI, 2*M_PI, 2*M_PI};
    const double MAX_QD[6] = {M_PI, M_PI, M_PI,M_PI, M_PI, M_PI};
    const double MAX_QDD[6] = {15.0, 15.0, 15.0,25.0, 25.0, 25.0};
    const double MAX_TORQUE[6] = {150.0, 150.0, 150.0,28.0, 28.0, 28.0};

    using namespace ur5_message::joint_command::JointCommandTypes;
    using namespace ur5_message::config_command::ConfigCommandsTypes;
    pid_t pid;
    struct sched_param sch_param;

    timeval t0, t1, t_elapsed;

    void timeStamp(const char *msg) {
        gettimeofday(&t1, 0);
        timersub(&t1, &t0, &t_elapsed);
        printf("\t[%10.3lf] : %s\n", t_elapsed.tv_sec + t_elapsed.tv_usec / 1000000.0, msg);
    }

#define PRINT_TIME_STAMP(msg) timeStamp(msg)

    URInterface::URInterface() {
        gettimeofday(&t0, 0);
        loop_count = 0;
    }

    bool URInterface::init() {
        for(int i=0;i<6;i++)
        {
            joint_p_controller[i].init(1.0, -MAX_Q[i], MAX_Q[i], 0.25*MAX_QD[i], 5.0);
        }

        if (!server_sock.init(UR_COMM_PORT)) {
            LOG_ERROR("URInterface init failed");
            return false;
        }
        ur_comm.setSocket(&server_sock);

        ur_comm.registerMessageType(
                CONFIG_COMMAND,
                &msg_config_cmd);
        ur_comm.registerMessageType(
                JOINT_COMMAND,
                &msg_joint_cmd);
        ur_comm.registerMessageType(
                TARGET_JOINT_POSITION_COMMAND,
                &msg_target_joint_pos);
        wrapper_configuration_load();
#ifdef BUILD_REAL_ROBOT

        pid = getpid();
        sch_param.sched_priority = 99;
        if (sched_setscheduler(pid, SCHED_FIFO, &sch_param) == 0) {
            printf("- Prioority set\n");
        } else {
            printf("- Priority not set, error: %i\n", errno);
            return false;
        }
#endif

        return true;
    }

    void URInterface::turnOffRobot() {
        LOG_INFO("Turning off the robot\n");
        if (wrapper_robotinterface_is_robot_connected()) {
            if (wrapper_robotinterface_is_power_on_robot()) {
                LOG_INFO("Power off the robot\n");
                wrapper_robotinterface_power_off_robot();
                sleep(1.0);
            }
            LOG_INFO("Close interface\n");
            wrapper_robotinterface_close();
        }
    }

    void URInterface::controlLoop() {
        updateRobotState();
        sendRobotState();
        readCommands();
        conductCommands();
        extraButtonHandler();

        loop_count++;
    }

    bool URInterface::isConnected() {
        return ur_comm.isConnected();
    }

    void URInterface::readCommands() {
        msg_joint_cmd.reset();
        msg_config_cmd.reset();
        ur_comm.processAllIncomingMessage();
    }

    void URInterface::sendRobotState() {
        ur_comm.sendMessage(ROBOT_STATE, &msg_robot_state);
    }

    void URInterface::conductCommands() {
        if (msg_config_cmd.isMessageUpdated()) {
            conductConfigCommands();
        }

        if (msg_joint_cmd.isMessageUpdated()) {
            conductJointCommands();
        }else{
            wrapper_robotinterface_command_empty_command();
        }

    }

    void URInterface::updateRobotState() {
        wrapper_robotinterface_read_state_blocking();
        msg_robot_state.is_robot_connected =
                wrapper_robotinterface_is_robot_connected();

        if (!msg_robot_state.is_robot_connected) {
            return;
        }

        msg_robot_state.robot_mode =
                wrapper_robotinterface_get_robot_mode();
        msg_robot_state.robot_time =
                wrapper_robotinterface_get_time();

        msg_robot_state.is_power_on_robot =
                wrapper_robotinterface_is_power_on_robot();
        msg_robot_state.is_emergency_stopped =
                wrapper_robotinterface_is_emergency_stopped();
        msg_robot_state.is_power_button_pressed =
                wrapper_robotinterface_is_power_button_pressed();
        msg_robot_state.is_extra_button_pressed =
                wrapper_robotinterface_is_extra_button_pressed();
        msg_robot_state.is_security_stopped =
                wrapper_robotinterface_is_security_stopped();
        msg_robot_state.is_safety_signal_such_that_we_should_stop =
                wrapper_robotinterface_is_safety_signal_such_that_we_should_stop();

        for (int i = 0; i < 6; i++) {
            msg_robot_state.joint_modes[i] =
                    wrapper_robotinterface_get_joint_mode(i);
        }

        wrapper_robotinterface_get_actual(
                msg_robot_state.q_actual,
                msg_robot_state.qd_actual);
        wrapper_robotinterface_get_target(
                msg_robot_state.q_target,
                msg_robot_state.qd_target,
                msg_robot_state.qdd_target);
        wrapper_robotinterface_get_actual_current(msg_robot_state.i_actual);
        wrapper_robotinterface_get_target_current(msg_robot_state.i_target);
        wrapper_robotinterface_get_target_moment(msg_robot_state.moment_target);
        wrapper_robotinterface_get_tcp_force(msg_robot_state.tcp_force);
        wrapper_robotinterface_get_tcp_speed(msg_robot_state.tcp_speed);
        wrapper_robotinterface_get_tcp_wrench(msg_robot_state.tcp_wrench);
        wrapper_robotinterface_get_tcp(msg_robot_state.tcp_pose);
        msg_robot_state.tcp_force_scalar =
                wrapper_robotinterface_get_tcp_force_scalar();
        msg_robot_state.tcp_power =
                wrapper_robotinterface_get_tcp_power();
        msg_robot_state.tcp_payload =
                wrapper_robotinterface_get_tcp_payload();
        wrapper_robotinterface_get_tcp_payload_cog(
                msg_robot_state.tcp_payload_cog
        );

        msg_robot_state.power = wrapper_robotinterface_get_power();

        msg_robot_state.digital_inputs =
                wrapper_robotinterface_get_actual_digital_input_bits();

        msg_robot_state.digital_outpus =
                wrapper_robotinterface_get_actual_digital_output_bits();
    }

    void URInterface::conductConfigCommands() {
        if (msg_config_cmd.isCommandSet(OPEN_INTERFACE)) {
            wrapper_robotinterface_open(0);
        }

        if (msg_config_cmd.isCommandSet(CLOSE_INTERFACE)) {
            wrapper_robotinterface_close();
        }

        if (msg_config_cmd.isCommandSet(POWER_ON_ROBOT)) {
            wrapper_robotinterface_power_on_robot();
        }

        if (msg_config_cmd.isCommandSet(POWER_OFF_ROBOT)) {
            wrapper_robotinterface_power_off_robot();
        }

        if (msg_config_cmd.isCommandSet(SET_ROBOT_READY_MODE)) {
            wrapper_robotinterface_set_robot_ready_mode();
        }

        if (msg_config_cmd.isCommandSet(SET_ROBOT_RUNNING_MODE)) {
            wrapper_robotinterface_set_robot_running_mode();
        }

        if (msg_config_cmd.isCommandSet(SET_ROBOT_FREEDRIVE_MODE)) {
            wrapper_robotinterface_set_robot_freedrive_mode();
        }

        if (msg_config_cmd.isCommandSet(SET_SECURITY_STOP)) {
            wrapper_robotinterface_security_stop();
        }

        if (msg_config_cmd.isCommandSet(UNLOCK_SECURITY_STOP)) {
            wrapper_robotinterface_unlock_security_stop();
        }
    }

    void URInterface::conductJointCommands() {
        switch(msg_joint_cmd.cmd_type){
            case PVA_COMMAND:
                wrapper_robotinterface_command_position_velocity_acceleration(
                        msg_joint_cmd.q,
                        msg_joint_cmd.qd,
                        msg_joint_cmd.qdd
                );
                break;
            case VEL_COMMAND:
                wrapper_robotinterface_command_velocity(msg_joint_cmd.qd);
                break;
            case TORQUE_COMMAND:
                wrapper_robotinterface_command_torque(
                        msg_joint_cmd.qd,
                        msg_joint_cmd.security_torque,
                        msg_joint_cmd.torque
                );
                break;
            default:
                LOG_WARN("Undefined joint command(%d)", msg_joint_cmd.cmd_type);
                wrapper_robotinterface_command_empty_command();
                break;
        }
    }

    void URInterface::extraButtonHandler(){
        if(msg_robot_state.is_extra_button_pressed){
            if(msg_robot_state.robot_mode != ROBOT_FREEDRIVE_MODE) {
                if(isJointsMoving()){
                    LOG_WARN("Cannot begin FREEDRIVE when joints are moving.");
                    return;
                }
                wrapper_robotinterface_set_robot_freedrive_mode();
            }
        }else{
            if(msg_robot_state.robot_mode == ROBOT_FREEDRIVE_MODE){
                wrapper_robotinterface_set_robot_running_mode();
            }
        }
    }

    bool URInterface::isJointsMoving(){
        for(size_t i=0;i<6;i++){
            if(fabs(msg_robot_state.qd_actual[i]) > 0.00001){
                return true;
            }
        }
        return false;
    }

}