/**
 * @file fdb/internal/future.h
 * 
 * A scoped RAII pointer to manage memory of C-style FDBFuture pointers.
 */
#pragma once
#ifndef INCLUDE_FDB_INTERNAL_FUTURE_H
#define INCLUDE_FDB_INTERNAL_FUTURE_H

#include "fdb.h"
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
}}
#endif