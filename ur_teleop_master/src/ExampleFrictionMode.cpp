//
// Created by ub1404 on 16. 11. 15.
//
#include <ros/ros.h>
#include <haptics/haptic_devices/Omega6.h>
#include <dhdc.h>
void quaternionToRPY(double q[4], double RPY[3]){
    double ysqr = q[1] * q[1];
    double t0 = -2.0f * (ysqr + q[2] * q[2]) + 1.0f;
    double t1 = +2.0f * (q[0] * q[2] - q[3] * q[2]);
    double t2 = -2.0f * (q[0]* q[2] + q[3] * q[1]);
    double t3 = +2.0f * (q[1] * q[2] - q[3] * q[0]);
    double t4 = -2.0f * (q[0] * q[0] + ysqr) + 1.0f;

    t2 = t2 > 1.0f ? 1.0f : t2;
    t2 = t2 < -1.0f ? -1.0f : t2;

    RPY[0] = std::atan2(t3, t4);
    RPY[1] = std::asin(t2);
    RPY[2] = std::atan2(t1, t0);
}
#define RAD2DEG(rad)    (rad*180.0/3.141592)

int main(int argc,char** argv){
    ros::init(argc, argv, "example_friction_mode");
    ros::NodeHandle nh;
    ros::NodeHandle p_nh("~");

    if(Omega6::getNumberOfDevices() == 0){
        ROS_INFO("No available haptic devices");
        return 0;
    }
    HapticDevice* device = new Omega6(0);

    ///////////////////////////////////////////////////////
    if(!device->open()){
        ROS_INFO("Cannot open haptic device");
        return 0;
    }

    ROS_INFO("Starting Haptic Loop");

    double x,y,z;
    double vx, vy, vz;
    double K = -10.0;
    while(ros::ok()){
        device->getTranslation(x,y,z);
        device->getLinearVelocity(vx, vy, vz);
        device->setForce(K*vx, K*vy,K*vz);

        printf("%6.3lf %6.3lf %6.3lf ", x,y,z);
        if(device->isOrientationAvailable()) {
            double q[4];
            double RPY[3];
            device->getOrientation(q[0], q[1], q[2], q[3]);
            quaternionToRPY(q, RPY);
            printf("%6.1lf %6.1lf %6.1lf ", RAD2DEG(RPY[0]),RAD2DEG(RPY[1]),RAD2DEG(RPY[2]));
        }
        printf("\r");
        fflush(stdout);
    }
    device->close();
    delete device;
    ROS_INFO("Bye Bye~");
    return 0;
}