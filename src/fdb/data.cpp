#include <fdb/data.h>
namespace fdb {

    data::data ()
    : valid_ (false) {}

    data::data (const data& rhs)
    : data_ (rhs.data_) {}

    data::data (const char* key)
    : data (reinterpret_cast <const uint8_t*> (key), strlen(key)) {}

    data::data (std::string key) 
    : data (reinterpret_cast <const uint8_t*> (key.c_str ()), key.size ()) {}

    data::data (const uint8_t* key, int length)
    : data_ (std::string (key, key + length))
    , valid_ (true) {}

    data::data (const void* key, int length)
    : data (reinterpret_cast <const uint8_t*> (key), length) {}

    const int data::size () const {
        return data_.size ();
    }

    data::operator const uint8_t* () const {
        return reinterpret_cast<const uint8_t*> (data_.c_str ());
    }

    data::operator std::string () const {
        return data_;
    }

    bool data::operator< (const data &b) const {
        return (static_cast <std::string> (*this) < static_cast <std::string> (b));
    }

    bool data::valid () const { return valid_; }
}