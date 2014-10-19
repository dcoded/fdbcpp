#ifndef INCLUDE_FDB_KEY_H
#define INCLUDE_FDB_KEY_H

#include "data.h"

namespace fdb {

    enum key_selector {
        // #define FDB_KEYSEL_LAST_LESS_THAN(k, l) k, l, 0, 0
        LAST_LESS_THAN = 0x0,
        // #define FDB_KEYSEL_FIRST_GREATER_OR_EQUAL(k, l) k, l, 0, 1
        FIRST_GREATER_THAN_OR_EQUAL = 0x1,
        // #define FDB_KEYSEL_LAST_LESS_OR_EQUAL(k, l) k, l, 1, 0
        LAST_LESS_OR_EQUAL = 0x2,
        // #define FDB_KEYSEL_FIRST_GREATER_THAN(k, l) k, l, 1, 1
        FIRST_GREATER_THAN = 0x3
    };

    class key : public data {
    private:
        int equal_;
        int offset_;

    public:
        key ();
        key (const key& rhs);

        key (const char* key_id, key_selector sel = key_selector::FIRST_GREATER_THAN_OR_EQUAL);
        key (std::string key_id, key_selector sel = key_selector::FIRST_GREATER_THAN_OR_EQUAL);

        key (const uint8_t* key_id   , int len, key_selector sel = key_selector::FIRST_GREATER_THAN_OR_EQUAL);
        key (const void* const key_id, int len, key_selector sel = key_selector::FIRST_GREATER_THAN_OR_EQUAL);

        const int equal () const;
        const int offset () const;
    };

    key::key () : data () {}
    key::key (const key& rhs)
    : data (rhs) {
        equal_  = rhs.equal_;
        offset_ = rhs.offset_;
    }

    key::key (const char* key_id, key_selector sel)
    : data (key_id)
    , equal_ (sel & 0x2)
    , offset_ (sel & 0x1) {}

    key::key (std::string key_id, key_selector sel)
    : data (key_id)
    , equal_ (sel & 0x2)
    , offset_ (sel & 0x1) {}

    key::key (const uint8_t* key_id, int len, key_selector sel)
    : data (key_id, len)
    , equal_ (sel & 0x2)
    , offset_ (sel & 0x1) {}

    key::key (const void* const key_id, int len, key_selector sel)
    : data (key_id, len)
    , equal_ (sel & 0x2)
    , offset_ (sel & 0x1) {}

    const int key::equal () const { return equal_; }
    const int key::offset () const { return offset_; }
}

#endif