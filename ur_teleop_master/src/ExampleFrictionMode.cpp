//
// Created by ub1404 on 16. 11. 15.
//
#include <ros/ros.h>
#include <haptics/haptic_devices/OmegaDevice.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#define RAD2DEG(rad)    (rad*180.0/3.141592)

int main(int argc,char** argv){
    ros::init(argc, argv, "example_friction_mode");
    ros::NodeHandle nh;
    ros::NodeHandle p_nh("~");

    tf::TransformBroadcaster tf_broad;
    std::string device_type;
    if(!p_nh.getParam("device", device_type)){
        ROS_ERROR("Required parameter \'device\' is missing.");
        return 0;
    }

    HapticDevice* device = NULL;
    if(device_type == "OmegaDevice"){
        if(OmegaDevice::getNumberOfDevices() == 0){
            ROS_INFO("No available haptic devices");
            return 0;
        }
        ROS_INFO("%d devices are available", OmegaDevice::getNumberOfDevices());
        device = new OmegaDevice(0);
    }else{
        ROS_ERROR("Undefined device type \'%s\'",device_type.c_str());
        return 0;
    }

    ///////////////////////////////////////////////////////
    if(!device->open()){
        ROS_INFO("Cannot open haptic device[%s]", device->getErrorMessage());
        return 0;
    }
    ROS_INFO("Starting Haptic Loop");

    tf::StampedTransform transform;
    double x,y,z;
    double vx, vy, vz;
    double K = -10.0;
    transform.frame_id_ = "world";
    transform.child_frame_id_ = "haptic_device";
    while(ros::ok()){
        device->update();
        printf("%s ", device->getDeviceName());

        //Buttons
        for(size_t i=0;i<device->numberOfButtons();i++){
            printf("\t%c ", device->getButton(i).isPressed()?'O':'X');
        }

        //Translation
        device->getTranslation(x,y,z);
        device->getLinearVelocity(vx, vy, vz);
        printf("%6.3lf %6.3lf %6.3lf ", x,y,z);
        transform.stamp_ = ros::Time::now();
        transform.setOrigin(tf::Vector3(x,y,z));

        //Orientation
        if(device->isOrientationAvailable()) {
            Eigen::Quaterniond q;
            device->getOrientation(q.x(), q.y(), q.z(), q.w());
            double R,P,Y;
            tf::Matrix3x3(tf::Quaternion(q.x(),q.y(), q.z(), q.w())).getRPY(R,P,Y);
            printf("%6.1lf %6.1lf %6.1lf ", RAD2DEG(R),RAD2DEG(P),RAD2DEG(Y));

            ////Eigen's eulerAngles method return discrete(only in appearance) RPY value,
            ////but it is actually correct solution
            ////(Rotation matrix->Euler angles have two solutions if it is not at singularity).
//            printf("%6.1lf %6.1lf %6.1lf ", RAD2DEG(RPY[2]),RAD2DEG(RPY[1]),RAD2DEG(RPY[0]));
//            Eigen::Vector3d RPY= q.matrix().eulerAngles(2,1,0);
            transform.setRotation(tf::Quaternion(q.x(), q.y(), q.z(), q.w()));
        }else{
            transform.setRotation(tf::Quaternion(0,0,0,1));
        }
        printf("\r");
        fflush(stdout);

        //Set Friction Force
        device->setForce(K*vx, K*vy, K*vz);

        //Send transform
        tf_broad.sendTransform(transform);
    }
    device->close();
    delete device;
    ROS_INFO("Bye Bye~");
    return 0;
}