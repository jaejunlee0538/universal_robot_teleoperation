//
// Created by ub1404 on 16. 11. 15.
//

#include <stdlib.h>
#include <haptics/haptic_devices/OmegaDevice.h>
#include <dhdc.h>
#include <string>
size_t OmegaDevice::getNumberOfDevices(){
    return dhdGetDeviceCount();
}

OmegaDevice::OmegaDevice(int device_id):device_id(device_id){

}

OmegaDevice::~OmegaDevice(){

}

bool OmegaDevice::open(){
    if((device_id_internal = dhdOpenID(device_id)) < 0){
        setErrorMessage("dhdOpenID failed");
        return false;
    }

    if(!initInternalVariables()) {
        dhdClose(device_id_internal);
        return false;
    }

    xyz.setZero();
    xyz_vel.setZero();
    rotation = Eigen::Quaterniond(0,0,0,1);

    //
    wrist_available = dhdHasWrist(device_id_internal);

    //
    dhdEnableForce(DHD_ON, device_id_internal);

    setForce_called = false;
    return true;
}

void OmegaDevice::close(){
    dhdEnableForce(DHD_OFF,device_id_internal);
    dhdClose(device_id_internal);
}

bool OmegaDevice::isOrientationAvailable() const{
    return wrist_available;
}

void OmegaDevice::update(){
    if(!setForce_called){
        //If setForce was not called after the last 'update' call,
        //force to it to be called with zero force.
        setForce(0,0,0);
    }
    setForce_called = false;

    //update translation
    Eigen::Vector3d tmp;
    dhdGetPosition(&tmp[0], &tmp[1], &tmp[2], device_id_internal);
    xyz = R_origin_to_ref * tmp;

    //update linear velocity
    dhdGetLinearVelocity(&tmp[0], &tmp[1], &tmp[2], device_id_internal);
    xyz_vel = R_origin_to_ref * tmp;

    //update rotation
    if(isOrientationAvailable()){
        double rot[3][3];
        if (dhdGetOrientationFrame(rot, device_id_internal) >= 0) {
            Eigen::Matrix3d m;
            for(size_t i=0;i<3;i++){
                for(size_t k=0;k<3;k++){
                    m(i,k) = rot[i][k];
                }
            }
            m  =  R_origin_to_ref * rot45 * m * R_origin_to_ref;
            rotation = Eigen::Quaterniond(m);
        }
    }

    //update buttons
    for(size_t i=0;i<buttonsAvailable.size();i++){
        buttonsAvailable[i].update(dhdGetButton(i, device_id_internal) == DHD_ON);
    }
}

bool OmegaDevice::getTranslation(double& x, double& y, double& z){
    x = xyz[0];
    y = xyz[1];
    z = xyz[2];
    return true;
}

bool OmegaDevice::getLinearVelocity(double& vx, double& vy, double& vz){
    vx = xyz_vel[0];
    vy = xyz_vel[1];
    vz = xyz_vel[2];
    return true;
}

size_t OmegaDevice::numberOfButtons() const{
    return buttonsAvailable.size();
}

const Button& OmegaDevice::getButton(const size_t& idx){
    assert(idx < buttonsAvailable.size());
    return buttonsAvailable[idx];
}

bool OmegaDevice::getOrientation(double& qx, double& qy, double& qz, double& qw) {
    qx = rotation.x();
    qy = rotation.y();
    qz = rotation.z();
    qw = rotation.w();
    return true;
}

bool OmegaDevice::setForce(const double& fx, const double& fy, const double& fz){
    setForce_called = true;
    Eigen::Vector3d f(fx, fy, fz);
    f = R_origin_to_ref * f;
    if(dhdSetForce(f[0], f[1], f[2], device_id_internal) < 0){
        return false;
    }
    return true;
}

bool OmegaDevice::isTorqueAvilable() const{
    return false;
}

bool OmegaDevice::setTorque(const double& tx, const double& ty, const double& tz){
    return false;
}

const char* OmegaDevice::getDeviceName(){
    return dhdGetSystemName(device_id_internal);
}

bool OmegaDevice::initInternalVariables(){
    int device_type = dhdGetSystemType(device_id_internal);
    if(device_type<0){
        setErrorMessage("Failed to get device type - id : %d", device_id_internal);
        return false;
    }
    buttonsAvailable.clear();
    switch (device_type) {
        case DHD_DEVICE_OMEGA33: case DHD_DEVICE_OMEGA33_LEFT:
            //TODO : is this applicable to DHD_DEVICE_OMEGA33_LEFT also?
            rot45 = Eigen::AngleAxisd(M_PI_2, Eigen::Vector3d::UnitY()).matrix();
            R_origin_to_ref = Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitZ()).inverse();
            //
            buttonsAvailable.resize(1);
            return true;
        case DHD_DEVICE_OMEGA3:
            rot45.setIdentity();
            R_origin_to_ref = Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitZ()).inverse();
            buttonsAvailable.resize(1);
            return true;
        case DHD_DEVICE_NONE:
            setErrorMessage("No device is detected.");
            return false;
        case DHD_DEVICE_FALCON:
            setErrorMessage("Falcon is not implemented yet.");
            return false;
        default:
            setErrorMessage("Undefined device type - %d", device_type);
            return false;
    }

}

bool OmegaDevice::initButtons(){

}
