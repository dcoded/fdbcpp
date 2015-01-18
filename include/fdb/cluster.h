/**
 * @file fdb/cluster.h
 */
#pragma once
#ifndef INCLUDE_FDB_CLUSTER_H
#define INCLUDE_FDB_CLUSTER_H

#include "internal/future.h"
#include "internal/cluster.h"
#include "exception.h"

/** @namespace fdb */
namespace fdb {
    
    /** FoundationDB Cluster */
    class cluster {
    friend class database;

    private:
        fdb::internal::cluster instance;
        operator fdb::internal::cluster () const;
    public:
       /**
        * Create a new FoundationDB cluster.
        * 
        * Configures access to a FDB cluster with the provided configuration file.
        * If the filepath is null then a default cluster is created.
        * 
        * @param filepath configuration file location
        */
        explicit cluster (const char* filepath = nullptr);
    };
}
#endif