#include <iostream>
#include <cstdio>
#include <thread>

void AddAndPrint(uint32_t *value) {
	if (value) {
		std::cout << "thread " << (*value)++ << std::endl;
	}
}

int main(void) {

	uint32_t number_ = 1u;

	std::thread tr1{ AddAndPrint ,&number_ };
	tr1.join();

	std::thread tr2{ AddAndPrint ,&number_ };
	tr2.join();

	std::thread tr3{ AddAndPrint ,&number_ };
	tr3.join();

	return 0;
}