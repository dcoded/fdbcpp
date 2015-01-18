#ifndef INCLUDE_FDB_KEY_H
#define INCLUDE_FDB_KEY_H

#include "data.h"

namespace fdb {

    /** @enum key_selector
     *  
     *  Predefined selectors to use when retrieving keys and key ranges.
     */
    enum key_selector {
        // #define FDB_KEYSEL_LAST_LESS_THAN(k, l) k, l, 0, 0
        LAST_LESS_THAN = 0x0, /**< Use the previous key before the defined key */
        // #define FDB_KEYSEL_FIRST_GREATER_OR_EQUAL(k, l) k, l, 0, 1
        FIRST_GREATER_THAN_OR_EQUAL = 0x1 /**< Use either the defined key or the next possible key */,
        // #define FDB_KEYSEL_LAST_LESS_OR_EQUAL(k, l) k, l, 1, 0
        LAST_LESS_OR_EQUAL = 0x2 /**< Use either the defined key or the previous possible key */,
        // #define FDB_KEYSEL_FIRST_GREATER_THAN(k, l) k, l, 1, 1
        FIRST_GREATER_THAN = 0x3 /**< Use the first key after the defined key */
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
}

#endif