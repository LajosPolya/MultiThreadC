#include <iostream>
#include <string>
#include <thread>
#include <mutex>

// https://www.youtube.com/watch?v=3ZxZPeXPaM4

std::mutex mu;

/* To avoid Data Races use a mutex */
void sharedPrint(std::string message, int id) {
	/* We shouldn't just use mu alone because if an exception is thrown 
	   between the lock and unlock then the resource will be locked forever.
	   So instead use a lock_guard and when the guard goes out of scope it'll
	   release the lock
	*/ 
	std::lock_guard<std::mutex> gaurd(mu); // RAII
	std::cout << message << id << std::endl;
}

void function1() {
	for (int i = 0; i > -100; i--) {
		sharedPrint("From t1: ", i);
	}
}

int main(void) {
	std::thread t1(function1);

	for (int i = 0; i < 100; i++) {
		sharedPrint("From Main: ", i);
	}

	t1.join();


	while (1) {}

	return 0;
}
