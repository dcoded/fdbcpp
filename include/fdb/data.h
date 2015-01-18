#ifndef INCLUDE_FDB_DATA_H
#define INCLUDE_FDB_DATA_H  

#include <vector>
#include <string>

namespace fdb {

    class data {
    private:
        std::string data_;
        bool valid_;
    public:
        data ();

        /**
         * Explicit copy operator.
         * 
         * Performs a shallow copy (due to managed memory owned by external scoped_ptr).
         * 
         * @param rhs Target data object to copy
         */
        data (const data& rhs);

        /**
         * C-string constructor.
         * 
         * Points to underlying c-string address location to perform
         * transparent type-casting between uint8_t and std::string/
         * const char* interfaces.
         * 
         * @param key_id c-string of ASCII key
         */
        data (const char* key_id);

        /**
         * std::string constructor.
         * 
         * Points to underlying c-string address location to perform
         * transparent type-casting between uint8_t and std::string/
         * const char* interfaces.
         * 
         * @param key_id ascii or binary string of key
         */
        data (std::string key_id);

        /**
         * binary buffer constructor.
         * 
         * Points to buffer address location to perform transparent
         * type-casting between uint8_t and std::string/const char*
         * interfaces.
         * 
         * @param data binary buffer of key
         * @param len  length of key in bytes
         */
        data (const uint8_t* data, int len);

        /**
         * binary buffer constructor.
         * 
         * Points to buffer address location to perform transparent
         * type-casting between uint8_t and std::string/const char*
         * interfaces.
         * 
         * @param data binary buffer of key
         * @param len  length of key in bytes
         */
        data (const void* const data, int len);

        /**
         * Size of key data buffer.
         * 
         * The length of the key (either ASCII or binary) in bytes.
         * @return size of key
         */
        const int size () const;

        /**
         * Type-cast operator to read key as binary buffer.
         * 
         * @return binary buffer
         */
        virtual operator const uint8_t* () const;

        /**
         * Type-cast operator to read key as string
         * 
         * @return string key
         */
        virtual operator std::string () const;

        /**
         * Less-then comparator to allow use in sorted containers.
         * 
         * @return true if and only if this is less than other
         */
        bool operator< (const data &other) const;



        bool valid () const;
    };
}

#endif