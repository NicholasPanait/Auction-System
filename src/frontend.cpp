#include <iostream>
#include "utility/utility.h"
#include "appState/appState.h"
#include <string>
#include <fstream>
using namespace std;

// TODO: create, delete, refund

// Tests if a file exists in the project directory
bool filesExist(char *argv[])
{
    try
    {
        for (int i = 1; i < 3; i++)
        {
            ifstream file(argv[i]);
            if (!file)
            {
                throw runtime_error("File not found: " + string(argv[i]));
            }
            // read data from the file...
            file.close();
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
    return true;
}

/*** RETURN CODES
 * 0: Program ran with no errors
 * 1: Too many command line arguments
 * 2: Files do not exist
 ***/

// argc: num arguments
// argv: vector of parameters
// ORDER OF PARAMETERS: USERFILE ITEMFILE OUTPUTDIRECTORY
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Please enter the following files: itemFile, accountFile, outputDirectory" << endl;
        return 1;
    }
    else if (filesExist(argv))
    {
        AppState::getInstance().setUserFile(argv[1]);
        AppState::getInstance().setItemFile(argv[2]);
        AppState::getInstance().setOutputDirectory(argv[3]);

        cout << "Welcome to Hubble Auction House" << endl;
        while (true)
        {
            string command;
            cout << "Please enter a command:" << endl;
            cin >> command;
            ProcessCommand(command);
        }
        return 0;
    }
    else
    {
        return 2;
    }
}