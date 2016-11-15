//
// Created by ub1404 on 15. 8. 4.
//

#include <commons/serialize/ByteBufferEndian.h>

namespace serialize_module {

    ByteBufferEndian::Endian ByteBufferEndian::_system_endian = ByteBufferEndian::INVALID;

    void ByteBufferEndian::load_without_byte_swap(const void *p_data, int len) {
        _buffer.insert(_buffer.end(), (char *) p_data, (char *) p_data + len);
    }

    void ByteBufferEndian::load_with_byte_swap(const void *p_data, int len) {
        const char *p_char = (const char *) p_data;
        int sz_buf = _buffer.size() + len;
        _buffer.resize(sz_buf);
        sz_buf--;
        for (int i = 0; i < len; i++, sz_buf--, p_char++) {
            _buffer[sz_buf] = *p_char;
        }
    }

    bool ByteBufferEndian::unload_without_byte_swap(void *p_data, int len) {
        if (_buffer.size() - _unload_idx < len) {
            this->clear();
            return false;
        }
        char *p_char = (char *) p_data;
        for (int i = 0; i < len; i++, p_char++, _unload_idx++)
            *p_char = _buffer[_unload_idx];
        return true;
    }

    bool ByteBufferEndian::unload_with_byte_swap(void *p_data, int len) {
        if (_buffer.size() - _unload_idx < len) {
            this->clear();
            return false;
        }
        char *p_char = ((char *) p_data) + (len - 1);
        for (int i = 0; i < len; i++, p_char--, _unload_idx++)
            *p_char = _buffer[_unload_idx];
        return true;
    }

//Runtime check for endian-ness
    bool ByteBufferEndian::is_big_endian(void) {
        short word = 0x4321;
        if ((*(char *) &word) != 0x21)
            return true;
        else
            return false;
    }
}