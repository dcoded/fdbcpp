#ifndef INCLUDE_FDB_DATA_H
#define INCLUDE_FDB_DATA_H  
#include <vector>

namespace fdb {

    class data {
    private:
        std::string data_;
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
    };

    data::data () {}

    data::data (const data& rhs)
    : data_ (rhs.data_) {}

    data::data (const char* key)
    : data (reinterpret_cast <const void*> (key), strlen(key)) {}

    data::data (std::string key) 
    : data (reinterpret_cast <const void*> (key.c_str ()), key.size ()) {}

    data::data (const uint8_t* key, int length)
    : data_ (std::string (key, key + length)) {}

    data::data (const void* key, int length)
    : data (reinterpret_cast <const uint8_t*> (key), length) {}

    const int data::size () const { return data_.size (); }

    data::operator const uint8_t* () const {
        return reinterpret_cast<const uint8_t*> (data_.c_str ());
    }

    data::operator std::string () const {
        return data_;
    }

    bool data::operator< (const data &b) const {
        return (static_cast <std::string> (*this) < static_cast <std::string> (b));
    }
}

#endif