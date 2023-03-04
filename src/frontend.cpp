#include <iostream>
#include "utility/utility.h"
#include "appState/appState.h"
#include <string>
#include <fstream>
using namespace std;

// NOTE: We recomend using the Better Comments extension from the VSCode Marketplace

/**
 * Tests if a file exists in the project directory
 * @param argv  The inputs from the user, contains locations for files and directories
 * @return      Reurns true if the files and directories are valid
*/
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

/**
 * @param argc  num arguments
 * @param argv  vector of parameters
 * @return      Returns numbers based on different errors:
 *                  0: Program ran with no errors
 *                  1: Too many command line arguments
 *                  2: Files do not exist
 */

//  * ORDER OF PARAMETERS: USERFILE ITEMFILE OUTPUTDIRECTORY
//  * Linux Example: ./frontend.exe ../res/UserFile.txt ../res/ItemFile.txt ../res/logs
//  * Windows Example: frontend.exe ../res/UserFile.txt ../res/ItemFile.txt ../res/logs
/*
? Account Info
! MasterAdmin = ADMIN
! SuperMod = Super
! LongTimeJoe = 123
! WarehouserJane = Houser
! CheapKent = discounts4life
! NoBuyOlivia = Sella
! NewBuyerSteve = L33TSP33K
! Test Space = S P A C E
*/
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
        string command = "";
        while (command != "exit")
        {
            cout << "Please enter a command:" << endl;
            cin >> command;
            if (command != "exit") ProcessCommand(command);
        }
        return 0;
    }
    else
    {
        return 2;
    }
}