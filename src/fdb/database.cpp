#include <fdb/database.h>

namespace fdb {

    database::database (const fdb::cluster& cluster, fdb::data db_name) {

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