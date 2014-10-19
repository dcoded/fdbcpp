#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_GETRANGE_H
#define INCLUDE_FDB_TRANSACTIONAL_GETRANGE_H

#include <map>

namespace fdb {
    class get_range : public transactional </* return */ std::map<fdb::key, fdb::data>,
    /* arg types */ fdb::key, fdb::key, size_t, bool> {
    private:
        const FDBKeyValue* results = nullptr;
    public: 
        using transactional::transactional;

        virtual std::map<fdb::key, fdb::data> execute (
            fdb::key begin, fdb::key end,
            size_t limit, bool reverse
        );
    };

    std::map<fdb::key, fdb::data> get_range::execute (fdb::key begin, fdb::key end, size_t limit, bool reverse) {

        FDBFuture* future = fdb_transaction_get_range (tx_,
            begin, begin.size (), begin.equal (), begin.offset (),
            end  , end.size ()  , end.equal ()  , end.offset (),

            limit, 0, FDB_STREAMING_MODE_WANT_ALL, 1, 0, reverse
        );

        fdb_error_t error;
        if ((error = fdb_future_block_until_ready(future)) != 0) {
            fdb_future_destroy (future);
            throw fdb::exception (error);
        }

        int length;
        fdb_bool_t more;
        if ((error = fdb_future_get_keyvalue_array (future, &results, &length, &more)) != 0) {
            fdb_future_destroy (future);
            throw fdb::exception (error);
        }

        fdb::key key;
        fdb::data value;
        std::map <fdb::key, fdb::data> kv_map;
        
        for (int i = 0; i < length; i++) {

            key   = {results[i].key, results[i].key_length};
            value = {results[i].value, results[i].value_length};

            kv_map[key] = value;
        }

        fdb_future_destroy (future);

        return kv_map;
    }
}


#endif