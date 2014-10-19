// $Id$
/**
 * @file fdb.h
 * Main header file used and included by client applications.
 */
// $Log$
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

#include <fdb/key.h>

#endif