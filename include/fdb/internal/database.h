#ifndef INCLUDE_FDB_INTERNAL_DATABASE_H
#define INCLUDE_FDB_INTERNAL_DATABASE_H

#include "scoped_ptr.h"
#include "../exception.h"

namespace fdb {
namespace internal {
    class database : public virtual scoped_ptr <FDBDatabase> {
    public:
        virtual ~database ();
        using scoped_ptr<FDBDatabase>::operator=;
    };

    database::~database () {
        if (ptr_ != nullptr)
            fdb_database_destroy (ptr_);
    }
}}
#endif