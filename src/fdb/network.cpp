#include <fdb/network.h>

namespace fdb {

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