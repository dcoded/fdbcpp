/**
 * @file fdb/transactional/get.h
 * 
 * Get operation on a FoundationDB database.
 */
#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_GET_H
#define INCLUDE_FDB_TRANSACTIONAL_GET_H

#include "../key.h"

/** @namespace fdb */
namespace fdb {

/** @namespace op */
namespace op  {

    /** Get operation returns a value from key (if exists) */
    class get : public transactional </* return */ fdb::data, /* arg types */ fdb::key> {
    public: 
        using transactional::transactional;
        virtual fdb::data execute (const fdb::key& key);
    };

    fdb::data get::execute (const fdb::key& key) {
        
        fdb::internal::future future;
        future = fdb_transaction_get (tx_, key, key.size (), false);

        fdb_error_t error;

        int length;
        fdb_bool_t exists;
        const uint8_t* value;
        
        if ((error = fdb_future_get_value (future, &exists, &value, &length)) != 0)
            throw fdb::exception (error);

        return fdb::data (value, length);
    }
}}


#endif