#pragma once
#ifndef INCLUDE_FDB_NETWORK_H
#define INCLUDE_FDB_NETWORK_H

#include "exception.h"

#include <system_error>
#include <string>
#include <future>
#include <cassert>

namespace fdb {

	class network {
	private:
		int api_version = -1;
		std::future <fdb_error_t> f_network_;
	public:
		
		explicit network (int api_version = FDB_API_VERSION);
		
		~network ();

		fdb_error_t join ();
		std::future <fdb_error_t> stop () const;

		bool ok () const;
		bool err () const;
	};



	network::network (int api_version) {
		fdb_error_t error;

		if ((error = fdb_select_api_version (api_version)) != 0)
			throw fdb::exception (error);

		if ((error = fdb_setup_network ()) != 0)
			throw fdb::exception (error);

		f_network_ = std::async (std::launch::async, fdb_run_network);
	}

	network::~network () {
		stop ();
	}


	std::future<fdb_error_t> network::stop () const {
		// future : std::future<fdb_error_t>
		return std::async (std::launch::async, fdb_stop_network);
	}

	fdb_error_t network::join () {
		 return f_network_.get ();
	}
}
#endif