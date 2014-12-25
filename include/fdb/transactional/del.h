/**
 * @file fdb/transactional/del.h
 * 
 * Delete operation on a FoundationDB database.
 */
#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_DEL_H
#define INCLUDE_FDB_TRANSACTIONAL_DEL_H

#include "../key.h"

/** @namespace fdb */
namespace fdb {

/** @namespace op */
namespace op  {

	/** Delete operation removes a key and value (if exists) */
    class del : public transactional </* return */ void, /* arg types */ fdb::key> {
    public: 
        using transactional::transactional;

        /**
         * Execute deletion of key in transaction.
         */
        virtual void execute (const fdb::key& key);
    };

    void del::execute (const fdb::key& key) {
        fdb_transaction_clear (tx_, key, key.size ());
    }
}}


#endif