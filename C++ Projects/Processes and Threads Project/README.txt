README: Processes and Threads

Course: CS4348 Operating Systems
Project #1
Tested on cslinux1 using PuTTY

1. Comp. and Execution
Project uses a Makefile to power the process
In order to generate two executables shsh.exe and TH.exe, command the Bash:
make 

In order to run the Shell-Shell, command the Bash:
./shsh.exe

In order to clean the build files, command the Bash:
make clean

2. Details of Implementation
Atomicity: Due to Q&A, there was extra implementation regarding the std::ostringstream in TH.cpp, making sure that the thread start and end messages are printed in one operation and not in a garbled output when multiple threads write to stdout at the same time.
TH.exe uses a binary search algorithm in it's main() to figure out the iteration count R where the counter mismatch happens.
The cmd uses the system() call, handling the creation of a subprocess.
TH command creates a process using bot execl() and fork() (I relearned so much of C++ over the course of this week).
Finally, the exit command perfectly terminates the shell.

3. N Counter Value Mismatch
Observed: 
(a) As N (number of threads) increased, the frequency of mismatches would increase to counter. More threads being active means a higher chance of more than one thread enacting the RMW (read-modify-write) operations on the important global counter variable at the exact same time.
(b) Extremely high R values bring with them a much lower Actual counter than Theoretical (N * R) amount. This is a result of multiple threads overwriting each others increases in increments.
(c) If N value was lower, such as N = 5, mismatch is shown through the binary search to start at a higher R value atleast when compared to an N value higher than 5. This means less threads need more matches in order to crash.

4. Deviations
None as far as I can tell. Program follows all the strict requirements.