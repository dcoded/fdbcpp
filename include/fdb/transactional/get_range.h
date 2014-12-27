/**
 * @file fdb/transactional/get_range.h
 * 
 * Bulk get operation on a FoundationDB database.
 */
#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_GETRANGE_H
#define INCLUDE_FDB_TRANSACTIONAL_GETRANGE_H

#include <vector>

/** @namespace fdb */
namespace fdb {

/** @namespace op */
namespace op  {

    /** Get Range operation returns a map of (key,value) from key range */
    class get_range : public transactional <
    /* return */ std::vector<std::pair<fdb::key, fdb::data>>,
    /* arg types */ fdb::key, fdb::key, size_t, bool> {
    private:
        const FDBKeyValue* results = nullptr;
    public: 
        using transactional::transactional;

        virtual std::vector<std::pair<fdb::key, fdb::data>> execute (
            const fdb::key& begin, const fdb::key& end,
            const size_t& limit, const bool& reverse
        );
    };

    std::vector<std::pair<fdb::key, fdb::data>> get_range::execute (const fdb::key& begin, const fdb::key& end, const size_t& limit, const bool& reverse) {

        fdb::internal::future future;
        future = fdb_transaction_get_range (tx_,
            begin, begin.size (), begin.equal (), begin.offset (),
            end  ,   end.size (),   end.equal (),   end.offset (),

            limit, 0, FDB_STREAMING_MODE_WANT_ALL, 1, 0, reverse
        );

        int length;
        fdb_error_t error;
        fdb_bool_t more;
        if ((error = fdb_future_get_keyvalue_array (future, &results, &length, &more)) != 0)
            throw fdb::exception (error);

        fdb::key key;
        fdb::data value;
        std::vector<std::pair<fdb::key, fdb::data>> kv_map;

        for (int i = 0; i < length; i++) {
            key   = {results[i].key  , results[i].key_length  };
            value = {results[i].value, results[i].value_length};

            kv_map.push_back(std::make_pair (key, value));
        }

        return kv_map;
    }
}}


#endif