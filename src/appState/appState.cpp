#include "../appState/appState.h"
#include "../utility/utility.h"

using namespace std;


//returns the current singleton instance, grantees that there is only every one instance
AppState &AppState::getInstance(){
	static AppState INSTANCE;
	return INSTANCE;

}

// Singleton constructor, should only ever be called by getInstance()
AppState::AppState()
{
    this->currentUser = nullptr;
    this->transactionBuffer = "";
    this->itemFile = "";
    this->userFile = "";
    this->outputDirectory = "";
}

bool AppState::isLoggedIn()
{
    return (this->currentUser != nullptr);
}

User &AppState::getCurrentUser()
{
    if (this->currentUser == nullptr)
    {
        this->currentUser = new User();
    }
    return *this->currentUser;
}

string AppState::getTransactionBuffer() const
{
    return this->transactionBuffer;
}

string AppState::getUserFile() const
{
    return this->userFile;
}

string AppState::getItemFile() const
{
    return this->itemFile;
}

string AppState::getOutputDirectory() const
{
    return this->outputDirectory;
}

void AppState::setCurrentUser(User user)
{
    if (this->currentUser == nullptr)
    {
        this->currentUser = new User();
    }
    *(this->currentUser) = user;
}

void AppState::resetCurrentUser()
{
    this->currentUser = nullptr;
}

void AppState::appendTransactionBuffer(string transaction)
{
    this->transactionBuffer.append(transaction);
}

void AppState::setUserFile(string file)
{
    this->userFile = file;
}

void AppState::setItemFile(string file)
{
    this->itemFile = file;
}

void AppState::setOutputDirectory(string directory)
{
    this->outputDirectory = directory;
}