#pragma once
#ifndef INCLUDE_FDB_DATABASE_H
#define INCLUDE_FDB_DATABASE_H

#include "transaction.h"

namespace fdb {

    class database {
    private:
        FDBDatabase* instance;
        operator decltype(instance) () const;
    public:
        explicit database (const cluster& cluster, std::string db_name = "DB");
        ~database ();

        transaction transaction () const;
    };

    database::database (const cluster& cluster, std::string db_name) {

        FDBFuture* future;
        future = fdb_cluster_create_database (cluster,
            reinterpret_cast<const uint8_t*>(db_name.c_str()),
            db_name.size ()
        );

        fdb_error_t error;
        error = fdb_future_block_until_ready (future);

        if (error != 0) {
            fdb_future_destroy (future);
            throw fdb::exception (error);
        }

        error = fdb_future_get_database (future, &instance);
                fdb_future_destroy (future);

        if (error != 0)
            throw fdb::exception (error);
    }

    database::~database () {
        if (instance != nullptr)
            fdb_database_destroy (instance);
    }

    transaction database::transaction () const {
        return fdb::transaction (instance);
    }

    database::operator decltype(instance) () const {
        return instance;
    }
}

#endif