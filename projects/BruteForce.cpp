#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <array>
#include <cstring>

using namespace std;

// Function to run the hackMe executable and check access
bool softwareAccess(const string& attempt) {
    // Create pipes for communication
    int inputPipe[2];  // Pipe for input
    int outputPipe[2]; // Pipe for output

    // Create the pipes
    if (pipe(inputPipe) == -1) {
        cerr << "Pipe creation for input failed: " << strerror(errno) << endl;
        return false;
    }
    if (pipe(outputPipe) == -1) {
        cerr << "Pipe creation for output failed: " << strerror(errno) << endl;
        close(inputPipe[0]);
        close(inputPipe[1]);
        return false;
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Fork failed: " << strerror(errno) << endl;
        close(inputPipe[0]);
        close(inputPipe[1]);
        close(outputPipe[0]);
        close(outputPipe[1]);
        return false;
    }

    if (pid == 0) { // Child process
        // Close unused pipe ends
        close(inputPipe[1]);  // Close write end of input pipe
        close(outputPipe[0]); // Close read end of output pipe

        // Redirect stdin and stdout
        dup2(inputPipe[0], STDIN_FILENO);  // Redirect stdin to inputPipe read end
        dup2(outputPipe[1], STDOUT_FILENO); // Redirect stdout to outputPipe write end

        // Execute the hackMe program
        execl("./hackMe", "hackMe", (char*)nullptr);
        
        // If exec fails
        cerr << "Exec failed: " << strerror(errno) << endl;
        exit(1); // Exit child process
    } else { // Parent process
        // Close unused pipe ends
        close(inputPipe[0]);  // Close read end of input pipe
        close(outputPipe[1]); // Close write end of output pipe

        // Write the password attempt to the input pipe
        write(inputPipe[1], attempt.c_str(), attempt.size());
        write(inputPipe[1], "\n", 1); // Add newline to simulate pressing enter
        close(inputPipe[1]); // Close the input pipe after writing

        // Read the output from the output pipe
        array<char, 128> buffer;
        string result;
        ssize_t bytesRead;

        while ((bytesRead = read(outputPipe[0], buffer.data(), buffer.size())) > 0) {
            result.append(buffer.data(), bytesRead);
        }

        // Close the output pipe after reading
        close(outputPipe[0]);

        // Wait for child process to finish
        waitpid(pid, nullptr, 0);

        // Check if the result contains "Access granted!"
        return result.find("Access granted!") != string::npos;
    }
}

// Generates the next password attempt
void generateNextAttempt(string &attempt, const string &characters) {
    int length = attempt.size();
    
    // Start from the last character of the attempt string
    for (int i = length - 1; i >= 0; --i) {
        // Find current character's position in `characters`
        int pos = characters.find(attempt[i]);
        
        // If it's the last character in `characters`, reset and carry over
        if (pos == characters.size() - 1) {
            attempt[i] = characters[0]; // Reset to the first character
        } else {
            // Move to the next character in `characters`
            attempt[i] = characters[pos + 1];
            return; // Stop after incrementing one character
        }
    }
}

// Brute-force password cracker function
void bruteForceCrack() {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&"; // Possible characters
    string attempt;

    // Start brute-force attempts
    for (int len = 1; len <= 5; ++len) {  // Max length of 5
        attempt = string(len, characters[0]);  // Initialize attempt string of size `len`
        
        while (true) {
            // Try to access software with current attempt
            if (softwareAccess(attempt)) {
                cout << "Password cracked: " << attempt << endl;
                return;
            }

            // Generate next combination
            generateNextAttempt(attempt, characters);

            // Break if we wrapped back to the starting combination for this length
            if (attempt == string(len, characters[0])) break;
        }
    }

    cout << "Password not found." << endl;
}

int main() {
    bruteForceCrack();
    return 0;
}
