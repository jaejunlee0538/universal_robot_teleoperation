//
// Created by ub1404 on 15. 8. 4.
//

#include <commons/serialize/ByteBuffer.h>
#include <commons/serialize/SerializeInterface.h>

namespace serialize_module {
    ByteBuffer::ByteBuffer() {
        this->_unload_idx = 0;
    }

    ByteBuffer::~ByteBuffer() {

    }

    void ByteBuffer::clear(void) {
        _buffer.clear();
        _unload_idx = 0;
    }

    int ByteBuffer::getBufferSize(void) {
        return _buffer.size();
    }

    int ByteBuffer::getRemainedBufferSize(void) {
        return _buffer.size() - _unload_idx;
    }

    const char *ByteBuffer::getBuffer(void) {
        return _buffer.data();
    }

    void ByteBuffer::copyFrom(const char *data, int len) {
        this->_buffer.resize(len);
        ::memcpy(_buffer.data(), data, len);
    }

    void ByteBuffer::printBuffers(void) {
        if (_buffer.size() == 0) {
            printf("No data\n");
            return;
        }
        printf("%d BYTES :\n\t", _buffer.size());
        for (size_t i = 1; i <= _buffer.size(); i++) {
            printf("%02X", (unsigned char) _buffer[i - 1]);
            if (i % 4 == 0) {
                if (i % 32 == 0)
                    printf("\n\t");
                else
                    printf("\t");
            }
        }
        printf("\n");
    }

    void ByteBuffer::load(bool data) {
        load(&data, sizeof(data));
    }

    void ByteBuffer::load(int8_t data) {
        load(&data, sizeof(data));
    }

    void ByteBuffer::load(uint8_t data) {
        load(&data, sizeof(data));
    }

    void ByteBuffer::load(int32_t data) {
        load(&data, sizeof(data));
    }

    void ByteBuffer::load(uint32_t data) {
        load(&data, sizeof(data));
    }

    void ByteBuffer::load(double data) {
        load(&data, sizeof(data));
    }

    void ByteBuffer::load(float data) {
        load(&data, sizeof(data));
    }

    void ByteBuffer::load(const void *p_data, int len) {
        _buffer.insert(_buffer.end(), (char *) p_data, (char *) p_data + len);
    }

    void ByteBuffer::load(SerializeInterface *data) {
        data->serialize(this);
    }

    bool ByteBuffer::unload(bool &data) {
        return unload(&data, sizeof(data));
    }

    bool ByteBuffer::unload(int8_t &data) {
        return unload(&data, sizeof(data));
    }

    bool ByteBuffer::unload(uint8_t &data) {
        return unload(&data, sizeof(data));
    }

    bool ByteBuffer::unload(int32_t &data) {
        return unload(&data, sizeof(data));
    }

    bool ByteBuffer::unload(uint32_t &data) {
        return unload(&data, sizeof(data));
    }

    bool ByteBuffer::unload(double &data) {
        return unload(&data, sizeof(data));
    }

    bool ByteBuffer::unload(float &data) {
        return unload(&data, sizeof(data));
    }

    bool ByteBuffer::unload(void *p_data, int len) {
        if (_buffer.size() - _unload_idx < len) {
            this->clear();
            return false;
        }
        char *p_char = (char *) p_data;
        ::memcpy(p_char, &_buffer[_unload_idx], len);
        _unload_idx += len;
        return true;
    }

    bool ByteBuffer::unload(SerializeInterface *data) {
        return data->deserialize(this);
    }
}