#pragma once
#ifndef INCLUDE_FDB_EXCEPTION_H
#define INCLUDE_FDB_EXCEPTION_H

#include <stdexcept>
#include <future>
#include <cassert>

namespace fdb {

    class exception : public std::runtime_error {
    public:
        explicit exception (fdb_error_t code)
        : std::runtime_error (fdb_get_error (code)) {}

        explicit exception (const std::string what)
        : std::runtime_error (what) {}
    };
}

#endif