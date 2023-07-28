#include <string>
#include <thread>
#include <mutex>
#include <fstream>

// https://www.youtube.com/watch?v=3ZxZPeXPaM4

/* To fully protect the resource the Mutex has to be bundled with the Resource */
class LogFile {
	std::mutex mu;
	std::ofstream f;

public:
	LogFile() {
		f.open("log.txt");
	}

	~LogFile() {
		f.close();
	}

	void sharedPrint(std::string id, int value) {
		std::lock_guard<std::mutex> locker(mu);
		f << "From: " << id << " : " << value << std::endl;
	}

	/* Things to Never Do */
	// Never return f to the outside world
	// ofstream& getStream() { return f; }

	// Never pass f as an argument to a user provided function
	/*
		void processf(void fun(ofstream &)) {
			fun(f);
		}
	*/

	// Always Design interface appropriately
	/* If two threads call top() of a stack and both see the same value then they both pop()
	   expecting to pop the same value but now two values have been popped instead of one. 
	   So the stack interface is not thread safe. */
};


void function1(LogFile & log) {
	for (int i = 0; i > -100; i--) {
		log.sharedPrint("From t1: ", i);
	}
}

int main(void) {
	LogFile log;
	std::thread t1(function1, std::ref(log));

	for (int i = 0; i < 100; i++) {
		log.sharedPrint("From Main: ", i);
	}

	t1.join();

	return 0;
}
