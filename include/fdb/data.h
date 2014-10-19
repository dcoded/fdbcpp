#ifndef INCLUDE_FDB_DATA_H
#define INCLUDE_FDB_DATA_H  

namespace fdb {

    class data {
    private:
        const uint8_t* data_;
        int size_;
    public:
        data ();
        data (const data& rhs);

        data (const char* key_id);
        data (std::string key_id);
        data (const uint8_t* data, int len);
        data (const void* const data, int len);

        const int size () const;

        virtual operator const uint8_t* () const;
        virtual operator std::string () const;

        bool operator< (const data &b) const;
    };

    data::data () {}

    data::data (const data& rhs) {
        data_ = rhs.data_;
        size_ = rhs.size_;
    }

    data::data (const char* key_id)
    : data_ (reinterpret_cast <const uint8_t*> (key_id))
    , size_ (strlen (key_id))  {}

    data::data (std::string key_id)
    : data_ (reinterpret_cast <const uint8_t*> (key_id.c_str ()))
    , size_ (key_id.size ()) {}

    data::data (const uint8_t* data, int length)
    : data_ (data)
    , size_ (length) {}

    data::data (const void* const data, int length)
    : data_ (reinterpret_cast<const uint8_t*> (data))
    , size_ (length) {}

    const int data::size () const { return size_; }

    data::operator const uint8_t* () const {
        return data_;
    }

    data::operator std::string () const {
        return std::string (reinterpret_cast<const char*>(data_), size_);
    }

    bool data::operator< (const data &b) const {
        return (std::string (reinterpret_cast<const char*>(data_), size_) <
            std::string (reinterpret_cast<const char*>(b.data_), b.size_));
    }
}

#endif