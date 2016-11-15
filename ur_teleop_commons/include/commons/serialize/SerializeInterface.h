//
// Created by ub1404 on 15. 8. 13.
//

#ifndef COMMMODULE_SERIALIZEINTERFACE_H
#define COMMMODULE_SERIALIZEINTERFACE_H

#include "ByteBuffer.h"

namespace serialize_module {

    class SerializeInterface {
    public:
        SerializeInterface() {
            this->is_message_updated = false;
        }

        virtual int32_t getByteLength() = 0;    //must be implemented

        virtual bool serialize(ByteBuffer *msg_out) = 0;    //must be implemented

        /*
         * !!!Do not implement this method.
         *
         *  message size check.
         *  if deserialization succeed,
         *      set true is_message_update flag.
         *  otherwise
         *      set false is_message_update flag.
         */
        bool deserialize(ByteBuffer *msg_in) {
            if (this->__deserialize(msg_in))
                this->is_message_updated = true;
            else
                this->is_message_updated = false;

            return this->is_message_updated;
        }

        void reset() {
            this->is_message_updated = false;
        }

        bool isMessageUpdated() {
            return this->is_message_updated;
        }

        virtual void printAttributes(){}

    protected:
        virtual bool __deserialize(ByteBuffer *msg_in) = 0; //must be implemented

        /*
         * Set true after successfully being updated by __deserialize call.
         */
        bool is_message_updated;

    public:
        /* Declare attributes here in implementation*/
        //example...

        //int32_t sequence;
        //double joint_angle[6];
        //double joint_speed[6];
        //double joint_torque[6];
    };
}
#endif //COMMMODULE_SERIALIZEINTERFACE_H
