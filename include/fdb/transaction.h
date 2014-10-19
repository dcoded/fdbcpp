#pragma once
#ifndef INCLUDE_FDB_TRANSACTION_H
#define INCLUDE_FDB_TRANSACTION_H

#include "async_wait_enabled.h"

#include <iterator>
#include <vector>

namespace fdb {
    class transaction {
    friend class database;
    private:
        std::vector <fdb::async_wait_enabled*> tasks;
        fdb::internal::transaction instance;
    protected:
        explicit transaction (FDBDatabase* db);
    public:
        int64_t commit ();
        void    await (async_wait_enabled* t);

        int64_t operator() ();
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