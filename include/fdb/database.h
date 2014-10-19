#pragma once
#ifndef INCLUDE_FDB_DATABASE_H
#define INCLUDE_FDB_DATABASE_H

#include "data.h"
#include "transaction.h"

/** @namespace fdb */
namespace fdb {

    /** FoundationDB Database */
    class database {
    private:
        fdb::internal::database instance;
        operator fdb::internal::database () const;
    public:
        /**
         * Instantiate a database instance in a given cluster.
         * 
         * @param cluster fdb::cluster instance
         * @param db_name name of the database (FoundationDB currently only allows "DB" as a valid name)
         */
        explicit database (const cluster& cluster, fdb::data db_name = "DB");

        /**
         * Create a new transaction on this database
         * 
         * @return a new transaction object
         */
        transaction transaction () const;
    };

    database::database (const cluster& cluster, fdb::data db_name) {

        fdb::internal::future future;
        future = fdb_cluster_create_database (
            static_cast<fdb::internal::cluster> (cluster),
            db_name, db_name.size ()
        );

        fdb_error_t error;
        error = fdb_future_get_database (future, instance);

        if (error != 0)
            throw fdb::exception (error);
    }

    transaction database::transaction () const {
        return fdb::transaction (instance);
    }

    database::operator fdb::internal::database () const {
        return instance;
    }
}

#endif