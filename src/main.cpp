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

	auto future6 = set (tx) ("buy:x.xx:987979:33921", "order-554541");
	
	auto x = set (tx) ("x", "hello test");
	auto z = get (tx) ("x");
	auto f = get_range (tx) ( "buy:\x00", "buy:\xFF", 0, true);
	//auto d = del (tx) ("x");


	auto ver = tx ();
	auto kv_map = f.get ();

	std::cout << "Transaction Version: " << ver << "\n";
	std::cout << "'" << static_cast<std::string>(z.get ()) << "'\n";
	for (auto i : kv_map)
		std::cout << '[' << i.first << "] " << i.second << "\n";
}
catch (const fdb::exception& ex) {
	std::cerr << "[fdb]" << ex.what () << std::endl;
}