#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

mutex mtx;                    // Mutex for synchronization
condition_variable cv;        // Condition variable
bool ready = false;           // Shared condition flag

// Task A: waits until "ready" becomes true
void taskA() {
    unique_lock<mutex> lock(mtx);  // Acquire lock
    
    cout << "TaskA is waiting...\n";
    
    // Wait until "ready" becomes true
    cv.wait(lock, [] { return ready; });
    
    // Once signaled and condition met
    cout << "TaskA is running after signal!\n";
}

// Task B: signals TaskA to proceed
void taskB() {
    this_thread::sleep_for(chrono::seconds(2)); // Simulate some work
    
    {
        lock_guard<mutex> lock(mtx);  // Lock before modifying "ready"
        ready = true;                 // Update condition
        cout << "TaskB signals TaskA!\n";
    }
    
    cv.notify_one();  // Signal (wake up one waiting thread)
}

int main() {
    thread t1(taskA);  // Thread that waits
    thread t2(taskB);  // Thread that signals

    t1.join();
    t2.join();

    return 0;
}
