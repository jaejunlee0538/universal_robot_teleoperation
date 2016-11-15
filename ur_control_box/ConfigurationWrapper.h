//
// Created by ub1404 on 15. 8. 24.
//

#ifndef UR5_CONFIGURATIONWRAPPER_H
#define UR5_CONFIGURATIONWRAPPER_H

#ifdef BUILD_REAL_ROBOT
#include "urrobot/ur5/control_box_driver/ur_c_api/Configuration.h"

#define     wrapper_calibration_load()              calibration_load()
#define     wrapper_calibration_save()              calibration_save()
#define     wrapper_configuration_load()            configuration_load()
#define     wrapper_check_for_valid_hw_combo()      check_for_valid_hw_combo()
#define     wrapper_configuration_print()           configuration_print()
#define     wrapper_calibration_print()             calibration_print()
#define     wrapper_getJointVersion(jointID)        getJointVersion(jointID)
#define     wrapper_setForceParamsToDefault()       setForceParamsToDefault()

#else

#include "urrobot/ur5/control_box_driver/ConfigurationFake.h"
#define     wrapper_calibration_load()              fake_calibration_load()
#define     wrapper_calibration_save()              fake_calibration_save()
#define     wrapper_configuration_load()            fake_configuration_load()
#define     wrapper_check_for_valid_hw_combo()      fake_check_for_valid_hw_combo()
#define     wrapper_configuration_print()           fake_configuration_print()
#define     wrapper_calibration_print()             fake_calibration_print()
#define     wrapper_getJointVersion(jointID)        fake_getJointVersion(jointID)
#define     wrapper_setForceParamsToDefault()       fake_setForceParamsToDefault()
#endif

#endif //UR5_CONFIGURATIONWRAPPER_H
