//
// Created by ub1404 on 16. 11. 14.
//
#include <ros/ros.h>
#include <ros_client/URRosClient.h>
#include <boost/thread.hpp>
void URSpinThread(URRosClient* client){
    ROS_INFO("Starting URSpinThread");
    while(ros::ok()){
        client->spinOnce();
    }
}

int main(int argc, char** argv){
    ros::init(argc, argv, "ur_ros_client_node");
    ros::NodeHandle nh;
    ros::NodeHandle p_nh("~");
    std::string robot_ip;
    int port_number;
    if(!p_nh.getParam("robot_ip", robot_ip)){
        ROS_ERROR("Parameter \'robot_ip\' is missing");
        return 0;
    }
    if(!p_nh.getParam("port_number", port_number)){
        ROS_ERROR("Parameter \'port_number\' is missing");
        return 0;
    }

    URRosClient ros_client;
    if(!ros_client.init(robot_ip.c_str(), port_number)){
        ROS_ERROR("Cannot connect to the robot");
        return 0;
    }
    ros_client.initTopics(nh, "joint_states", "ur_state", "ur_joint_command", "ur_config_command");

    boost::thread spin_thread(URSpinThread,&ros_client);

    ros::spin();

    spin_thread.join();
    return 0;
}