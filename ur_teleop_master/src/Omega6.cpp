//
// Created by ub1404 on 16. 11. 15.
//

#include <haptics/haptic_devices/Omega6.h>
#include <dhdc.h>

size_t Omega6::getNumberOfDevices(){
    return dhdGetDeviceCount();
}

Omega6::Omega6(int device_id):device_id(device_id){
    initReferenceFrame();
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
    Eigen::Vector3d v;
    if(dhdGetPosition(&v[0], &v[1], &v[2], device_id) < 0){
        return false;
    }
    v = R_origin_to_ref * v;
    x = v[0];
    y = v[1];
    z = v[2];
    return true;
}

bool Omega6::getLinearVelocity(double& vx, double& vy, double& vz){
    Eigen::Vector3d v;
    if(dhdGetLinearVelocity(&v[0], &v[1], &v[2], device_id)<0){
        return false;
    }
    v = R_origin_to_ref * v;
    vx = v[0];
    vy = v[1];
    vz = v[2];
    return true;
}

size_t Omega6::numberOfButtons() const{
    return 1;
}

bool Omega6::getButtonPressed(const size_t& button_idx) {
    if(button_idx >= numberOfButtons()){
        //TODO : throw exception rather than return false
        return false;
    }
    return dhdGetButton(button_idx, device_id) == DHD_ON;
}

bool Omega6::getOrientation(double& qx, double& qy, double& qz, double& qw) {
    double rot[3][3];
    if (dhdGetOrientationFrame(rot, device_id) < 0) {
        return false;
    }

    Eigen::Matrix3d m;
    for(size_t i=0;i<3;i++){
        for(size_t k=0;k<3;k++){
            m(i,k) = rot[i][k];
        }
    }

    m  =  R_origin_to_ref * rot45 * m * R_origin_to_ref;
    Eigen::Quaterniond quat(m);
    qx = quat.x();
    qy = quat.y();
    qz = quat.z();
    qw = quat.w();
    return true;
}

bool Omega6::setForce(const double& fx, const double& fy, const double& fz){
    Eigen::Vector3d f(fx, fy, fz);
    f = R_origin_to_ref * f;
    if(dhdSetForce(f[0], f[1], f[2], device_id)<0){
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

void Omega6::initReferenceFrame(){
    rot45 = Eigen::AngleAxisd(M_PI_2, Eigen::Vector3d::UnitY()).matrix();
    R_origin_to_ref = Eigen::AngleAxisd(M_PI, Eigen::Vector3d::UnitZ()).inverse();
    R_origin_to_ref_inv = R_origin_to_ref.inverse();
}