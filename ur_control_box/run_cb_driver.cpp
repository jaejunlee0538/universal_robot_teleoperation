//
// Created by ub1404 on 15. 8. 21.
//
#include <stdlib.h>
#include <stdio.h>
#include <urrobot/ur5/control_box_driver/URInterface.h>

int main(int argc, char** argv)
{
    ur_control_box::URInterface ur_robot;

    if(!ur_robot.init())
    {
        LOG_ERROR("Robot init failed");
        exit(-1);
    }

    while(!ur_robot.should_stop())
    {
        ur_robot.controlLoop();
    }

    ur_robot.turnOffRobot();
    return 1;
}