#include <fdb/transaction.h>
namespace fdb {

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
        fdb_error_t error;
        int64_t version;

        future = fdb_transaction_commit (instance);
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