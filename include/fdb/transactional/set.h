/**
 * @file fdb/transactional/set.h
 * 
 * Set operation on a FoundationDB database.
 */
#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_SET_H
#define INCLUDE_FDB_TRANSACTIONAL_SET_H

/** @namespace fdb */
namespace fdb {

/** @namespace op */
namespace op  {

	/**
	 * Set operation creates or updates a value for a given key
	 * 
	 * @tparam ReturnType
	 * @tparam Arguments... parameter type list of execute() method
	 */
    class set : public transactional <void/**< return type */, /** argument types */ fdb::key, fdb::data> {
    public: 
        using transactional::transactional;

        virtual void execute (const fdb::key& key, const fdb::data& val) {
            fdb_transaction_set (tx_, key, key.size (), val, val.size ());
        }
    };
}}


#endif