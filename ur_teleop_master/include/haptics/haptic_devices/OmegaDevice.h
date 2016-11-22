//
// Created by ub1404 on 16. 11. 15.
//

#ifndef UR_TELEOP_MASTER_OMEGA6_H
#define UR_TELEOP_MASTER_OMEGA6_H
#include "HapticDevice.h"
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <Eigen/Geometry>

class OmegaDevice :public HapticDevice{
public:
    static size_t getNumberOfDevices();
public:
    OmegaDevice(int device_id);
    ~OmegaDevice();
    bool open();
    void close();
    void update();
    bool isOrientationAvailable() const;
    bool getTranslation(double& x, double& y, double& z);
    bool getLinearVelocity(double& vx, double& vy, double& vz);
    size_t numberOfButtons() const;
    bool getOrientation(double& qx, double& qy, double& qz, double& qw);
    bool setForce(const double& fx, const double& fy, const double& fz);
    bool isTorqueAvilable() const;
    bool setTorque(const double& tx, const double& ty, const double& tz);
    const Button& getButton(const size_t& idx);
    const char* getDeviceName();
protected:
    bool initInternalVariables();
    bool initButtons();
protected:
    int device_id;//When openning the device, this should be used
    int device_id_internal;//unique device id assigned by dh-sdk.
    bool wrist_available;

    Eigen::Vector3d xyz;
    Eigen::Vector3d xyz_vel;
    Eigen::Quaterniond rotation;

    Eigen::Matrix3d R_origin_to_ref;//rotation matrix to rotate the reference frame
    Eigen::Matrix3d rot45;
    std::vector<Button> buttonsAvailable;
};


#endif //UR_TELEOP_MASTER_OMEGA6_H
