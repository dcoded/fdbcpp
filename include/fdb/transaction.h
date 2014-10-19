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
        FDBTransaction* instance = nullptr;
    protected:
        explicit transaction (FDBDatabase* db);
    public:
        ~transaction ();
        int64_t commit ();
        void    await (async_wait_enabled* t);

        int64_t operator() ();
        FDBTransaction* get ();
    };

    transaction::transaction (FDBDatabase* db) {
        fdb_error_t error;
        if ((error = fdb_database_create_transaction (db, &instance)) != 0)
            throw new fdb::exception (error);
    }

    transaction::~transaction () {
        if (instance != nullptr)
            fdb_transaction_destroy (instance);
    }

    FDBTransaction* transaction::get () {
        return instance;
    }

    int64_t transaction::commit () {

        for (auto task : tasks)
            task->wait ();

        FDBFuture* future;
        future = fdb_transaction_commit (instance);

        fdb_error_t error;
        if ((error = fdb_future_block_until_ready(future)) != 0) {
            fdb_future_destroy (future);
            throw fdb::exception (error);
        }

        fdb_future_destroy (future);

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