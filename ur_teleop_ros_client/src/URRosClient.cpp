//
// Created by ub1404 on 16. 11. 14.
//

#include <ros_client/URRosClient.h>
#include <sensor_msgs/JointState.h>
#include <ur_teleop_messages/URState.h>
#include <ur_messages/ConfigCommandMessage.h>
#include <ur_messages/JointCommandMessage.h>
URRosClient::URRosClient(){

}

void URRosClient::initTopics(ros::NodeHandle& nh, const std::string& joint_state_topic, const std::string& robot_state_topic,
const std::string& joint_command_topic, const std::string& config_command_topic){
    ROS_INFO("Initializing URRosClient");
    joint_command.reset();
    config_command.reset();
    joint_state_publisher = nh.advertise<sensor_msgs::JointState>(joint_state_topic,10);
    robot_state_publisher = nh.advertise<ur_teleop_messages::URState>(robot_state_topic,10);
    joint_command_subscriber = nh.subscribe(joint_command_topic, 10, &URRosClient::jointCommandCallback, this);
    config_command_subscriber = nh.subscribe(config_command_topic, 10, &URRosClient::configCommandCallback, this);
}

bool URRosClient::stateCallback(ur5_message::RobotStateMessage robot_state){
    ROS_DEBUG("URState callback(%.3lf)",robot_state.robot_time);
    publishJointState(robot_state);
    publishRobotState(robot_state);
    boost::mutex::scoped_lock lock(command_lock);
    if(joint_command){
        ROS_DEBUG("Sending a joint command to Universal Robot");
        ur5_message::JointCommandMessage joint_command_packet;
        switch (joint_command->cmd_type){
            case ur5_message::JointCommandTypes::VEL_COMMAND:
                joint_command_packet.cmd_type = ur5_message::JointCommandTypes::VEL_COMMAND;
                for(size_t i=0;i<6;i++) {
                    joint_command_packet.qd[i] = joint_command->qd[i];
                }
                break;
            case ur5_message::JointCommandTypes::PVA_COMMAND:
                joint_command_packet.cmd_type = ur5_message::JointCommandTypes::PVA_COMMAND;
                for(size_t i=0;i<6;i++) {
                    joint_command_packet.q[i] = joint_command->q[i];
                    joint_command_packet.qd[i] = joint_command->qd[i];
                    joint_command_packet.qdd[i] = joint_command->qdd[i];
                }
                break;
            case ur5_message::JointCommandTypes::TORQUE_COMMAND:
                joint_command_packet.cmd_type = ur5_message::JointCommandTypes::TORQUE_COMMAND;
                for(size_t i=0;i<6;i++) {
                    joint_command_packet.torque[i] = joint_command->torque[i];
                }
                break;
            default:
                ROS_WARN("Undefined joint command has been received(type : %d)", joint_command->cmd_type);
            case ur5_message::JointCommandTypes::NO_COMMAND:
                joint_command_packet.cmd_type = ur5_message::JointCommandTypes::NO_COMMAND;
        }
        this->sendJointCommand(joint_command_packet);
    }

    if(config_command){
        ROS_DEBUG("Sending a config command to Universal Robot");

        ur5_message::ConfigCommandMessage config_command_packet;
        config_command_packet.reset();
        if(config_command->do_open_interface){
            config_command_packet.setOpenInterface();
        }
        if(config_command->do_close_interface){
            config_command_packet.setCloseInterface();
        }
        if(config_command->do_set_power_off_robot){
            config_command_packet.setPowerOffRobot();
        }
        if(config_command->do_set_robot_freedrive_mode){
            config_command_packet.setRobotFreedriveMode();
        }
        if(config_command->do_set_security_stop){
            config_command_packet.setSecurityStop();
        }
        if(config_command->do_set_robot_running_mode){
            config_command_packet.setRobotRunningMode();
        }
        if(config_command->do_set_robot_ready_mode){
            config_command_packet.setRobotReadyMode();
        }
        this->sendConfigCommand(config_command_packet);
    }
    this->joint_command.reset();
    this->config_command.reset();
}

void URRosClient::jointCommandCallback(const ur_teleop_messages::URJointCommandConstPtr& jnt_command){
    boost::mutex::scoped_lock lock(command_lock);
    this->joint_command = jnt_command;
}

void URRosClient::configCommandCallback(const ur_teleop_messages::URConfigCommandConstPtr& config_command){
    boost::mutex::scoped_lock lock(command_lock);
    this->config_command = config_command;
}

void URRosClient::publishJointState(const ur5_message::RobotStateMessage& robot_state){
    const static char* names[] = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint",
                                  "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};
    sensor_msgs::JointStatePtr joint_state(new sensor_msgs::JointState());
    joint_state->name.push_back(names[0]);
    joint_state->name.push_back(names[1]);
    joint_state->name.push_back(names[2]);
    joint_state->name.push_back(names[3]);
    joint_state->name.push_back(names[4]);
    joint_state->name.push_back(names[5]);

    joint_state->header.frame_id = "UniversalRobot";
    joint_state->header.stamp = ros::Time::now();

    joint_state->position =
            sensor_msgs::JointState::_velocity_type(
                    &robot_state.q_actual[0],&robot_state.q_actual[5]);
    joint_state->velocity =
            sensor_msgs::JointState::_velocity_type(
                    &robot_state.qd_actual[0],&robot_state.qd_actual[5]);
    joint_state->effort.resize(6, 0);
    joint_state_publisher.publish(joint_state);
}

void URRosClient::publishRobotState(const ur5_message::RobotStateMessage& robot_state){
    ur_teleop_messages::URStatePtr robot_state_msg(new ur_teleop_messages::URState());
    robot_state_msg->header.frame_id = "UniversalRobot";
    robot_state_msg->header.stamp = ros::Time::now();
    robot_state_msg->robot_mode = robot_state.robot_mode;
    robot_state_msg->robot_time = robot_state.robot_time;
    robot_state_msg->is_power_on_robot = robot_state.is_power_on_robot;
    robot_state_msg->is_extra_button_pressed = robot_state.is_extra_button_pressed;
    robot_state_msg->is_emergency_stopped = robot_state.is_emergency_stopped;
    robot_state_msg->is_power_button_pressed = robot_state.is_power_button_pressed;
    robot_state_msg->is_robot_connected = robot_state.is_robot_connected;
    robot_state_msg->is_safety_signal_such_taht_we_should_stop = robot_state.is_safety_signal_such_that_we_should_stop;
    robot_state_msg->is_security_stopped = robot_state.is_security_stopped;
    for(size_t i=0;i<6;i++) {
        robot_state_msg->q_actual[i] = robot_state.q_actual[i];
        robot_state_msg->qd_actual[i] = robot_state.qd_actual[i];
        robot_state_msg->joint_modes[i] = robot_state.joint_modes[i];
    }
    robot_state_publisher.publish(robot_state_msg);
}