//
// Created by ub1404 on 15. 8. 13.
//
#include "JointCommandMessage.h"
#include "cmd_utils.h"

namespace ur5_message {
    JointCommandMessage::JointCommandMessage() {
        this->initAttributes();
    }

    JointCommandMessage::~JointCommandMessage() {

    }

    bool JointCommandMessage::serialize(ByteBuffer *msg_out) {
        msg_out->load(cmd_type);
        msg_out->load(sequence);
        msg_out->load(q[0]);
        msg_out->load(q[1]);
        msg_out->load(q[2]);
        msg_out->load(q[3]);
        msg_out->load(q[4]);
        msg_out->load(q[5]);

        msg_out->load(qd[0]);
        msg_out->load(qd[1]);
        msg_out->load(qd[2]);
        msg_out->load(qd[3]);
        msg_out->load(qd[4]);
        msg_out->load(qd[5]);

        msg_out->load(qdd[0]);
        msg_out->load(qdd[1]);
        msg_out->load(qdd[2]);
        msg_out->load(qdd[3]);
        msg_out->load(qdd[4]);
        msg_out->load(qdd[5]);

        msg_out->load(softness[0]);
        msg_out->load(softness[1]);
        msg_out->load(softness[2]);
        msg_out->load(softness[3]);
        msg_out->load(softness[4]);
        msg_out->load(softness[5]);

        return true;
    }

    bool JointCommandMessage::__deserialize(ByteBuffer *msg_in) {
        if (msg_in->getRemainedBufferSize() != this->getByteLength()) {
            return false;
        }
        msg_in->unload(cmd_type);
        msg_in->unload(sequence);
        msg_in->unload(q[0]);
        msg_in->unload(q[1]);
        msg_in->unload(q[2]);
        msg_in->unload(q[3]);
        msg_in->unload(q[4]);
        msg_in->unload(q[5]);

        msg_in->unload(qd[0]);
        msg_in->unload(qd[1]);
        msg_in->unload(qd[2]);
        msg_in->unload(qd[3]);
        msg_in->unload(qd[4]);
        msg_in->unload(qd[5]);

        msg_in->unload(qdd[0]);
        msg_in->unload(qdd[1]);
        msg_in->unload(qdd[2]);
        msg_in->unload(qdd[3]);
        msg_in->unload(qdd[4]);
        msg_in->unload(qdd[5]);

        msg_in->unload(softness[0]);
        msg_in->unload(softness[1]);
        msg_in->unload(softness[2]);
        msg_in->unload(softness[3]);
        msg_in->unload(softness[4]);
        msg_in->unload(softness[5]);
        return true;
    }

    void JointCommandMessage::initAttributes() {
        this->cmd_type = 0;
        this->sequence = 0;
        for (int i = 0; i < 6; i++) {
            this->q[i] = 0.0;
            this->qd[i] = 0.0;
            this->qdd[i] = 0.0;
            this->softness[i] = 0.0;
        }
    }

    JointCommandMessage JointCommandMessage::makeDummy() {
        this->cmd_type = 1;
        this->sequence = 123;
        for (int i = 0; i < 6; i++) {
            this->q[i] = i + 1.23548;
            this->qd[i] = 0.12354878;
            this->qdd[i] = i * 1.2348;
            this->softness[i] = 0.12348;
        }
    }

    bool JointCommandMessage::operator!=(const JointCommandMessage &A) {
        return !operator==(A);
    }

    bool JointCommandMessage::operator==(const JointCommandMessage &A) {
        if (cmd_type != A.cmd_type)
            return false;
        if (sequence != A.sequence)
            return false;
        for (int i = 0; i < 6; i++) {
            if (!compareDoubles(q[i], A.q[i])) {
                return false;
            }
            if (!compareDoubles(qd[i], A.qd[i])) {
                return false;
            }
            if (!compareDoubles(qdd[i], A.qdd[i])) {
                return false;
            }
            if (!compareDoubles(softness[i], A.softness[i])) {
                return false;
            }
        }
        return true;
    }

    void JointCommandMessage::setTorqueCommand(const double *_qd, const double *_security_torque,
                                               const double *_control_torque, const int &_seq) {
        this->cmd_type = JointCommandTypes::TORQUE_COMMAND;
        ::memcpy(this->qd, _qd, sizeof(this->qd[0]) * 6);
        ::memcpy(this->security_torque, _security_torque, sizeof(this->security_torque[0]) * 6);
        ::memcpy(this->torque, _control_torque, sizeof(this->torque[0]) * 6);
        this->sequence = _seq;
    }

    void JointCommandMessage::setPVACommand(const double *_q, const double *_qd, const double *_qdd,
                                            const int &_seq) {
        this->cmd_type = JointCommandTypes::PVA_COMMAND;
        ::memcpy(this->q, _q, sizeof(this->q[0]) * 6);
        ::memcpy(this->qd, _qd, sizeof(this->qd[0]) * 6);
        ::memcpy(this->qdd, _qdd, sizeof(this->qdd[0]) * 6);
        this->sequence = _seq;
    }

    void JointCommandMessage::setVelocityCommand(const double *_qd, const int &_seq) {
        this->cmd_type = JointCommandTypes::VEL_COMMAND;
        ::memcpy(this->qd, _qd, sizeof(this->qd[0]) * 6);
        this->sequence = _seq;
    }

}
