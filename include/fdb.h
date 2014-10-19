/**
 * @file fdb.h
 */

/** @mainpage My Personal Index Page
 *
 * @section intro_sec Introduction
 *
 * This is the introduction.
 *
 * @section install_sec Installation
 *
 * @subsection step1 Step 1: Opening the box
 *  
 * etc...
 */
#pragma once
#ifndef INCLUDE_FDB_H
#define INCLUDE_FDB_H

#include <fdb/fdb.h>

#include <fdb/internal/future.h>
#include <fdb/internal/cluster.h>
#include <fdb/internal/database.h>
#include <fdb/internal/transaction.h>

#include <fdb/network.h>
#include <fdb/cluster.h>
#include <fdb/database.h>

#include <fdb/transactional.h>
#include <fdb/transactional/get.h>
#include <fdb/transactional/get_range.h>
#include <fdb/transactional/set.h>
#include <fdb/transactional/del.h>

#include <fdb/data.h>
#include <fdb/key.h>

/** @namespace fdb
 *	FoundationDB C to C++11 interface library
 */

/** @namespace fdb::internal
 * RAII scoped pointers to manage dynamic memory.
 */

 /** @namespace fdb::op
 * Implemented database operations
 */

#endif