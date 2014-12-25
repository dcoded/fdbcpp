#include <iostream>
#include <fdb.h>

int main(int argc, char** argv)
try
{
	using namespace fdb::op;

	fdb::network network;
	fdb::cluster cluster;
	fdb::database database (cluster);
	fdb::transaction tx = database.transaction ();
	
	auto y = set (tx) ("x", "0123");

	auto z = get (tx) ("x");
	auto f = get_range (tx) ("\x00", "\xFF", 0, false);
	auto d = del (tx) ("a2a");
	
	auto ver = tx ();
	auto kv_map = f.get ();

	std::cout << static_cast<std::string>(z.get ()) << "\n";
	// for (auto i : kv_map)
	// 	std::cout << i.first << " -> " << i.second << "\n";
}
catch (const fdb::exception& ex) {
	std::cerr << ex.what () << std::endl;
}