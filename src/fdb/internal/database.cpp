#include <fdb/internal/database.h>
namespace fdb {
namespace internal {

    database::~database () {
        if (ptr_ != nullptr)
            fdb_database_destroy (ptr_);
    }

}}