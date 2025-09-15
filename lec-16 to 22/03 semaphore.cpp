#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

class Semaphore {
private:
    int value;                       // counter
    mutex mtx;                       // protects value
    condition_variable cv;           // for blocking/wakeup

public:
    Semaphore(int init = 1) : value(init) {}

    // P operation = wait()
    void wait() {
        unique_lock<mutex> lock(mtx);
        value--;                     // decrement counter
        if (value < 0) {
            // if not available, wait
            cv.wait(lock, [&] { return value >= 0; });
        }
    }

    // V operation = signal()
    void signal() {
        unique_lock<mutex> lock(mtx);
        value++;                     // increment counter
        if (value <= 0) {
            // wake up one waiting thread
            cv.notify_one();
        }
    }
};

// Shared semaphore (binary = 1)
Semaphore sem(1);

void taskA() {
    for (int i = 0; i < 5; i++) {
        sem.wait(); // P()
        cout << "TaskA running " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        sem.signal(); // V()
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void taskB() {
    for (int i = 0; i < 5; i++) {
        sem.wait(); // P()
        cout << "TaskB running " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
        sem.signal(); // V()
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

int main() {
    thread t1(taskA);
    thread t2(taskB);

    t1.join();
    t2.join();

    return 0;
}
