#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main () {

    vector<int> path;

    ifstream file("path.txt");
    int value;
    while(file >> value) {
        path.push_back(value);
    }

    file.close();

    for(int i = 3; i < path.size(); i++) {
        if(path[i-3] == path[i]) cout << "falsch!!!!" << endl;
    }



}