//
// Created by ub1404 on 16. 11. 15.
//

#ifndef UR_TELEOP_MASTER_HAPTICDEVICE_H
#define UR_TELEOP_MASTER_HAPTICDEVICE_H
#include "Button.h"
#include <cstdio>
#include <cstdarg>
class HapticDevice {
public:
    HapticDevice(){err_msg[0]=NULL;}
    virtual ~HapticDevice(){}
    virtual bool open() = 0;
    virtual void close() =0;
    virtual void update() = 0;

    //translational
    virtual bool getTranslation(double& x, double& y, double& z) = 0;
    virtual bool getLinearVelocity(double& vx, double& vy, double& vz) = 0;
    virtual bool setForce(const double& fx, const double& fy, const double& fz) = 0;

    //orientational
    virtual bool isOrientationAvailable() const = 0;
    virtual bool getOrientation(double& qx, double& qy, double& qz, double& qw) = 0;
    virtual bool setTorque(const double& tx, const double& ty, const double& tz) = 0;
    virtual bool isTorqueAvilable() const = 0;

    //buttons
    virtual size_t numberOfButtons() const = 0 ;
    virtual const Button& getButton(const size_t& idx) = 0;

    virtual const char* getDeviceName() = 0;
    const char* getErrorMessage()const{
        return err_msg;
    }

protected:
    void setErrorMessage(const char* fmt, ...){
        std::va_list arg;
        va_start(arg, fmt);
        std::vsnprintf(err_msg, 1024, fmt, arg);
        va_end(arg);
    }

private:
    char err_msg[1024];
};


#endif //UR_TELEOP_MASTER_HAPTICDEVICE_H
