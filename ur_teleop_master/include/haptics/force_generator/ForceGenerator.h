//
// Created by ub1404 on 16. 11. 14.
//

#ifndef UR_TELEOP_MASTER_DEVICES_FORCEGENERATOR_H
#define UR_TELEOP_MASTER_DEVICES_FORCEGENERATOR_H
class ForceGenerator{
public:
    virtual int computeForce(const double *xyz, const double *vxyz, double *forces, double *delta_xyz) = 0;
};
#endif //UR_TELEOP_MASTER_DEVICES_FORCEGENERATOR_H
