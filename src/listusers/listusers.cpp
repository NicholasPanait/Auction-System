#include "listusers.h"
using namespace std;
//TODO: Implement the list users command so that it lists all the users and there credits
void ListUsers(){
    string output;
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
                output.append(line);
                output.append("\n");
            }
        }
    }
    input.close();
}