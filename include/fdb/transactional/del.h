#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_DEL_H
#define INCLUDE_FDB_TRANSACTIONAL_DEL_H

#include "../key.h"

namespace fdb {
    class del : public transactional </* return */ void, /* arg types */ fdb::key> {
    public: 
        using transactional::transactional;
        virtual void execute (fdb::key key);
    };

    void del::execute (fdb::key key) {
        fdb_transaction_clear (tx_, key, key.size ());
    }
}


#endif