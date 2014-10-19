#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_GET_H
#define INCLUDE_FDB_TRANSACTIONAL_GET_H

#include "../key.h"

namespace fdb {
    class get : public transactional </* return */ fdb::data, /* arg types */ fdb::key> {
    public: 
        using transactional::transactional;
        virtual fdb::data execute (fdb::key key);
    };

    fdb::data get::execute (fdb::key key) {
        fdb_error_t error;
        fdb_bool_t  exists;

        int length;

        const uint8_t* value;
        FDBFuture*     future = fdb_transaction_get (tx_, key, key.size (), false);

        if ((error = fdb_future_block_until_ready(future)) != 0) {
            fdb_future_destroy (future);
            throw fdb::exception (error);
        }

        if ((error = fdb_future_get_value (future, &exists, &value, &length)) != 0) {
            fdb_future_destroy (future);
            throw fdb::exception (error);
        }

        fdb_future_destroy (future);

        return fdb::data (value, length);
    }
}


#endif