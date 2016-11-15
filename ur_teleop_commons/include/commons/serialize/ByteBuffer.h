//
// Created by ub1404 on 15. 8. 4.
//

#ifndef UNTITLED_BYTEBUFFER_H
#define UNTITLED_BYTEBUFFER_H

#include <endian.h>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


namespace serialize_module {
    class SerializeInterface;

    /*
 * ByteBuffer Class
 *  Basic buffer object for message serialization.
 *  This class does not take endian-ness into account.
 *  So, any byte swapping is not contained.
 */
    class ByteBuffer {
    public:
        ByteBuffer();

        virtual ~ByteBuffer();

        /*
         * Clear all buffer.
         *
         */
        void clear(void);

        /*
         * Get loaded buffer size.
         */
        int getBufferSize(void);

        /*
         * Get size of buffer which yet to be unloaded.
         */
        int getRemainedBufferSize(void);

        /*
         * Get pointer to raw buffer.
         */
        const char *getBuffer(void);

        /*
         * Copy raw bytes data from external buffer.
         */
        void copyFrom(const char *data, int len);

        /*
         * Print out buffer data in hex on console.
         * For debugging
         */
        void printBuffers(void);

        /*
         * Methods for loading data on ByteBuffer object for different data types.
         * !! Note that 'load' method append new data at the end of _buffer.
         */
        void load(bool data);

        void load(int8_t data);

        void load(uint8_t data);

        void load(int32_t data);

        void load(uint32_t data);

        void load(double data);

        void load(float data);

        void load(SerializeInterface *data);

        virtual void load(const void *p_data, int len);

        /*
         * Methods for unloading data from ByteBuffer object for different data types.
         * !! Note that 'unload' method does not change _buffer at all,
         * instead it increase _unload_idx to spot the location of data to be unloaded.
         * As 'unload' method unloads data sequentially, 'unload' method must be called
         * in the same sequence with that of 'load' calls.
         */
        bool unload(bool &data);

        bool unload(int8_t &data);

        bool unload(uint8_t &data);

        bool unload(int32_t &data);

        bool unload(uint32_t &data);

        bool unload(double &data); //TODO : Test double, float bytes size.
        bool unload(float &data);

        bool unload(SerializeInterface *data);

        virtual bool unload(void *p_data, int len);

    protected:
        std::vector<char> _buffer;
        int32_t _unload_idx;
    };
}


#endif //UNTITLED_BYTEBUFFER_H
