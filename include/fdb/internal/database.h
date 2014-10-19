/**
 * @file fdb/internal/database.h
 * 
 * A scoped RAII pointer to manage memory of C-style FDBDatabase pointers.
 */
#pragma once
#ifndef INCLUDE_FDB_INTERNAL_DATABASE_H
#define INCLUDE_FDB_INTERNAL_DATABASE_H

#include "scoped_ptr.h"
#include "../exception.h"

/** @namespace fdb */
namespace fdb {

/** @namespace internal */
namespace internal {
	
    class database : public virtual scoped_ptr <FDBDatabase> {
    public:
        virtual ~database ();
        using scoped_ptr<FDBDatabase>::operator=;
    };

    database::~database () {
        if (ptr_ != nullptr)
            fdb_database_destroy (ptr_);
    }
}}
#endif