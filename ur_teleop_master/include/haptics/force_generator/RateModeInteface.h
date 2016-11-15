#ifndef _RATE_MODE_INTERFACE_H_

#define _RATE_MODE_INTERFACE_H_

#include <math.h>
#include <string>
#include "ForceGenerator.h"
class AnchoredModeInterface:public ForceGenerator {
public:
    enum Region {
        REGION_IN_CIRCLE = 1,
        REGION_SURFACE,
        REGION_OUT_CIRCLE
    };

    AnchoredModeInterface() {
        initParameters(100.0, 20.0, 0.005, 0.005);
        for (int i = 0; i < 3; i++) {
            xyz_fix[i] = 0.0;
        }
        is_fixed = false;
    }

    void fixHere(const double *xyz) {
        for (int i = 0; i < 3; i++) {
            xyz_fix[i] = xyz[i];
        }
        this->is_fixed = true;
    }

    void releaseFix() {
        this->is_fixed = false;
    }

    /*
     * xyz   : xyz coordinates of master device
     * vxyz  : xyz velocity of master device
     * forces: computed forces for feedback
     * delta_xyz : distance from surface of safety sphere.
     */
    int computeForce(const double *xyz, const double *vxyz, double *forces, double *delta_xyz) {
        if (!this->is_fixed) {
            //Only viscosity works.
            for (int i = 0; i < 3; i++) {
                forces[i] = -this->_viscosity * vxyz[i];
                delta_xyz[i] = 0.0;
            }
            return REGION_OUT_CIRCLE;
        }

        double d_xyz[3];
        for (int i = 0; i < 3; i++) {
            d_xyz[i] = xyz[i] - xyz_fix[i];
        }

        double dist = sqrt(d_xyz[0] * d_xyz[0] + d_xyz[1] * d_xyz[1] + d_xyz[2] * d_xyz[2]);

        if (dist <= this->_safe_zone_radius) {
            for (int i = 0; i < 3; i++) {
                delta_xyz[i] = 0.0;
                forces[i] = -10.0 * vxyz[i];
            }
            return REGION_IN_CIRCLE;
        }
        else if (dist <= this->_R) {
            double net_force = 500.0 * (dist - this->_safe_zone_radius);
            for (int i = 0; i < 3; i++) {
                delta_xyz[i] = 0.0;
                forces[i] = -net_force * d_xyz[i] / dist;
            }
            return REGION_SURFACE;
        }
        else {
            for (int i = 0; i < 3; i++) {
                delta_xyz[i] = d_xyz[i] * (dist - this->_R) / dist;
                forces[i] = -(this->_elasticity * d_xyz[i] + this->_viscosity * vxyz[i]);
            }
            return REGION_OUT_CIRCLE;
        }
    }

    void setElasticity(double elasticity) {
        this->_elasticity = elasticity;
    }

    void setViscosity(double viscosity) {
        this->_viscosity = viscosity;
    }

    void setSafeSphere(double radius, double thickness) {
        if (radius == 0.0 || thickness == 0.0) {
            this->_safe_zone_radius =
            this->_wall_thickness =
            this->_R = -1.0;
        }
        else {
            this->_safe_zone_radius = radius;
            this->_wall_thickness = thickness;
            this->_R = this->_wall_thickness + this->_safe_zone_radius;
        }
    }

    void initParameters(double elasticity, double viscosity, double radius, double thickness) {
        this->setElasticity(elasticity);
        this->setViscosity(viscosity);
        this->setSafeSphere(radius, thickness);
    }

private:
    double xyz_fix[3];
    double _R;
    double _safe_zone_radius;
    double _wall_thickness;
    double _elasticity;
    double _viscosity;

    bool is_fixed;
};

#endif