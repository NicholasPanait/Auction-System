#include "../appState/appState.h"
#include "../utility/utility.h"

using namespace std;

// initialize the static instance pointer to nullptr
AppState *AppState::instance = nullptr;

// returns the current singleton instance, guarantees that there is only ever one instance
AppState &AppState::getInstance()
{
    if (AppState::instance == nullptr)
    {
        AppState::instance = new AppState();
    }
    return *AppState::instance;
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