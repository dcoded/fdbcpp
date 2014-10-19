#pragma once
#ifndef INCLUDE_FDB_ASYNCWAITENABLED_H
#define INCLUDE_FDB_ASYNCWAITENABLED_H

namespace fdb {

class async_wait_enabled {
public:
    virtual void wait () = 0;
};

}
#endif