#include <iostream>   // For standard I/O (cout, etc.)
#include <thread>     // For std::thread (to create threads in C++)
#include <unistd.h>   // For sleep() function (in seconds)
using namespace std;

// Task A function (runs in thread t1)
void taskA() {
    for (int i = 0; i < 10; ++i) {
        sleep(1); // Makes the thread sleep for 1 second
        // printf is used instead of cout because cout is buffered.
        // printf + fflush ensures immediate output from multiple threads.
        printf("TaskA: %d\n", i);
        fflush(stdout); // Forces the output to be printed immediately
    }
}

// Task B function (runs in thread t2)
void taskB() {
    for (int i = 0; i < 10; ++i) {
        sleep(1); 
        printf("TaskB: %d\n", i);
        fflush(stdout);
    }
}

int main() {
    // Creating two threads
    // Each thread runs independently and executes its respective function
    thread t1(taskA);  
    thread t2(taskB);

    // join() makes the main thread wait until both t1 and t2 finish
    t1.join(); 
    t2.join();

    return 0;
}
