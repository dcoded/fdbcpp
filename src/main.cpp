#include <iostream>
#include <fdb.h>

int main(int argc, char** argv)
{
    try {
        fdb::network network;
        fdb::cluster cluster;
        fdb::database database (cluster);

        fdb::transaction tx = database.transaction ();

        auto x = fdb::get (tx) ("x");
        auto y = fdb::set (tx) ("x", "helloxvsdvsj foobar");
        auto z = fdb::get (tx) ("x");
        auto f = fdb::get_range (tx) ("\x00", "\xFF", 0, false);
        auto d = fdb::del (tx) ("a2a");

        auto ver = tx ();
        
        auto kv_map = f.get ();



        for (auto i : kv_map)
            std::cout << i.first << " -> " << i.second << "\n";
    }
    catch (const fdb::exception& ex) {
        std::cerr << ex.what () << std::endl;
    }
}

