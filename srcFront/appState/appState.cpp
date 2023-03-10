#include "appState.h"

/**
 * This class contains universal information that is used throughout the frontend
 * which includes, current Logged In User, session's Added Credit, the Transaction
 * Buffer and the paths to the Item File, User File, and Output Directory
 */

/**
 * @return The current singleton instance containing universal information,
 *         guarantees that there is only ever one instance
 */
AppState &AppState::getInstance(){
	static AppState INSTANCE;
	return INSTANCE;

}

/**
 * Singleton constructor, should only ever be called by getInstance()
 */
AppState::AppState()
{
    this->currentUser = nullptr;
    this->transactionBuffer = "";
    this->itemFile = "";
    this->userFile = "";
    this->outputDirectory = "";
    this->addedCredit = 0.0;
}

/**
 * @return A boolean based on whether the user is logged in or not
 */
bool AppState::isLoggedIn()
{
    return (this->currentUser != nullptr);
}

/**
 * @return The current logged in user as a User object
 */
User &AppState::getCurrentUser()
{
    if (this->currentUser == nullptr)
    {
        this->currentUser = new User();
    }
    return *this->currentUser;
}

/**
 * @return The current transaction buffer
 */
string AppState::getTransactionBuffer() const
{
    return this->transactionBuffer;
}

/**
 * @return The path to the User File currently used by the frontend
 */
string AppState::getUserFile() const
{
    return this->userFile;
}

/**
 * @return The path to the Item File currently used by the frontend
 */
string AppState::getItemFile() const
{
    return this->itemFile;
}

/**
 * @return The path to the Output Directory currently used by the frontend
 */
string AppState::getOutputDirectory() const
{
    return this->outputDirectory;
}

/**
 * @return The session's current Added Credit (for addcredit's limit of $1000)
 */
double AppState::getAddedCredit() const
{
    return this->addedCredit;
}

/**
 * Function used to reset the currently logged in User
 */
void AppState::resetCurrentUser()
{
    this->currentUser = nullptr;
}

/**
 * Function to reset the session's Added Credit
 */
void AppState::resetAddedCredit()
{
    this-> addedCredit = 0;
}

/**
 * Function to set the current User logged in
 *
 * @param user The User to be set as the current logged in user
 */
void AppState::setCurrentUser(User user)
{
    if (this->currentUser == nullptr)
    {
        this->currentUser = new User();
    }
    *(this->currentUser) = user;
}

/**
 * Function to append a transaction code to the transaction buffer
 *
 * @param transaction The transaction code to be appended to the transaction buffer
 */
void AppState::appendTransactionBuffer(string transaction)
{
    this->transactionBuffer.append(transaction);
}

/**
 * Function to set the path to the User File currently used by the frontend
 *
 * @param file The path to the User File
 */
void AppState::setUserFile(string file)
{
    this->userFile = file;
}

/**
 * Function to set the path to the Item File currently used by the frontend
 *
 * @param file The path to the Item File
 */
void AppState::setItemFile(string file)
{
    this->itemFile = file;
}

/**
 * Function to set the path to the Output Directory currently used by the frontend
 *
 * @param directory The path to the Output Directory
 */
void AppState::setOutputDirectory(string directory)
{
    this->outputDirectory = directory;
}

/**
 * Function to add credit to the session's Added Credit
 *
 * @param credit The credit to be added to the session's Added Credit
 */
void AppState::addCredit(double credit)
{
    this->addedCredit += credit;
}