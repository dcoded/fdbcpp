/**
 * @file fdb/transactional.h
 * 
 * Interface for database operations.
 */
#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_H
#define INCLUDE_FDB_TRANSACTIONAL_H

#include "async_wait_enabled.h"
#include "exception.h"

/** @namespace fdb */
namespace fdb {

    /**
     * Base class for all operations during a transaction.
     * 
     * Also provides a standardized asyncronous wrapper for all operations.
     */
    template <typename ReturnType, typename... Arguments>
    class transactional : public async_wait_enabled {
    protected:
        std::future<ReturnType>* future_;
        transaction& tr_;
        fdb::internal::transaction& tx_;
    public:

        /**
         * @param tx is a database transaction instance @see fdb::database::transaction
         */
        transactional (transaction& tx)
        : tr_ (tx)
        , tx_ (tx) {}

        /**
         * C++11 std::async/std::future asynchronous wrapper for all operations.
         * 
         * All operations called via this method are automatically tracked by
         * the transaction.  The transaction will not commit until this and
         * all other futures are ready and without error.
         * 
         * @param args are template arguments defined by implemented operations
         * @return std::future<T> with T being the return type of operation
         */
        std::future<ReturnType> operator() (Arguments...args) {
            tr_.await (this);
            
            std::future<ReturnType> future = std::async (
                std::launch::deferred,
                &transactional::execute,
                this, args...
            );

            future_ = &future;
            return future;
        }

        /**
         * Implementation of polymorphic asyncronous block/wait.
         * 
         * @see fdb::async_wait_enabled::wait
         */
        virtual void wait () {
            future_->wait ();
        }

    protected:
        virtual ReturnType execute (const Arguments&...args) = 0;
    };
}
#endif