#ifndef ROBOTINTERFACE_FAKE_H_
#define ROBOTINTERFACE_FAKE_H_
#include <stdint.h>
#include <urrobot/ur5/control_box_driver/ur_c_api/robotinterface.h>

uint64_t fake_robotinterface_get_step();

double fake_robotinterface_get_time();

double fake_robotinterface_get_time_per_step();

void fake_robotinterface_command_position_velocity_acceleration(const double * q, const double * qd, const double * qdd);

void fake_robotinterface_command_velocity_acceleration(const double * q, const double * qd, const double * qdd);

void fake_robotinterface_command_velocity(const double * qd);

void fake_robotinterface_command_joint_position_velocity_acceleration(int joint, double q, double qd);

void fake_robotinterface_command_velocity_security_torque_control_torque(const double * qd, const double * security_torque, const double * control_torque, const double * softness);

void fake_robotinterface_command_torque(const double * qd, const double * security_torque, const double * control_torque);

void fake_robotinterface_command_empty_command();

void fake_robotinterface_master_goto_bootloader_mode();

void fake_robotinterface_command_digital_out_port(int port, int value);

void fake_robotinterface_command_digital_out_bits(unsigned short bits);

void fake_robotinterface_command_analog_out_port(int port, double value);

void fake_robotinterface_command_analog_input_range_port(int port, int range);

void fake_robotinterface_command_analog_output_domain(int port, int type);

void fake_robotinterface_command_tool_output_voltage(unsigned char value);

void fake_robotinterface_set_tcp(const double * tcp_pose);

void fake_robotinterface_set_tcp_payload_cog(const double * tcp_payload_cog);

void fake_robotinterface_set_tcp_payload(double tcp_payload);

void fake_robotinterface_get_tcp(double * tcp_pose);

void fake_robotinterface_get_tcp_payload_cog(double * tcp_pose);

double fake_robotinterface_get_tcp_payload();

void fake_robotinterface_set_tcp_wrench(const double * new_tcp_wrench, const int in_base_coord);

void fake_robotinterface_get_tcp_wrench(double * gotten_tcp_wrench);

int fake_robotinterface_is_tcp_wrench_in_base_coord();

int fake_robotinterface_open(int open_simulated);

int fake_robotinterface_do_open(int open_simulated);

int fake_robotinterface_open_allow_bootloader(int open_simulated);

void fake_robotinterface_read_state_blocking();

void fake_robotinterface_send();

int fake_robotinterface_is_robot_connected();

int fake_robotinterface_close();

uint8_t fake_robotinterface_get_robot_mode();

void fake_robotinterface_set_robot_ready_mode();

void fake_robotinterface_set_robot_running_mode();

void fake_robotinterface_set_robot_freedrive_mode();

uint8_t fake_robotinterface_get_joint_mode(int joint);

uint8_t fake_robotinterface_get_tool_mode();

uint8_t fake_robotinterface_get_message_count();

int fake_robotinterface_get_message(struct message_t * message);

int fake_robotinterface_get_message_codes(struct message_t * msg, int * error_code, int * error_argument);

void fake_robotinterface_power_on_robot();

void fake_robotinterface_power_off_robot();

void fake_robotinterface_security_stop(char joint_code, int error_state, int error_argument);

int fake_robotinterface_is_power_on_robot();

int fake_robotinterface_is_security_stopped();

int fake_robotinterface_is_emergency_stopped();

int fake_robotinterface_is_extra_button_pressed();

int fake_robotinterface_is_power_button_pressed();

int fake_robotinterface_is_safety_signal_such_that_we_should_stop();

int fake_robotinterface_unlock_security_stop();

int fake_robotinterface_has_security_message();

int fake_robotinterface_get_security_message(struct message_t * message, int * error_state, int * error_argument);

uint32_t fake_robotinterface_get_master_control_bits();

void fake_robotinterface_get_actual(double * q, double * qd);

void fake_robotinterface_get_actual_position(double * q);

void fake_robotinterface_get_actual_velocity(double * qd);

void fake_robotinterface_get_actual_current(double * I);

void fake_robotinterface_get_tool_accelerometer_readings(double * ax, double * ay, double * az);

double fake_robotinterface_get_tcp_force_scalar();

void fake_robotinterface_get_tcp_force(double * F);

void fake_robotinterface_get_tcp_speed(double * V);

double fake_robotinterface_get_tcp_power();

double fake_robotinterface_get_power();

int fake_robotinterface_get_actual_digital_input(int port);

int fake_robotinterface_get_actual_digital_output(int port);

unsigned short fake_robotinterface_get_actual_digital_input_bits();

unsigned short fake_robotinterface_get_actual_digital_output_bits();

double fake_robotinterface_get_actual_analog_input(int port);

double fake_robotinterface_get_actual_analog_output(int port);

unsigned char fake_robotinterface_get_actual_analog_input_range(int port);

unsigned char fake_robotinterface_get_actual_analog_output_domain(int port);

void fake_robotinterface_get_target(double * q, double * qd, double * qdd);

void fake_robotinterface_get_target_position(double * q);

void fake_robotinterface_get_target_velocity(double * qd);

void fake_robotinterface_get_target_acceleration(double * qdd);

void fake_robotinterface_get_target_current(double * I);

void fake_robotinterface_get_target_moment(double * m);

unsigned short fake_robotinterface_get_target_digital_output_bits();

double fake_robotinterface_get_target_analog_output(int port);

unsigned char fake_robotinterface_get_target_analog_input_range(int port);

unsigned char fake_robotinterface_get_target_analog_output_domain(int port);

float fake_robotinterface_get_master_temperature();

float fake_robotinterface_get_robot_voltage_48V();

float fake_robotinterface_get_robot_current();

float fake_robotinterface_get_master_io_current();

unsigned char fake_robotinterface_get_master_safety_state();

unsigned char fake_robotinterface_get_master_on_off_state();

void fake_robotinterface_safely_remove_euromap67_hardware();

void fake_robotinterface_disable_teach_pendant_safety();

void fake_robotinterface_get_motor_temperature(float * T);

void fake_robotinterface_get_micro_temperature(float * T);

void fake_robotinterface_get_joint_voltage(float * V);

float fake_robotinterface_get_tool_temperature();

float fake_robotinterface_get_tool_voltage_48V();

unsigned char fake_robotinterface_get_tool_output_voltage();

float fake_robotinterface_get_tool_current();

uint8_t fake_robotinterface_is_euromap_hardware_installed();

uint8_t fake_robotinterface_get_euromap_input(uint8_t input_bit_number);

uint8_t fake_robotinterface_get_euromap_output(uint8_t output_bit_number);

void fake_robotinterface_set_euromap_output(uint8_t output_bit_number, uint8_t desired_value);

uint32_t fake_robotinterface_get_euromap_input_bits();

uint32_t fake_robotinterface_get_euromap_output_bits();

uint16_t fake_robotinterface_get_euromap_24V_voltage();

uint16_t fake_robotinterface_get_euromap_24V_current();

uint16_t fake_robotinterface_get_general_purpose_register(int address);

void fake_robotinterface_set_general_purpose_register(int address, uint16_t value);

void fake_robotinterface_send_joint_regulation_parameter(int joint_id, int param_id, int param_value);

void fake_robotinterface_send_joint_special_parameter(int joint_id, int param_id, int param_value);


#endif