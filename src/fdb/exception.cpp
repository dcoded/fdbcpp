#include <fdb/exception.h>

namespace fdb {
    exception::exception (fdb_error_t code)
    : std::runtime_error (fdb_get_error (code)) {}

    exception::exception (const std::string what)
    : std::runtime_error (what) {}
}