#pragma once
#ifndef INCLUDE_FDB_NETWORK_H
#define INCLUDE_FDB_NETWORK_H

#include "exception.h"
#include "async_wait_enabled.h"

#include <system_error>
#include <string>
#include <future>
#include <cassert>

/** @namespace fdb */
namespace fdb {
    /**
     * FoundationDB network event loop manager
     */
    class network : async_wait_enabled {
    private:
        /** Event loop thread future */
        std::future <fdb_error_t> future;
    public:
        /**
         * Starts FDB network thread
         * 
         * @param api_version API version
         */
        explicit network (int api_version = FDB_API_VERSION);
        
        /** Stops network thread in case of scope loss due to exception */
        ~network ();

        /** Destroys the network thread, can only be called once per process */
        std::future <fdb_error_t> stop () const;

        /**
         * Implementation of polymorphic asyncronous block/wait.
         * 
         * @see fdb::async_wait_enabled::wait
         */
        virtual void wait ();
    };

    network::network (int api_version) {

        fdb_error_t error;
        if ((error = fdb_select_api_version (api_version)) != 0)
            throw fdb::exception (error);

        if ((error = fdb_setup_network ()) != 0)
            throw fdb::exception (error);

        future = std::async (std::launch::async, fdb_run_network);
    }

    network::~network () {
        stop ();
    }

    std::future<fdb_error_t> network::stop () const {
        return std::async (std::launch::async, fdb_stop_network);
    }

    void network::wait () {
        fdb_error_t error;

        if ((error = future.get ()) != 0)
            throw fdb::exception (error);

        future.wait ();
    }
}
#endif