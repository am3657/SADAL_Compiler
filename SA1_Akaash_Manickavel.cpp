#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {

    string question = "What are your first name, last name, and section number?";
    string answer = "";
    string sec = "";
    string name = "";

    cout << "Welcome to CS280 (Spring 2025)" << endl;
    cout << question << endl;
    getline(cin, answer);
    int i = 0;
    while (i < answer.length()) {
        if (isdigit(answer[i])) {
            sec += answer[i];
        }
        else {
            name += answer[i];
        }
        i++;
    }
    int index = name.find(" ");
    string first = name.substr(0, index);
    cout <<"Hello "<<first<<", Welcome to CS 280 Section " <<sec<<"."<< endl;
    return 0;
}

