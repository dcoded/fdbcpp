#pragma once
#ifndef INCLUDE_FDB_CLUSTER_H
#define INCLUDE_FDB_CLUSTER_H


namespace fdb {

    class cluster {
    friend class database;

    private:
        FDBCluster* instance = nullptr;
        operator decltype(instance) () const;
    public:
        explicit cluster (const char* filepath = nullptr);
        ~cluster ();
    };


    cluster::cluster (const char* filepath)
    {
        FDBFuture* future;
        future = fdb_create_cluster (filepath);

        fdb_error_t error;
        error = fdb_future_block_until_ready (future);

        if (error != 0) {
            fdb_future_destroy (future);
            throw fdb::exception (error);
        }
            
        error = fdb_future_get_cluster (future, &instance);
                fdb_future_destroy (future);
        
        if (error != 0)
            throw fdb::exception (error);
    }

    cluster::~cluster () {
        if (instance != nullptr)
            fdb_cluster_destroy (instance);
    }

    cluster::operator decltype(instance) () const {
        return instance;
    }
}

#endif