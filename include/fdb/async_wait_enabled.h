/**
 * @file fdb/async_wait_enabled.h
 * 
 * Allows different std::async'd tasks to block simultaneously.
 */
#pragma once
#ifndef INCLUDE_FDB_ASYNCWAITENABLED_H
#define INCLUDE_FDB_ASYNCWAITENABLED_H

/** @namespace fdb */
namespace fdb {

/** Polymorphic mixin to allow queuing of different signature std::future */
class async_wait_enabled {
public:
	/**
	 * Blocks until asynchronous future is ready.
	 */
    virtual void wait () = 0;
};

}
#endif