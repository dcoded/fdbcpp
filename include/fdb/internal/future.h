/**
 * @file fdb/internal/future.h
 * 
 * A scoped RAII pointer to manage memory of C-style FDBFuture pointers.
 */
#pragma once
#ifndef INCLUDE_FDB_INTERNAL_FUTURE_H
#define INCLUDE_FDB_INTERNAL_FUTURE_H

#include "scoped_ptr.h"
#include "../exception.h"

/** @namespace fdb */
namespace fdb {

/** @namespace internal */
namespace internal {
    class future : public virtual scoped_ptr <FDBFuture> {
    public:
        virtual ~future ();
        virtual operator FDBFuture* () const;
        using scoped_ptr<FDBFuture>::operator=;
    };

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
#endif