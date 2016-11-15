//
// Created by ub1404 on 15. 8. 24.
//

#include "ConfigurationFake.h"
#include <stdio.h>

int fake_calibration_load() {
    printf("fake_calibration_load\n");
    return 1;
}

int fake_calibration_save() {
    printf("fake_calibration_save\n");
    return 1;
}

int fake_configuration_load() {
    printf("fake_configuration_load\n");
    return 1;
}

void fake_check_for_valid_hw_combo() {
    printf("fake_check_for_valid_hw_combo\n");
}

void fake_configuration_print() {
    printf("fake_configuration_print\n");
}

void fake_calibration_print() {
    printf("fake_calibration_print\n");
}

const char *fake_getJointVersion(int const jointID) {
    printf("fake_getJointVersion\n");
}

void fake_setForceParamsToDefault() {
    printf("fake_setForceParamsToDefault\n");
}