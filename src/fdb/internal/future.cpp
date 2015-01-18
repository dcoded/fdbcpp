#include <fdb/internal/future.h>

namespace fdb {
namespace internal {

    future::~future () {
        if (ptr_ != nullptr)
            fdb_future_destroy (ptr_);
    }

    future::operator FDBFuture* () const {
        fdb_error_t error;
        if ((error = fdb_future_block_until_ready(ptr_)) != 0)
            throw fdb::exception (error);

        return ptr_;
    }
}}