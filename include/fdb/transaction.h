#pragma once
#ifndef INCLUDE_FDB_TRANSACTION_H
#define INCLUDE_FDB_TRANSACTION_H

#include <iterator>
#include <vector>

#include "async_wait_enabled.h"
#include "internal/transaction.h"
#include "internal/future.h"
#include "exception.h"

/** @namespace fdb */
namespace fdb {

    /** FoundationDB Transaction */
    class transaction {
    friend class database;
    private:
        std::vector <fdb::async_wait_enabled*> tasks;
        fdb::internal::transaction instance;
    protected:
        explicit transaction (FDBDatabase* db);
    public:
        void await (async_wait_enabled* t);

        /** @name Commit Operations */ 
        //@{
        /**
         * Commits all transactional operations.
         * 
         * FoundationDB will perform an all-or-nothing commit of operations as
         * per ACID requirements.  If a commit is successful then the operation
         * was commited to disk.
         * 
         * If only read operations are performed or can be simplifed to only
         * read operations then the version ID returned is -1
         * 
         * @return commit version ID
         */
        int64_t operator() ();
        int64_t commit ();
        //@}

        operator fdb::internal::transaction& ();
    };
}

#endif