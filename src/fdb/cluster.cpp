#include <fdb/cluster.h>
namespace fdb {

    cluster::cluster (const char* filepath) {
        
        fdb::internal::future future;
        fdb_error_t error;   

        future = fdb_create_cluster (filepath);   
        error  = fdb_future_get_cluster (future, instance);
        
        if (error != 0)
            throw fdb::exception (error);
    }

    cluster::operator fdb::internal::cluster () const {
        return instance;
    }
}