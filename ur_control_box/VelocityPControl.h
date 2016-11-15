//
// Created by ub1404 on 15. 9. 17.
//

#ifndef PLAYGROUND_VELOCITYPID_H
#define PLAYGROUND_VELOCITYPID_H
#include <vector>
#include <algorithm>
#include <math.h>
class VelocityPControl {
public:
    VelocityPControl(){

    }

    void init(double P, double min_pos, double max_pos, double max_vel, double max_acc)
    {
        this->P = P;
        this->min_pos = min_pos;
        this->max_pos = max_pos;
        this->max_vel = max_vel;
        this->max_acc = max_acc;
    }

    double update(const double& current_pos, const double& current_vel, const double& desired_pos, const double& dt)
    {
        double vel_cmd = P * (desired_pos - current_pos);
        if(current_vel > 0.0)
        {
            std::vector<double> max_vel_cand;//candidates
            max_vel_cand.push_back(current_vel + max_acc*dt);
            max_vel_cand.push_back(sqrt(2 * max_acc * (max_pos - current_pos)));
            max_vel_cand.push_back(max_vel);
            double vel_lim = *std::min_element(max_vel_cand.begin(), max_vel_cand.end());
            if(vel_cmd > vel_lim)
                vel_cmd = vel_lim;
        }
        else
        {
            std::vector<double> min_vel_cand;//candidates
            min_vel_cand.push_back(current_vel - max_acc*dt);
            min_vel_cand.push_back(-sqrt(2 * max_acc * (current_pos - min_pos)));
            min_vel_cand.push_back(-max_vel);
            double vel_lim = *std::min_element(min_vel_cand.begin(), min_vel_cand.end());
            if(vel_cmd < vel_lim)
                vel_cmd = vel_lim;
        }
//        printf("%.5f\t%.5f\t%.5f\n", desired_pos, current_pos, vel_cmd);
        return vel_cmd;
    }

protected:
    /*
     * Gain values for P
     */
    double P;

    double min_pos;
    double max_pos;
    double max_vel;
    double max_acc;
};


#endif //PLAYGROUND_VELOCITYPID_H
