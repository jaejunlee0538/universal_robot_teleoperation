//
// Created by ub1404 on 15. 8. 18.
//

#ifndef UR5_ROBOTSTATEMESSAGE_H
#define UR5_ROBOTSTATEMESSAGE_H
#include <commons/serialize/SerializeInterface.h>
#include "../ur_c_api/robotinterface.h"
#include "../ur_c_api/microprocessor_commands.h"

namespace ur5_message {
        using namespace serialize_module;

        class RobotStateMessage : public SerializeInterface {
        public:
            RobotStateMessage() {
                initAttributes();
            }

            ~RobotStateMessage() {

            }

            int32_t getByteLength() {
                return sizeof(double) * (12 * 6 + 3 + 5) +
                       sizeof(uint8_t) * (6 + 3 + 1);
            }

            void initAttributes();

            bool serialize(ByteBuffer *msg_out);

        protected:
            bool __deserialize(ByteBuffer *msg_in);

        private:
            uint8_t get_flags_in_byte();

            void unload_flags(uint8_t data);

        public:
            void printAttributes() {
                printf("-------RobotStateMessage-----------\n");
                printf("mode\t\t: %d\n", robot_mode);
                printf("time\t\t: %.3f\n", robot_time);
                printf("\n\n");
            }

            /*
             * GetDummy was static member.
             * But with static member, it seems like dynamic binding is not working as I intended.
             * It always ended up with segmentation fault error when calling SerializeInterface::getByteLength()
             */
            RobotStateMessage makeDummy();

            bool operator!=(const RobotStateMessage &A);

            bool operator==(const RobotStateMessage &A);

        public:
            //TODO : specify each attributes's corresponding function calls in robotinterface.h

            //total 27 attributes.

            //robot states(8 attr)
            uint8_t robot_mode;
            double robot_time;
            bool is_robot_connected;
            bool is_power_on_robot; //safety signal will be compressed into single uint8_t data.
            bool is_security_stopped;
            bool is_emergency_stopped;
            bool is_extra_button_pressed;
            bool is_power_button_pressed;
            bool is_safety_signal_such_that_we_should_stop;

            //joints state(11 attr)
            uint8_t joint_modes[6];
            double q_actual[6];
            double qd_actual[6];
            double i_actual[6];
            double q_target[6];
            double qd_target[6];
            double qdd_target[6];
            double i_target[6];
            double moment_target[6];
            double tcp_force[6];
            double tcp_speed[6];

            //configurations (7 attr)
            double tcp_wrench[6];
            double tcp_pose[6];
            double tcp_force_scalar;
            double tcp_power;
            double tcp_payload;
            double tcp_payload_cog[3];
            double power;

            // digital/analog IO (2 attr)
            uint8_t digital_inputs; //
            uint8_t digital_outpus; //

            //TODO : analog input/output
            //TODO : create general purpose Digital/Analog IO command
        };
    }


#endif //UR5_ROBOTSTATEMESSAGE_H
