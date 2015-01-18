#include <fdb/internal/cluster.h>
namespace fdb {
namespace internal {

    cluster::~cluster () {
        if (ptr_ != nullptr)
            fdb_cluster_destroy (ptr_);
    }

}}