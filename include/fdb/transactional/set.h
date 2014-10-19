#pragma once
#ifndef INCLUDE_FDB_TRANSACTIONAL_SET_H
#define INCLUDE_FDB_TRANSACTIONAL_SET_H

namespace fdb {
    class set : public transactional </* return */ void, /* arg types */ fdb::key, fdb::data> {
    public: 
        using transactional::transactional;

        virtual void execute (fdb::key key, fdb::data val) {
            fdb_transaction_set (tx_, key, key.size (), val, val.size ());
        }
    };
}


#endif