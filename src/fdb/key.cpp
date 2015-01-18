#include <fdb/key.h>

namespace fdb {

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