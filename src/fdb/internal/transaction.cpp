#include <fdb/internal/transaction.h>
namespace fdb {
namespace internal {
    
    transaction::~transaction () {
        if (ptr_ != nullptr)
            fdb_transaction_destroy (ptr_);
    }
}}