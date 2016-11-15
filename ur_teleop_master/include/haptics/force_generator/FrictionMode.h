//
// Created by ub1404 on 15. 9. 8.
//

#ifndef UR_ROBOT_FRICTIONMODE_H
#define UR_ROBOT_FRICTIONMODE_H
#include "ForceGenerator.h"

class FrictionModeInterface:public ForceGenerator {
public:
    FrictionModeInterface() {
        this->_viscosity = 15.0;
    }

    void setViscosity(double viscosity) {
        this->_viscosity = viscosity;
    }

    int computeForce(const double *xyz, const double *vxyz, double *forces, double *delta_xyz) {
        for (int i = 0; i < 3; i++) {
            forces[i] = -this->_viscosity * vxyz[i];

            if (delta_xyz)
                delta_xyz[i] = vxyz[i];
        }
    }

private:
    double _viscosity;
};


#endif //UR_ROBOT_FRICTIONMODE_H
