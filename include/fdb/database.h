#pragma once
#ifndef INCLUDE_FDB_DATABASE_H
#define INCLUDE_FDB_DATABASE_H

#include <string>

#include "internal/future.h"
#include "internal/database.h"
#include "cluster.h"

#include "transaction.h"
#include "data.h"

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
        explicit database (const fdb::cluster& cluster, fdb::data db_name = "DB");

        /**
         * Create a new transaction on this database
         * 
         * @return a new transaction object
         */
        transaction transaction () const;
    };
}

#endif