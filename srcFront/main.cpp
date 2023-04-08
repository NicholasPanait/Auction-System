/*
 * CSCI 3060 - Phase 2: FIRST RAPID PROTOTYPE
 * Authors: 
 *
 * Group Name: CSCI 3060 - ASC
 *
 * Submission Date: February 17th, 2023
 * Version: 1.0
 *
 * Description:
 * The following program is a the first rapid prototype for the console based, online auction system.
 * It allows users to conduct various types of transactions such as advetising, bidding, based
 * on the user type. All the information for each user, item and transaction is written to the user
 * accounts file, the available items file, and the daily transaction file respectively. In each
 * login session, the user is allowed to complete one transaction.
 */

#include "Application.h"

/*
 * The main method is used to start running the program in the command line by creating an instance
 * of the application class and calling the start function on it.
 *
 * @return - On a successful run, the main function returns 0.
 */
int main(int argc, char **argv)
{
    if (argc < 4) {
        std::cout << "Invalid amount of arguments\n";
        return 1;
    }
    Application app;
    app.start(argv);

    return 0;
}
