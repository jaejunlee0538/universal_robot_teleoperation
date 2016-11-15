//
// Created by ub1404 on 15. 8. 4.
//

#ifndef UNTITLED_BYTEBUFFERENDIAN_H
#define UNTITLED_BYTEBUFFERENDIAN_H

#include "ByteBuffer.h"

namespace serialize_module {
/*
 * ByteBufferEndian
 *  Abstraction class for implementing LittleEndianByteBuffer and BigEndianByteBuffer classes.
 *  First being created, it conduct run-time check for figuring out current system's endian-ness.
 *  While load and unload methods in ByteBuffer have implementations,
 *  ByteBufferEndian class make them as pure abstract methods.
 *  load and unload methods are implemented at LittleEndianByteBuffer and BigEndianByteBuffer classes.
 *
 * Purpose of this class group
 *  - you don't need to care about the endian-ness of your system.
 *    If you serialize class/struct using one of ByteBufferEndian group, ie, LittleEndianByteBuffer,
 *    it automatically generate a byte stream which compatible with little endian system.
 *    If your system is using little-endian byte order,
 *      LittleEndianByteBuffer will load and unload data as it is.
 *    but if your system is big-endian,
 *      LittleEndianByteBuffer will swap bytes before loading and unloading data.
 */
    class BigEndianByteBuffer;

    class LittleEndianByteBuffer;

//typedef BigEndianByteBuffer AlignedByteBuffer;
    typedef LittleEndianByteBuffer AlignedByteBuffer;

    class ByteBufferEndian : public ByteBuffer {
    public:
        enum Endian {
            INVALID = 0,
            LITTLE,
            BIG
        };

        ByteBufferEndian() {
            if (ByteBufferEndian::_system_endian == ByteBufferEndian::INVALID) {
                printf("This system is ");
                if (is_big_endian()) {
                    printf("Big Endian.\n");
                    ByteBufferEndian::_system_endian = ByteBufferEndian::BIG;
                }
                else {
                    printf("Little Endian.\n");
                    ByteBufferEndian::_system_endian = ByteBufferEndian::LITTLE;
                }
            }
            p_load = NULL;
            p_unload = NULL;
        }

        virtual ~ByteBufferEndian() {

        }

        virtual void load(const void *p_data, int len) = 0;

        virtual bool unload(void *p_data, int len) = 0;

    protected:
        typedef void (ByteBufferEndian::*p_load_type)(const void *, int);

        typedef bool (ByteBufferEndian::*p_unload_type)(void *, int);

        static Endian _system_endian;
        Endian _desired_endian;

        p_load_type p_load;
        p_unload_type p_unload;

        void load_without_byte_swap(const void *p_data, int len);

        void load_with_byte_swap(const void *p_data, int len);

        bool unload_without_byte_swap(void *p_data, int len);

        bool unload_with_byte_swap(void *p_data, int len);

        //Runtime check for endian-ness
        bool is_big_endian(void);
    };

/*
 * LittleEndianByteBuffer
 *
 */
    class LittleEndianByteBuffer : public ByteBufferEndian {
    public:
        LittleEndianByteBuffer() {
            if (_system_endian == ByteBufferEndian::BIG) {
                p_load = &LittleEndianByteBuffer::load_with_byte_swap;
                p_unload = &LittleEndianByteBuffer::unload_with_byte_swap;
            }
            else {
                p_load = &LittleEndianByteBuffer::load_without_byte_swap;
                p_unload = &LittleEndianByteBuffer::unload_without_byte_swap;
            }
        }

        void load(const void *p_data, int len) {
            (this->*p_load)(p_data, len);
        }

        bool unload(void *p_data, int len) {
            return (this->*p_unload)(p_data, len);
        }
    };

/*
 * BigEndianByteBuffer
 */
    class BigEndianByteBuffer : public ByteBufferEndian {
    public:
        BigEndianByteBuffer() {
            if (_system_endian == ByteBufferEndian::LITTLE) {
                p_load = &BigEndianByteBuffer::load_with_byte_swap;
                p_unload = &BigEndianByteBuffer::unload_with_byte_swap;
            }
            else {
                p_load = &BigEndianByteBuffer::load_without_byte_swap;
                p_unload = &BigEndianByteBuffer::unload_without_byte_swap;
            }
        }

        void load(const void *p_data, int len) {
            (this->*p_load)(p_data, len);
        }

        bool unload(void *p_data, int len) {
            return (this->*p_unload)(p_data, len);
        }
    };
}
#endif //UNTITLED_BYTEBUFFERENDIAN_H
