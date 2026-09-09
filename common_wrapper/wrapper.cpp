#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: ./wrapper <assignment_folder> <algorithm> <input_file>\n";
        cout << "Example: ./wrapper assignment_04 kmeans ../testFiles/km_01.txt\n";
        return 1;
    }

    string assignmentDir = argv[1];
    string algorithm = argv[2];
    string inputFile = argv[3];

    string command = "./" + assignmentDir + "/outputs/driver.out " + inputFile + " " + algorithm;
    
    cout << "Executing: " << command << "\n";
    cout << string(40, '-') << "\n";
    
    int result = system(command.c_str());
    
    if (result != 0) {
        cout << "\nCommand failed with code: " << result << "\n";
    }

    return result;
}