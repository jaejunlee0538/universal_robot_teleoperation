//
// Created by ub1404 on 15. 8. 13.
//

#ifndef COMMMODULE_JOINTCOMMANDMESSAGE_H
#define COMMMODULE_JOINTCOMMANDMESSAGE_H

#include <commons/serialize/SerializeInterface.h>

namespace ur5_message {
    using namespace serialize_module;

    namespace JointCommandTypes {
        enum JointCommandType {
	        NO_COMMAND = 1,
            PVA_COMMAND,
            VEL_COMMAND,
            TORQUE_COMMAND
        };
    }

    class JointCommandMessage : public SerializeInterface {
    public:
        JointCommandMessage();

        ~JointCommandMessage();

        int32_t getByteLength() //implementation
        {
            return (24 * sizeof(double) + 2 * sizeof(int32_t));
        }

        void initAttributes();

        bool serialize(ByteBuffer *msg_out); //implementation

    protected:
        bool __deserialize(ByteBuffer *msg_in); //implementation

    public:
        void setTorqueCommand(const double *_qd, const double *_security_torque, const double *_control_torque,
                              const int &_seq);

        void setPVACommand(const double *_q, const double *_qd, const double *_qdd, const int &_seq);

        void setVelocityCommand(const double *_qd, const int &_seq);

        void printAttributes() {
            printf("cmd_type\t\t: %d\n", cmd_type);
            printf("seq\t\t: %d\n", sequence);
            printf("q[0~5]\t\t: ");
            for (int i = 0; i < 6; i++) {
                printf("%+6.10f ", q[i]);
            }
            printf("\nqd[0~5]\t\t: ");
            for (int i = 0; i < 6; i++) {
                printf("%+6.10f ", qd[i]);
            }
            printf("\nqdd[0~5]\t\t: ");
            for (int i = 0; i < 6; i++) {
                printf("%+6.10f ", qdd[i]);
            }
            printf("\nsoftneww[0~5]\t\t: ");
            for (int i = 0; i < 6; i++) {
                printf("%+6.10f ", softness[i]);
            }
            printf("\n\n");
        }

        JointCommandMessage makeDummy();

        bool operator!=(const JointCommandMessage &A);

        bool operator==(const JointCommandMessage &A);

    public:
        int32_t cmd_type;
        int32_t sequence;

        union {
            double q[6];
            double security_torque[6];
        };
        double qd[6];
        union {
            double qdd[6];
            double torque[6];
        };
        double softness[6];
    };
}

#endif //COMMMODULE_MESSAGEJOINTCOMMAND_H
