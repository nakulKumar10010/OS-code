#include <iostream>
#include <thread>
#include <mutex>       // For std::mutex
#include <chrono>      // For std::this_thread::sleep_for
using namespace std;

mutex mtx; // global mutex for synchronizing output

// Task A function
void taskA() {
    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::seconds(1)); // sleep for 1 second
        
        // Lock before printing
        mtx.lock();
        cout << "TaskA: " << i << endl;
        mtx.unlock(); // Unlock so other thread can use
    }
}

// Task B function
void taskB() {
    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::seconds(1));
        
        // Lock before printing
        mtx.lock();
        cout << "TaskB: " << i << endl;
        mtx.unlock();
    }
}

int main() {
    // Create two threads
    thread t1(taskA);
    thread t2(taskB);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    return 0;
}
