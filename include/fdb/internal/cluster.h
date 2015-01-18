/**
 * @file fdb/internal/cluster.h
 * 
 * A scoped RAII pointer to manage memory of C-style FDBCluster pointers.
 */
#pragma once 
#ifndef INCLUDE_FDB_INTERNAL_CLUSTER_H
#define INCLUDE_FDB_INTERNAL_CLUSTER_H

#include "fdb.h"
#include "scoped_ptr.h"

/** @namespace fdb */
namespace fdb {

/** @namespace internal */
namespace internal {
	
    class cluster : public virtual scoped_ptr <FDBCluster> {
    public:
        virtual ~cluster ();
        using scoped_ptr<FDBCluster>::operator=;
    };
}}
#endif