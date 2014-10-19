/**
 * @file fdb/internal/transaction.h
 * 
 * A scoped RAII pointer to manage memory of C-style FDBTransaction pointers.
 */
#pragma once
#ifndef INCLUDE_FDB_INTERNAL_TRANSACTION_H
#define INCLUDE_FDB_INTERNAL_TRANSACTION_H

#include "scoped_ptr.h"
#include "../exception.h"

/** @namespace fdb */
namespace fdb {

/** @namespace internal */
namespace internal {
	
    class transaction : public virtual scoped_ptr <FDBTransaction> {
    public:
        virtual ~transaction ();
        using scoped_ptr<FDBTransaction>::operator=;
    };

    transaction::~transaction () {
        if (ptr_ != nullptr)
            fdb_transaction_destroy (ptr_);
    }
}}
#endif