#pragma once
#ifndef INCLUDE_FDB_TRANSACTION_H
#define INCLUDE_FDB_TRANSACTION_H

#include "async_wait_enabled.h"

#include <iterator>
#include <vector>

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

    transaction::transaction (FDBDatabase* db) {
        fdb_error_t error;
        if ((error = fdb_database_create_transaction (db, instance)) != 0)
            throw new fdb::exception (error);
    }

    transaction::operator fdb::internal::transaction& () {
        return instance;
    }

    int64_t transaction::commit () {

        for (auto task : tasks)
            task->wait ();

        fdb::internal::future future;
        future = fdb_transaction_commit (instance);

        fdb_error_t error;
        int64_t version;
        if ((error = fdb_transaction_get_committed_version(instance, &version)) != 0)
            throw fdb::exception (error);

        return version;
    }

    void transaction::await (async_wait_enabled* t) {
        tasks.push_back (t);
    }

    int64_t transaction::operator() () {
        return commit ();
    }
}

#endif