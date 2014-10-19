#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_H
#define INCLUDE_FDB_TRANSACTIONAL_H

#include <fdb.h>
#include "async_wait_enabled.h"

namespace fdb {

    template <typename ReturnType, typename... Arguments>
    class transactional : public async_wait_enabled {
    protected:
        std::future<ReturnType>* future_;
        transaction&    tr_;
        FDBTransaction* tx_;
    public:
        transactional (transaction& tx)
        : tr_ (tx)
        , tx_ (tx.get ()) {}

        std::future<ReturnType> operator() (Arguments...args) {
            tr_.await (this);
            
            std::future<ReturnType> f = std::async (
                std::launch::deferred,
                &transactional::execute,
                this, args...
            );

            future_ = &f;
            return f;
        }

        void wait () {
            future_->wait ();
        }

    protected:
        virtual ReturnType execute (Arguments...args) = 0;
    };
}
#endif