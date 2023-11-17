#include <iostream>
#include <pthread.h>
#include <sstream>

using namespace std;

// goal 1
string inputPhrase;

/* goal 3, using the current thread variable to control the 
execution sequence 
*/
int currentThread = 1;

// Function to check if a word starts with an alphabet character
bool startsWithAlpha(const string& word) {
    return !word.empty() && isalpha(word[0]);
}

// Function to check if a word starts with a numeric character
bool startsWithNumeric(const string& word) {
    return !word.empty() && isdigit(word[0]);
}

// Common function to process words
void* processWords(void* arg) {
    int threadId = *(int*)arg;
    istringstream iss(inputPhrase);
    string word;

    while (true) {
        if (currentThread == threadId) {
            while (iss >> word) {
                if ((threadId == 1 && startsWithAlpha(word)) || (threadId == 2 && startsWithNumeric(word))) {
                    cout << (threadId == 1 ? "alpha: " : "numeric: ") << word << endl;
                }
            }
            currentThread = threadId == 1 ? 2 : 1;  // Switch to the other thread
            break;
        }
    }

    pthread_exit(NULL);
}

int main() {
    cout <<"Enter String: ";
    // Read the input phrase
    getline(cin, inputPhrase);
    cout << "\n";

    // Thread identifiers
    pthread_t p1, p2;
    int alphaThreadId = 1;
    int numericThreadId = 2;

    // goal 2, main shoud create 2 concurrent threads
    pthread_create(&p1, NULL, processWords, &alphaThreadId);
    pthread_create(&p2, NULL, processWords, &numericThreadId);

    // Wait for the threads to complete
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    return 0;
}
