#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;
int main() {
    // Print startup info with PIDs [cite: 70, 71]
    pid_t my_pid = getpid();
    cout << "shsh process " << my_pid << " has been created by process " << getppid() << endl;
    string input;
    while (true) {
        cout << "shsh> "; // [cite: 51]
        if (!getline(cin, input) || input == "exit") break; // [cite: 50, 68]
        // Print processing message for every command [cite: 72]
        cout << "shsh processing " << input << endl;
        if (input.substr(0, 3) == "cmd") {
            // Use system() for cmd - it forks internally [cite: 54, 57]
            string shcmd = input.substr(4);
            system(shcmd.c_str());
        } 
        else if (input.substr(0, 2) == "TH") {
            // Manually fork for TH command [cite: 65]
            string N_val = input.substr(3);
            pid_t child_pid = fork();
            if (child_pid == 0) {
                // Executing TH.exe in the subprocess [cite: 65]
                execl("./TH.exe", "TH.exe", N_val.c_str(), (char*)NULL);
                exit(0);
            } else if (child_pid > 0) {
                // Parent prints forked PID and waits [cite: 73]
                cout << "shsh forked process " << child_pid << " to execute TH.exe" << endl;
                wait(NULL);
            }
        }
    }
    // Termination printout [cite: 72]
    cout << "shsh process " << my_pid << " terminates" << endl;
    return 0;
}