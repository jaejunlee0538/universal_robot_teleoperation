//
// Created by ub1404 on 16. 11. 15.
//

#include <haptics/haptic_devices/Omega6.h>
#include <dhdc.h>
size_t Omega6::getNumberOfDevices(){
    return dhdGetDeviceCount();
}

Omega6::Omega6(int device_id):device_id(device_id){

}

Omega6::~Omega6(){

}

bool Omega6::open(){
    if(dhdOpenID(device_id) < 0){
        return false;
    }
    dhdEnableForce(DHD_ON, device_id);
    return true;
}

void Omega6::close(){
    dhdEnableForce(DHD_OFF,device_id);
    dhdClose(device_id);
}

bool Omega6::isOrientationAvailable() const{
    return true;
}

bool Omega6::getTranslation(double& x, double& y, double& z){
    if(dhdGetPosition(&x, &y, &z, device_id) < 0){
        return false;
    }
    return true;
}

bool Omega6::getLinearVelocity(double& vx, double& vy, double& vz){
    if(dhdGetLinearVelocity(&vx, &vy, &vz, device_id)<0){
        return false;
    }
    return true;
}

size_t Omega6::numberOfButtons() const{
    return 1;
}

bool Omega6::getButtonPressed(bool& pressed ,const size_t& button_idx) {
    if(button_idx >= numberOfButtons()){
        return false;
    }
    int ret = dhdGetButton(button_idx, device_id);
    pressed = ret==DHD_ON;
    return true;
}

bool Omega6::getOrientation(double& qx, double& qy, double& qz, double& qw){
    double rot[3][3];
    if(dhdGetOrientationFrame(rot, device_id) < 0){
        return false;
    }
    qw = sqrt(1+rot[0][0]+rot[1][1]+rot[2][2])/2;
    qx = (rot[2][1]-rot[1][2])/(4*qw);
    qy = (rot[0][2]-rot[2][0])/(4*qw);
    qz = (rot[1][0]-rot[0][1])/(4*qw);
    double n = 1.0/sqrt(qw*qw+qx*qx+qy*qy+qz*qz);
    qw *= n;
    qx *= n;
    qy *= n;
    qz *= n;
    return true;
}

bool Omega6::setForce(const double& fx, const double& fy, const double& fz){
    if(dhdSetForce(fx, fy, fz, device_id)<0){
        return false;
    }
    return true;
}

bool Omega6::isTorqueAvilable() const{
    return false;
}

bool Omega6::setTorque(const double& tx, const double& ty, const double& tz){
    return false;
}
