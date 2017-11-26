#include <iostream>
#include <thread>

// https://www.youtube.com/watch?v=LL8wkskDlbs

void function1() {
	std::cout << "Print from Thread" << std::endl;
}


int main(void) {
	std::thread t1(function1);

	if (t1.joinable()) {
		// main thread waits here for thread to complete
		t1.join();
	}

	// So CLI doesn't quit;
	while (1);

	return 0;
}