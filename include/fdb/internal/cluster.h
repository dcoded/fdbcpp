#ifndef INCLUDE_FDB_INTERNAL_CLUSTER_H
#define INCLUDE_FDB_INTERNAL_CLUSTER_H

#include "scoped_ptr.h"
#include "../exception.h"

namespace fdb {
namespace internal {
    class cluster : public virtual scoped_ptr <FDBCluster> {
    public:
        virtual ~cluster ();
        using scoped_ptr<FDBCluster>::operator=;
    };

    cluster::~cluster () {
        if (ptr_ != nullptr)
            fdb_cluster_destroy (ptr_);
    }
}}
#endif