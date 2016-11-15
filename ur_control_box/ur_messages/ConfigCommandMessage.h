//
// Created by ub1404 on 15. 8. 18.
//

#ifndef UR5_CONFIGCOMMANDMESSAGE_H
#define UR5_CONFIGCOMMANDMESSAGE_H

#include <commons/serialize/SerializeInterface.h>

namespace ur5_message {
    using namespace serialize_module;

    namespace ConfigCommandsTypes {
        enum ConfigCommandsType {
            OPEN_INTERFACE = 0,
            CLOSE_INTERFACE,
            POWER_ON_ROBOT,
            POWER_OFF_ROBOT,
            SET_ROBOT_READY_MODE,
            SET_ROBOT_RUNNING_MODE,
            SET_ROBOT_FREEDRIVE_MODE,
            SET_SECURITY_STOP,
            UNLOCK_SECURITY_STOP
        };
    }

    class ConfigCommandMessage : public SerializeInterface {
    public:
        ConfigCommandMessage() {
            this->initAttributes();
        }

        ~ConfigCommandMessage() {

        }

        int32_t getByteLength() {
            return sizeof(int32_t);
        }

        void initAttributes() {
            func_calls = 0;
        }

        bool serialize(ByteBuffer *msg_out);

    protected:
        bool __deserialize(ByteBuffer *msg_in);

    public:
        //getters
        //usage :
        // if(check_command(OPEN_INTERFACE))
        //      robotinterface_open(0);
        bool check_command(ConfigCommandsTypes::ConfigCommandsType cmd) {
            return (bool) (func_calls & (1 << cmd));
        }

        //setters
        void setOpenInterface();

        void setCloseInterface();

        void setRobotReadyMode();

        void setRobotRunningMode();

        void setRobotFreedriveMode();

        void setSecurityStop();

        void setUnlockSecurityStop();

        void setPowerOnRobot();

        void setPowerOffRobot();

        //getter
        bool isCommandSet(ConfigCommandsTypes::ConfigCommandsType command);

    public:
        void printAttributes() {
            int32_t data = func_calls;
            printf("-------ConfigCommandMessage-----------\n");
            printf("%0X\n", data);

            for (int i = 0; i < 8 * sizeof(data); i++)
                printf("%3d", i);
            printf("\n");
            for (int i = 0; i < 8 * sizeof(data); i++) {
                printf("%3d", (data & 0x01));
                data >>= 1;
            }
            printf("\n\n");
        }

        ConfigCommandMessage makeDummy();

        bool operator!=(const ConfigCommandMessage &A);

        bool operator==(const ConfigCommandMessage &A);

    public:
        int32_t func_calls; //bit-mask

        // TODO : adding robot parameters modulation interface.(ie. tcp, tcp_payload)
    };
}
#endif //UR5_CONFIGCOMMANDMESSAGE_H
