#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
#include <sstream> // For atomic printing
#include <cstdlib> // For atoi
using namespace std;
// Global variable as required [cite: 13]
int counter = 0;
struct ThreadData {
    int mytid;
    int R;
};
// Thread function: loops R times to increment the global counter [cite: 30]
void* threadFunction(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    pthread_t systid = pthread_self(); // [cite: 36]
    // Solution for garbled output: Print to string first then to cout
    ostringstream start_msg;
    start_msg << "Start of thread (" << data->mytid << ", " << (unsigned long)systid << ")\n";
    cout << start_msg.str(); // [cite: 31]
    for (int i = 0; i < data->R; ++i) {
        counter++;
    }
    ostringstream end_msg;
    end_msg << "End of thread (" << data->mytid << ", " << (unsigned long)systid << ")\n";
    cout << end_msg.str(); // [cite: 32]
    return NULL;
}
// Thread Manager: creates N threads and waits for them [cite: 16, 24]
void threadManager(int R, int N) {
    counter = 0; // Initialize to 0 before thread creation [cite: 13]
    vector<pthread_t> threads(N);
    vector<ThreadData> tData(N);
    for (int i = 0; i < N; ++i) {
        tData[i].mytid = i + 1; // Assign ID 1 to N [cite: 22]
        tData[i].R = R;
        pthread_create(&threads[i], NULL, threadFunction, &tData[i]); // [cite: 19]
    }
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL); // Wait for threads [cite: 24]
    }
    long theoretical = (long)N * R; // [cite: 26]
    cout << "Actual counter value by " << N << " threads = " << counter 
         << "; Theoretical counter value = " << theoretical << endl; // [cite: 27]
}
int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    int N = atoi(argv[1]); // [cite: 15]
    // Observe behavior under different R values [cite: 38, 39]
    threadManager(1000, N);
    threadManager(1000000, N);
    // Binary search for mismatch R value [cite: 40]
    int low = 1, high = 1000000;
    int first_mismatch = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        threadManager(mid, N); 
        if (counter != (long)N * mid) {
            first_mismatch = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return 0;
}