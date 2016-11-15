/*
 * Author : jaejunlee.
 * Email : jaejun0201@gmail.com
 *
 */
#ifndef OMEGA6_UTILS_H_
#define OMEGA6_UTILS_H_
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <dhdc.h>
#include <drdc.h>
#include <stdio.h>
#include <string.h>

namespace OMEGA6 {
    typedef int DeviceID;

    class Button {
        //TODO : at specific rapid count , Callback?
    public:
        enum ButtonStates {
            BUTTON_ON = 1,
            BUTTON_OFF = 0,
        };

        enum EdesState {
            NO_EDGE = 0,
            ON_TO_OFF = -2,
            OFF_TO_ON = 2,
        };

        Button() {
            last_state = current_state = BUTTON_OFF;
            tick_count_buffer = tick_count = 0;
            sensitivity = 0.25;    //tuned
            pressed_for = 0.0;
        }

        /*
         * call this method in haptic or control loop.
         * state : BUTTON_ON or BUTTON_OFF
         * t	 : current time in seconds unit.
         */
        void update(ButtonStates state, double t) {
            current_state = state;
            diff = 2 * (current_state - last_state);

            if (t - last_tick_time > sensitivity) {
                tick_count_buffer = tick_count;
                tick_count = 0;
            }

            if (diff == OFF_TO_ON) {
                pressed_start = t;
            }

            if (diff == ON_TO_OFF) {
                tick_count++;
                last_tick_time = t;
                pressed_for = 0.0;
            }

            if (current_state == BUTTON_ON) {
                pressed_for = t - pressed_start;
            }

            last_state = current_state;
        }

        /*
         * Return elapsed time from button started being pressed.
         */
        double pressedFor() {
            return pressed_for;
        }

        /*
         * return BUTTON_ON or BUTTON_OFF
         */
        int isPressed() {
            return current_state;
        }

        /*
         * return NO_EDGE or ON_TO_OFF or OFF_TO_ON
         */
        int getEdge() {
            return diff;
        }

        /*
         * set acceptable time interval in seconds between each ticks.
         */
        void setTickSensitivity(double dt) {
            this->sensitivity = dt;
        }

        /*
         * get ticks.
         * As tick count is volatile quantity, it is cleared after being read.
         */
        int getTicks() {
            int ret = tick_count_buffer;
            tick_count_buffer = 0;
            return ret;
        }

    private:
        int current_state;
        int last_state;
        int diff;

        double pressed_start;
        double pressed_for;

        int tick_count;
        int tick_count_buffer;
        double sensitivity;
        double last_tick_time;
    };

    class ButtonOmega6 : public Button {
    public:
        /*
         * Button wrapper for Omega6.
         */
        void update() {
            double t = dhdGetTime();
            int btn = dhdGetButton(0);
            switch (btn) {
                case DHD_ON:
                    Button::update(BUTTON_ON, t);
                    break;
                case DHD_OFF:
                    Button::update(BUTTON_OFF, t);
                    break;
                default:
                    //error.
                    break;
            }
        }
    };

    template <typename T>
    void copyData(const T* src, T* dest, const int& N)
    {
        ::memcpy((void*)dest, (const void*)src, sizeof(T)*N);
    }

    /*
     * Return elapsed time from the first 'getTime' call.
     * If 'reset' is given true, getTime will change start point to now.
     */
    double getTime(bool reset=false)
    {
        static double t0 = dhdGetTime();
        if(reset)
            t0 = dhdGetTime();
        return dhdGetTime() - t0;
    }

    char getKeyInput() {
        if (dhdKbHit())
            return dhdKbGet();
        return -1;
    }

    bool shouldStop() {
        if (getKeyInput() == 'q')
            return true;
        return false;
    }

    void printSDKVersion(void) {
        int major, minor, release, revision;
        dhdGetSDKVersion(&major, &minor, &release, &revision);
        printf("\n");
        printf("Force Dimension - Gravity Compensation Example %d.%d.%d.%d\n", major, minor, release, revision);
        printf("(C) 2014 Force Dimension\n");
        printf("All Rights Reserved.\n\n");

    }

    void printErrorMessage(void) {
        int err = dhdErrorGetLast();
        printf("DHD error : %s(error code : %d)\n", dhdErrorGetStr(err), err);
    }

    void printPositionAndOriantation(bool carrage_return = false, int freq = 60) {
        static double t0 = dhdGetTime();
        static double last_print = 0.0;
        double x, y, z;
        double vx, vy, vz;
        double oa, ob, og;
        double wx, wy, wz;
        double t;
        t = dhdGetTime() - t0;

        dhdGetPositionAndOrientationDeg(&x, &y, &z, &oa, &ob, &og);
        if ((t - last_print) > (1.0 / freq)) {
            dhdGetLinearVelocity(&vx, &vy, &vz);
            dhdGetAngularVelocityDeg(&wx, &wy, &wz);
            printf("%+5.3lf:", t);    //t
            printf("%+5.3lf ", x);
            printf("%+5.3lf ", y);
            printf("%+5.3lf ", z); //pos
            printf(" | ");
            printf("%+6.2lf ", oa);
            printf("%+6.2lf ", ob);
            printf("%+6.2lf ", og); //orientation
            printf(" | ");
            printf("%+5.3lf ", vx);
            printf("%+5.3lf ", vy);
            printf("%+5.3lf ", vz); //linear vel
            printf(" | ");
            printf("%+6.2lf ", wx);
            printf("%+6.2lf ", wy);
            printf("%+6.2lf ", wz);//angular vel
            if (carrage_return) {
                printf("\r");
                fflush(stdout);
            }
            else {
                printf("\n");
            }
            last_print = t;
        }
    }

    /*
     * Every inputs shares one limit value.
     */
    void saturation(double *input, const int Nval, const double limit) {
        for (int i = 0; i < Nval; i++) {
            if (input[i] > 0.0) {
                if (fabs(input[i]) > limit)
                    input[i] = -1.0 * limit;
            }
            else {
                if (input[i] > limit)
                    input[i] = limit;
            }
        }
    }

    /*
     * Each inputs has it's own limit.
     */
    void saturation(double *input, const double *limit, const int Nval) {
        for (int i = 0; i < Nval; i++) {
            if (input[i] > 0.0) {
                if (fabs(input[i]) > limit[i])
                    input[i] = -1.0 * limit[i];
            }
            else {
                if (input[i] > limit[i])
                    input[i] = limit[i];
            }
        }
    }

    int setForces(const double* fxyz)
    {
        if(fxyz)
            return dhdSetForce(fxyz[0], fxyz[1], fxyz[2]);
        return DHD_ERROR;
    }

    int getLinearVelocity(double * xyz)
    {
        if(xyz)
            return dhdGetLinearVelocity(&xyz[0], &xyz[1], &xyz[2]);
        return DHD_ERROR;
    }

    int getAngularVelocityDeg(double * wxyz)
    {
        if(wxyz)
            return dhdGetAngularVelocityDeg(&wxyz[0], &wxyz[1], &wxyz[2]);
        return DHD_ERROR;
    }

    int getAngularVelocityRad(double * wxyz)
    {
        if(wxyz)
            return dhdGetAngularVelocityRad(&wxyz[0], &wxyz[1], &wxyz[2]);
        return DHD_ERROR;
    }

    int getPosition(double *xyz) {
        if (xyz)
            return dhdGetPosition(&xyz[0], &xyz[1], &xyz[2]);
        return DHD_ERROR;
    }

    int getPositionAndOrientationRad(double *xyz, double *abg) {
        if (xyz && abg)
            return dhdGetPositionAndOrientationRad(&xyz[0], &xyz[1], &xyz[2],
                                                   &abg[0], &abg[1], &abg[2]);
        return DHD_ERROR;
    }

    int getPositionAndOrientationDeg(double *xyz, double *abg) {
        if (xyz && abg)
            return dhdGetPositionAndOrientationDeg(&xyz[0], &xyz[1], &xyz[2],
                                                   &abg[0], &abg[1], &abg[2]);
        return DHD_ERROR;
    }

    DeviceID initDHD(bool force_enable = false) {
        int device_count = 0;

        printSDKVersion();

        device_count = dhdGetDeviceCount();
        if (device_count < 0) {
            printf("error: %s\n", dhdErrorGetLastStr());
            return DHD_ERROR;
        }
        else if (device_count < 1) {
            printf("no device detected\n");
            return DHD_ERROR;
        }

        if (dhdOpen() < 0) {
            printf("error: cannot open device (%s)\n", dhdErrorGetLastStr());
            dhdSleep(2.0);
            return DHD_ERROR;
        }

        // identify device
        printf("%s device detected\n\n", dhdGetSystemName());

        if (force_enable) {
            dhdEnableForce(DHD_ON);
        }
        return DHD_NO_ERROR;
    }

    void closeDHD(void) {
        dhdEnableForce(DHD_OFF);
        dhdClose();
    }

    DeviceID initDRD(void) {
        int device_count = 0;

        printSDKVersion();

        device_count = dhdGetDeviceCount();
        if (device_count < 0) {
            printf("error: %s\n", dhdErrorGetLastStr());
            return DHD_ERROR;
        }
        else if (device_count < 1) {
            printf("no device detected\n");
            return DHD_ERROR;
        }

        if (drdOpen() < 0) {
            printf("error: cannot open device (%s)\n", dhdErrorGetLastStr());
            dhdSleep(2.0);
            return DHD_ERROR;
        }

        if (!drdIsSupported()) {
            printf("unsupported device\n");
            printf("exiting...\n");
            dhdSleep(2.0);
            drdClose();
            return DHD_ERROR;
        }

        // identify device
        printf("%s device detected\n\n", dhdGetSystemName());
        return DHD_NO_ERROR;
    }

    void closeDRD(void) {
        drdClose();
    }
}

#endif