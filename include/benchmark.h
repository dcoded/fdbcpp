#pragma once
#include <chrono>
#include <vector>
#include <numeric>
#include <fstream>
#include <iomanip>

class benchmark {
private:
	std::ostream& ostream;
public:

	benchmark (std::ostream& ostream)
	: ostream (ostream) {
		ostream
			<< std::left
			<< std::setw (16) << "testname"
			<< std::setw (16) << "varient"
			<< std::setw (8)  << "time (us)"
			<< std::endl
			<< std::setw (16) << "--------"
			<< std::setw (16) << "-------"
			<< std::setw (8)  << "---------"
			<< std::endl;
	}

	void default_round_initialization () {

	}

	template <typename Fn, typename... Args>
	benchmark& run (std::string test, std::string varient, int rounds, std::function<void()>* init, Fn fn, Args&... args) {

		std::vector< std::chrono::duration<double, std::micro> >times;

		for (int i = 0; i < rounds; i++) {

			if (init != nullptr)
				(*init) ();

			auto start = std::chrono::steady_clock::now ();
			fn (args...);
			auto stop = std::chrono::steady_clock::now ();
			times.push_back(
				std::chrono::duration <double, std::micro> (stop-start));
		}

		auto average = (1.0/rounds) * std::accumulate (times.begin (), times.end (),
						 	std::chrono::duration <double, std::micro>(0));
		ostream
			<< std::left
			<< std::setw (16) << test
			<< std::setw (16) << varient
			<< std::setw (8)  << average.count ()
			<< std::endl;

		return *this;
	}


};