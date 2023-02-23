#include "listusers.h"
#include "../appState/appState.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;
//TODO: Implement the list users command so that it lists all the users and there credits
void ListUsers(){
    string output = "Username\tAccount Type\tCredits:";
    string line;
    ifstream input(AppState::getInstance().getUserFile());
    if (input.is_open())
    {
        while (getline(input, line))
        {
            if (line == "END")
            {
                input.close();
            }
            else
            {
                output.append("\n");
                output.append(line.substr(0, 18) + "\t\t"); // username and account type
                output.append("$" + RemoveLeading(line.substr(19, 9), '0')); // credits
            }
        }
    }
    cout << output << endl;
    input.close();
}