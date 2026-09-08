#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../../common_wrapper/timer.h" 
#include "../src/KMEANS.h"
#include "../src/FASTMAP.h"

using namespace std;

// Helper to extract just the filename from a relative/absolute path
string getBaseName(const string& path) {
    size_t pos = path.find_last_of("/\\");
    return (pos == string::npos) ? path : path.substr(pos + 1);
}

void runKMeans(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) { cout << "| " << getBaseName(filePath) << " | - | - | - | - | - | - | - | Fail (File Error) |\n"; return; }

    int N, D, K;
    file >> N >> D >> K;
    if (N <= 0 || D <= 0 || K <= 0 || K > N) {
        cout << "| " << getBaseName(filePath) << " | " << N << " | " << D << " | " << K << " | - | - | - | - | Fail (Invalid Input) |\n";
        return;
    }

    vector<vector<double>> points(N, vector<double>(D));
    for (int i = 0; i < N; ++i) {
        for (int d = 0; d < D; ++d) file >> points[i][d];
    }

    string dummy; int maxIter; double tol;
    file >> dummy >> maxIter >> dummy >> tol;     
    file.close();

    Timer t;
    t.start();
    KMeansResult res = funcKMeans(N, D, K, points, maxIter, tol);
    double elapsedSeconds = t.stop();

    // Markdown Table Row Output
    // File | N | D | K | Max Iter. | Actual Iter. | WCSS | Time | Status
    cout << fixed << setprecision(2);
    cout << "| " << getBaseName(filePath) << " | " << N << " | " << D << " | " << K << " | " 
         << maxIter << " | " << res.iterations << " | " << res.wcss << " | " 
         << (elapsedSeconds * 1000.0) << " ms | " << (res.converged ? "Pass" : "Fail (DNC)") << " |\n";
}

void runFastMap(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) { cout << "| " << getBaseName(filePath) << " | - | - | - | - | - | Fail (File Error) |\n"; return; }

    int N, k;
    file >> N >> k;
    if (N <= 0 || k <= 0 || k >= N) {
        cout << "| " << getBaseName(filePath) << " | " << N << " | " << k << " | - | - | - | Fail (Invalid Input) |\n";
        return;
    }

    vector<vector<double>> D(N, vector<double>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) file >> D[i][j];
    }
    file.close();

    Timer t;
    t.start();
    FastMapResult res = funcFastMap(N, k, D);
    double elapsedSeconds = t.stop();

    // Format pivots[cite: 8]
    string pivots = "";
    for(size_t i=0; i<res.pivots.size(); ++i) {
        pivots += "(" + to_string(res.pivots[i].first) + "," + to_string(res.pivots[i].second) + ")";
        if (i < res.pivots.size() - 1) pivots += ", ";
    }

    // Markdown Table Row Output[cite: 8]
    // File | N | Target k | Pivots (per dim) | Avg. Distance Error | Time | Status
    cout << fixed << setprecision(2);
    cout << "| " << getBaseName(filePath) << " | " << N << " | " << k << " | " 
         << pivots << " | N/A | " << (elapsedSeconds * 1000.0) << " ms | Pass |\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    string fileName = argv[1];
    string algo = argv[2];

    if (algo == "kmeans") runKMeans(fileName);
    else if (algo == "fastmap") runFastMap(fileName);
    
    return 0;
}