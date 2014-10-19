/**
 * @file fdb/cluster.h
 */
#pragma once
#ifndef INCLUDE_FDB_CLUSTER_H
#define INCLUDE_FDB_CLUSTER_H

/** @namespace fdb */
namespace fdb {

    /** FoundationDB Cluster */
    class cluster {
    friend class database;

    private:
        fdb::internal::cluster instance;
        operator fdb::internal::cluster () const;
    public:
        explicit cluster (const char* filepath = nullptr);
    };

    /**
     * Create a new FoundationDB cluster.
     * 
     * Configures access to a FDB cluster with the provided configuration file.
     * If the filepath is null then a default cluster is created.
     * 
     * @param filepath configuration file location
     */
    cluster::cluster (const char* filepath)
    {
        fdb::internal::future future;
        future = fdb_create_cluster (filepath);

        fdb_error_t error;       
        error = fdb_future_get_cluster (future, instance);
        
        if (error != 0)
            throw fdb::exception (error);
    }

    cluster::operator fdb::internal::cluster () const {
        return instance;
    }
}

#endif