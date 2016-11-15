#include "RobotinterfaceFake.h"
#include "stdio.h"
#include "unistd.h"
#include <string.h>
#include <sys/time.h>

void printArrays(const double *val, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.4lf  ", val);
    }
    printf("\n");
}

uint64_t fake_robotinterface_get_step() {
    // printf("fake_robotinterface_get_step\n");
    uint64_t temp = 1;

    return temp;
}

double fake_robotinterface_get_time() {
    // printf("fake_robotinterface_get_time\n");
    static bool first_run = true;
    static timeval t0;
    if (first_run) {
        gettimeofday(&t0, NULL);
        first_run = false;
    }
    timeval t_diff;
    timeval t1;
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t_diff);

    double temp = 0.0;
    temp = t_diff.tv_sec + t_diff.tv_usec / 1000000.0;

    return temp;
}

double fake_robotinterface_get_time_per_step() {
    // printf("fake_robotinterface_get_time_per_step\n");
    double temp = 0.008;

    return temp;
}

void fake_robotinterface_command_position_velocity_acceleration(const double *q, const double *qd, const double *qdd) {
    printf("fake_robotinterface_command_position_velocity_acceleration\n");
    printf("fake_robotinterface_command_position_velocity_acceleration\n");
    printf("q\t: ");
    printArrays(q, 6);
    printf("qd\t: ");
    printArrays(qd, 6);
    printf("qdd\t: ");
    printArrays(qdd, 6);
}

void fake_robotinterface_command_velocity_acceleration(const double *q, const double *qd, const double *qdd) {
    printf("fake_robotinterface_command_velocity_acceleration\n");
    printf("q\t: ");
    printArrays(q, 6);
    printf("qd\t: ");
    printArrays(qd, 6);
    printf("qdd\t: ");
    printArrays(qdd, 6);
}

void fake_robotinterface_command_velocity(const double *qd) {
    printf("fake_robotinterface_command_velocity\n");
    printf("qd\t: ");
    printArrays(qd, 6);
}

void fake_robotinterface_command_joint_position_velocity_acceleration(int joint, double q, double qd) {
    printf("fake_robotinterface_command_joint_position_velocity_acceleration\n");
    printf("joint : %2d q : %+6.4lf qd : %+6.4lf\n", joint, q, qd);
}

void fake_robotinterface_command_velocity_security_torque_control_torque(const double *qd,
                                                                         const double *security_torque,
                                                                         const double *control_torque,
                                                                         const double *softness) {
    printf("fake_robotinterface_command_velocity_security_torque_control_torque\n");
    printf("qd\t: ");
    printArrays(qd, 6);
    printf("seq_torq\t: ");
    printArrays(security_torque, 6);
    printf("ctrl_torq\t: ");
    printArrays(control_torque, 6);
    printf("softness\t: ");
    printArrays(softness, 6);
}

void fake_robotinterface_command_torque(const double *qd, const double *security_torque, const double *control_torque) {
    printf("fake_robotinterface_command_torque\n");
    printf("qd\t: ");
    printArrays(qd, 6);
    printf("seq_torq\t: ");
    printArrays(security_torque, 6);
    printf("ctrl_torq\t: ");
    printArrays(control_torque, 6);
}

void fake_robotinterface_command_empty_command() {
    printf("fake_robotinterface_command_empty_command\n");

}

void fake_robotinterface_master_goto_bootloader_mode() {
    printf("fake_robotinterface_master_goto_bootloader_mode\n");

}

void fake_robotinterface_command_digital_out_port(int port, int value) {
    printf("fake_robotinterface_command_digital_out_port\n");
    printf("port : %d  val : %d\n", port, value);
}

void fake_robotinterface_command_digital_out_bits(unsigned short bits) {
    printf("fake_robotinterface_command_digital_out_bits\n");
    printf("%0X", bits);
}

void fake_robotinterface_command_analog_out_port(int port, double value) {
    printf("fake_robotinterface_command_analog_out_port\n");
    printf("port : %d  val : %.4lf\n", port, value);
}

void fake_robotinterface_command_analog_input_range_port(int port, int range) {
    printf("fake_robotinterface_command_analog_input_range_port\n");
    printf("port : %d  range : %d\n", port, range);
}

void fake_robotinterface_command_analog_output_domain(int port, int type) {
    printf("fake_robotinterface_command_analog_output_domain\n");
    printf("port : %d  type : %d\n", port, type);

}

void fake_robotinterface_command_tool_output_voltage(unsigned char value) {
    printf("fake_robotinterface_command_tool_output_voltage\n");
    printf("value : %d\n", value);
}

void fake_robotinterface_set_tcp(const double *tcp_pose) {
    printf("fake_robotinterface_set_tcp\n");

}

void fake_robotinterface_set_tcp_payload_cog(const double *tcp_payload_cog) {
    printf("fake_robotinterface_set_tcp_payload_cog\n");

}

void fake_robotinterface_set_tcp_payload(double tcp_payload) {
    printf("fake_robotinterface_set_tcp_payload\n");

}

void fake_robotinterface_get_tcp(double *tcp_pose) {
    // printf("fake_robotinterface_get_tcp\n");

}

void fake_robotinterface_get_tcp_payload_cog(double *tcp_pose) {
    // printf("fake_robotinterface_get_tcp_payload_cog\n");

}

double fake_robotinterface_get_tcp_payload() {
    // printf("fake_robotinterface_get_tcp_payload\n");
    double temp = 0.0;

    return temp;
}

void fake_robotinterface_set_tcp_wrench(const double *new_tcp_wrench, const int in_base_coord) {
    printf("fake_robotinterface_set_tcp_wrench\n");

}

void fake_robotinterface_get_tcp_wrench(double *gotten_tcp_wrench) {
    // printf("fake_robotinterface_get_tcp_wrench\n");

}

int fake_robotinterface_is_tcp_wrench_in_base_coord() {
//	printf("fake_robotinterface_is_tcp_wrench_in_base_coord\n");
    int temp = 1;

    return temp;
}

int fake_robotinterface_open(int open_simulated) {
    printf("fake_robotinterface_open\n");
    int temp = 1;

    return temp;
}

int fake_robotinterface_do_open(int open_simulated) {
    printf("fake_robotinterface_do_open\n");
    int temp = 1;

    return temp;
}

int fake_robotinterface_open_allow_bootloader(int open_simulated) {
    printf("fake_robotinterface_open_allow_bootloader\n");
    int temp = 1;

    return temp;
}

void fake_robotinterface_read_state_blocking() {
    printf("fake_robotinterface_read_state_blocking\n");
    usleep(8000);
}

void fake_robotinterface_send() {
    printf("fake_robotinterface_send\n");

}

int fake_robotinterface_is_robot_connected() {
//	printf("fake_robotinterface_is_robot_connected\n");
    int temp = 1;

    return temp;
}

int fake_robotinterface_close() {
    printf("fake_robotinterface_close\n");
    int temp = 1;

    return temp;
}

uint8_t fake_robotinterface_get_robot_mode() {
    // printf("fake_robotinterface_get_robot_mode\n");
    uint8_t temp = 1;

    return temp;
}

void fake_robotinterface_set_robot_ready_mode() {
    printf("fake_robotinterface_set_robot_ready_mode\n");

}

void fake_robotinterface_set_robot_running_mode() {
    printf("fake_robotinterface_set_robot_running_mode\n");

}

void fake_robotinterface_set_robot_freedrive_mode() {
    printf("fake_robotinterface_set_robot_freedrive_mode\n");

}

uint8_t fake_robotinterface_get_joint_mode(int joint) {
    // printf("fake_robotinterface_get_joint_mode\n");
    uint8_t temp = 1;

    return temp;
}

uint8_t fake_robotinterface_get_tool_mode() {
    // printf("fake_robotinterface_get_tool_mode\n");
    uint8_t temp = 1;

    return temp;
}

uint8_t fake_robotinterface_get_message_count() {
    // printf("fake_robotinterface_get_message_count\n");
    uint8_t temp = 0;

    return temp;
}

int fake_robotinterface_get_message(struct message_t *message) {
    // printf("fake_robotinterface_get_message\n");
    int temp = 1;

    return temp;
}

int fake_robotinterface_get_message_codes(struct message_t *msg, int *error_code, int *error_argument) {
    // printf("fake_robotinterface_get_message_codes\n");
    int temp = 1;

    return temp;
}

void fake_robotinterface_power_on_robot() {
    printf("fake_robotinterface_power_on_robot\n");

}

void fake_robotinterface_power_off_robot() {
    printf("fake_robotinterface_power_off_robot\n");

}

void fake_robotinterface_security_stop(char joint_code, int error_state, int error_argument) {
    printf("fake_robotinterface_security_stop\n");
    printf("joint_code:%d\n", joint_code);
    printf("error_state:%d\n", error_state);
    printf("error_argument:%d\n", error_argument);
}

int fake_robotinterface_is_power_on_robot() {
//	printf("fake_robotinterface_is_power_on_robot\n");
    int temp = 1;

    return temp;
}

int fake_robotinterface_is_security_stopped() {
//	printf("fake_robotinterface_is_security_stopped\n");
    int temp = 0;

    return temp;
}

int fake_robotinterface_is_emergency_stopped() {
//	printf("fake_robotinterface_is_emergency_stopped\n");
    int temp = 0;

    return temp;
}

int fake_robotinterface_is_extra_button_pressed() {
//	printf("fake_robotinterface_is_extra_button_pressed\n");
    int temp = 0;

    return temp;
}

int fake_robotinterface_is_power_button_pressed() {
//	printf("fake_robotinterface_is_power_button_pressed\n");
    int temp = 0;

    return temp;
}

int fake_robotinterface_is_safety_signal_such_that_we_should_stop() {
//	printf("fake_robotinterface_is_safety_signal_such_that_we_should_stop\n");
    int temp = 0;

    return temp;
}

int fake_robotinterface_unlock_security_stop() {
    printf("fake_robotinterface_unlock_security_stop\n");
    int temp = 1;

    return temp;
}

int fake_robotinterface_has_security_message() {
    printf("fake_robotinterface_has_security_message\n");
    int temp = 0;

    return temp;
}

int fake_robotinterface_get_security_message(struct message_t *message, int *error_state, int *error_argument) {
    // printf("fake_robotinterface_get_security_message\n");
    int temp = 1;

    return temp;
}

uint32_t fake_robotinterface_get_master_control_bits() {
    // printf("fake_robotinterface_get_master_control_bits\n");
    uint32_t temp = 0;

    return temp;
}

void fake_robotinterface_get_actual(double *q, double *qd) {
    // printf("fake_robotinterface_get_actual\n");
    memset(q, 0, sizeof(q[0]) * 6);
    memset(qd, 0, sizeof(qd[0]) * 6);
}

void fake_robotinterface_get_actual_position(double *q) {
    // printf("fake_robotinterface_get_actual_position\n");
    memset(q, 0, sizeof(q[0]) * 6);
}

void fake_robotinterface_get_actual_velocity(double *qd) {
    // printf("fake_robotinterface_get_actual_velocity\n");
    memset(qd, 0, sizeof(qd[0]) * 6);
}

void fake_robotinterface_get_actual_current(double *I) {
    // printf("fake_robotinterface_get_actual_current\n");
    memset(I, 0, sizeof(I[0]) * 6);
}

void fake_robotinterface_get_tool_accelerometer_readings(double *ax, double *ay, double *az) {
    // printf("fake_robotinterface_get_tool_accelerometer_readings\n");

}

double fake_robotinterface_get_tcp_force_scalar() {
    // printf("fake_robotinterface_get_tcp_force_scalar\n");
    double temp = 0;

    return temp;
}

void fake_robotinterface_get_tcp_force(double *F) {
    // printf("fake_robotinterface_get_tcp_force\n");

}

void fake_robotinterface_get_tcp_speed(double *V) {
    // printf("fake_robotinterface_get_tcp_speed\n");
    memset(V, 0, sizeof(V[0]) * 6);
}

double fake_robotinterface_get_tcp_power() {
    // printf("fake_robotinterface_get_tcp_power\n");
    double temp = 0.0;

    return temp;
}

double fake_robotinterface_get_power() {
    // printf("fake_robotinterface_get_power\n");
    double temp = 0.0;

    return temp;
}

int fake_robotinterface_get_actual_digital_input(int port) {
    // printf("fake_robotinterface_get_actual_digital_input\n");
    int temp = 0;

    return temp;
}

int fake_robotinterface_get_actual_digital_output(int port) {
    // printf("fake_robotinterface_get_actual_digital_output\n");
    int temp = 0;

    return temp;
}

unsigned short fake_robotinterface_get_actual_digital_input_bits() {
    // printf("fake_robotinterface_get_actual_digital_input_bits\n");
    unsigned short temp = 0;

    return temp;
}

unsigned short fake_robotinterface_get_actual_digital_output_bits() {
    // printf("fake_robotinterface_get_actual_digital_output_bits\n");
    unsigned short temp = 0;

    return temp;
}

double fake_robotinterface_get_actual_analog_input(int port) {
    // printf("fake_robotinterface_get_actual_analog_input\n");
    double temp = 0;

    return temp;
}

double fake_robotinterface_get_actual_analog_output(int port) {
    // printf("fake_robotinterface_get_actual_analog_output\n");
    double temp = 0;

    return temp;
}

unsigned char fake_robotinterface_get_actual_analog_input_range(int port) {
    // printf("fake_robotinterface_get_actual_analog_input_range\n");
    unsigned char temp = 0;

    return temp;
}

unsigned char fake_robotinterface_get_actual_analog_output_domain(int port) {
    // printf("fake_robotinterface_get_actual_analog_output_domain\n");
    unsigned char temp = 0;

    return temp;
}

void fake_robotinterface_get_target(double *q, double *qd, double *qdd) {
    // printf("fake_robotinterface_get_target\n");

}

void fake_robotinterface_get_target_position(double *q) {
    // printf("fake_robotinterface_get_target_position\n");
    memset(q, 0, sizeof(q[0]) * 6);
}

void fake_robotinterface_get_target_velocity(double *qd) {
    // printf("fake_robotinterface_get_target_velocity\n");
    memset(qd, 0, sizeof(qd[0]) * 6);
}

void fake_robotinterface_get_target_acceleration(double *qdd) {
    // printf("fake_robotinterface_get_target_acceleration\n");
    memset(qdd, 0, sizeof(qdd[0]) * 6);
}

void fake_robotinterface_get_target_current(double *I) {
    // printf("fake_robotinterface_get_target_current\n");
    memset(I, 0, sizeof(I[0]) * 6);
}

void fake_robotinterface_get_target_moment(double *m) {
    // printf("fake_robotinterface_get_target_moment\n");
    memset(m, 0, sizeof(m[0]) * 6);
}

unsigned short fake_robotinterface_get_target_digital_output_bits() {
    // printf("fake_robotinterface_get_target_digital_output_bits\n");
    unsigned short temp = 0;

    return temp;
}

double fake_robotinterface_get_target_analog_output(int port) {
    // printf("fake_robotinterface_get_target_analog_output\n");
    double temp = 0;

    return temp;
}

unsigned char fake_robotinterface_get_target_analog_input_range(int port) {
    // printf("fake_robotinterface_get_target_analog_input_range\n");
    unsigned char temp = 0;

    return temp;
}

unsigned char fake_robotinterface_get_target_analog_output_domain(int port) {
    // printf("fake_robotinterface_get_target_analog_output_domain\n");
    unsigned char temp = 0;

    return temp;
}

float fake_robotinterface_get_master_temperature() {
    // printf("fake_robotinterface_get_master_temperature\n");
    float temp = 0;

    return temp;
}

float fake_robotinterface_get_robot_voltage_48V() {
    // printf("fake_robotinterface_get_robot_voltage_48V\n");
    float temp = 0;

    return temp;
}

float fake_robotinterface_get_robot_current() {
    // printf("fake_robotinterface_get_robot_current\n");
    float temp = 0;

    return temp;
}

float fake_robotinterface_get_master_io_current() {
    // printf("fake_robotinterface_get_master_io_current\n");
    float temp = 0.0f;

    return temp;
}

unsigned char fake_robotinterface_get_master_safety_state() {
    // printf("fake_robotinterface_get_master_safety_state\n");
    unsigned char temp = 0;

    return temp;
}

unsigned char fake_robotinterface_get_master_on_off_state() {
    // printf("fake_robotinterface_get_master_on_off_state\n");
    unsigned char temp = 0;

    return temp;
}

void fake_robotinterface_safely_remove_euromap67_hardware() {
    printf("fake_robotinterface_safely_remove_euromap67_hardware\n");

}

void fake_robotinterface_disable_teach_pendant_safety() {
    printf("fake_robotinterface_disable_teach_pendant_safety\n");

}

void fake_robotinterface_get_motor_temperature(float *T) {
    // printf("fake_robotinterface_get_motor_temperature\n");
    memset(T, 0, sizeof(T[0]) * 6);
}

void fake_robotinterface_get_micro_temperature(float *T) {
    // printf("fake_robotinterface_get_micro_temperature\n");
    memset(T, 0, sizeof(T[0]) * 6);

}

void fake_robotinterface_get_joint_voltage(float *V) {
    // printf("fake_robotinterface_get_joint_voltage\n");
    memset(V, 0, sizeof(V[0]) * 6);

}

float fake_robotinterface_get_tool_temperature() {
    // printf("fake_robotinterface_get_tool_temperature\n");
    float temp = 0.0f;

    return temp;
}

float fake_robotinterface_get_tool_voltage_48V() {
    // printf("fake_robotinterface_get_tool_voltage_48V\n");
    float temp = 0.0f;

    return temp;
}

unsigned char fake_robotinterface_get_tool_output_voltage() {
    // printf("fake_robotinterface_get_tool_output_voltage\n");
    unsigned char temp = 0;

    return temp;
}

float fake_robotinterface_get_tool_current() {
    // printf("fake_robotinterface_get_tool_current\n");
    float temp = 0.0f;

    return temp;
}

uint8_t fake_robotinterface_is_euromap_hardware_installed() {
//	printf("fake_robotinterface_is_euromap_hardware_installed\n");
    uint8_t temp = 0;

    return temp;
}

uint8_t fake_robotinterface_get_euromap_input(uint8_t input_bit_number) {
    // printf("fake_robotinterface_get_euromap_input\n");
    uint8_t temp = 0;

    return temp;
}

uint8_t fake_robotinterface_get_euromap_output(uint8_t output_bit_number) {
    // printf("fake_robotinterface_get_euromap_output\n");
    uint8_t temp = 0;

    return temp;
}

void fake_robotinterface_set_euromap_output(uint8_t output_bit_number, uint8_t desired_value) {
    printf("fake_robotinterface_set_euromap_output\n");

}

uint32_t fake_robotinterface_get_euromap_input_bits() {
    // printf("fake_robotinterface_get_euromap_input_bits\n");
    uint32_t temp = 0;

    return temp;
}

uint32_t fake_robotinterface_get_euromap_output_bits() {
    // printf("fake_robotinterface_get_euromap_output_bits\n");
    uint32_t temp = 0;

    return temp;
}

uint16_t fake_robotinterface_get_euromap_24V_voltage() {
    // printf("fake_robotinterface_get_euromap_24V_voltage\n");
    uint16_t temp = 0;

    return temp;
}

uint16_t fake_robotinterface_get_euromap_24V_current() {
    // printf("fake_robotinterface_get_euromap_24V_current\n");
    uint16_t temp = 0;

    return temp;
}

uint16_t fake_robotinterface_get_general_purpose_register(int address) {
    // printf("fake_robotinterface_get_general_purpose_register\n");
    uint16_t temp = 0;

    return temp;
}

void fake_robotinterface_set_general_purpose_register(int address, uint16_t value) {
    printf("fake_robotinterface_set_general_purpose_register\n");
    printf("address : %d\n", address);
    printf("value : %d\n", value);
}

void fake_robotinterface_send_joint_regulation_parameter(int joint_id, int param_id, int param_value) {
    printf("fake_robotinterface_send_joint_regulation_parameter\n");
    printf("joint_id : %d\n", joint_id);
    printf("param_id : %d\n", param_id);
    printf("param_value : %d\n", param_value);
}

void fake_robotinterface_send_joint_special_parameter(int joint_id, int param_id, int param_value) {
    printf("fake_robotinterface_send_joint_special_parameter\n");
    printf("joint_id : %d\n", joint_id);
    printf("param_id : %d\n", param_id);
    printf("param_value : %d\n", param_value);
}

