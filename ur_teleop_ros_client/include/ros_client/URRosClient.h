//
// Created by ub1404 on 16. 11. 14.
//

#ifndef UR_TELEOP_ROS_CLIENT_URROSCLIENT_H
#define UR_TELEOP_ROS_CLIENT_URROSCLIENT_H
#include "URCallbackClient.h"
#include <ros/ros.h>
#include <ros/publisher.h>
#include <ros/subscriber.h>
#include <ur_teleop_messages/URJointCommand.h>
#include <ur_teleop_messages/URConfigCommand.h>
#include <boost/thread/mutex.hpp>
class URRosClient:public URCallbackClient {
public:
    URRosClient();
    void initTopics(ros::NodeHandle& nh, const std::string& joint_state_topic, const std::string& robot_state_topic,
              const std::string& joint_command_topic, const std::string& config_command_topic);

protected:
    virtual bool stateCallback(ur5_message::RobotStateMessage robot_state);

    void publishJointState(const ur5_message::RobotStateMessage& robot_state);
    void publishRobotState(const ur5_message::RobotStateMessage& robot_state);
    void jointCommandCallback(const ur_teleop_messages::URJointCommandConstPtr& jnt_command);
    void configCommandCallback(const ur_teleop_messages::URConfigCommandConstPtr& config_command);
protected:
    ur_teleop_messages::URJointCommandConstPtr joint_command;
    ur_teleop_messages::URConfigCommandConstPtr config_command;

    ros::Publisher joint_state_publisher;
    ros::Publisher robot_state_publisher;
    ros::Subscriber joint_command_subscriber;
    ros::Subscriber config_command_subscriber;

    boost::mutex command_lock;
};
#endif //UR_TELEOP_ROS_CLIENT_URROSCLIENT_H
