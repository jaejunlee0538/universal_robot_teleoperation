//
// Created by ub1404 on 15. 8. 24.
//


#ifndef CONFIGURATION_FAKE_H_
#define CONFIGURATION_FAKE_H_

int fake_calibration_load();
int fake_calibration_save();
int fake_configuration_load();
void fake_check_for_valid_hw_combo();
void fake_configuration_print();
void fake_calibration_print();
const char* fake_getJointVersion(int const jointID);
void fake_setForceParamsToDefault();

#endif