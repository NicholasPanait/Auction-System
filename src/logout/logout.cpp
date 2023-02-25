#include "logout.h"

void Logout()
{
    ofstream file;
    string file_name = AppState::getInstance().getOutputDirectory() + "/ ";

    const auto p1 = chrono::system_clock::now();
    int epoch_time = chrono::duration_cast<chrono::seconds>(p1.time_since_epoch()).count() - 1677191500;

    file_name.append(to_string(epoch_time));

    file_name.append(AppState::getInstance().getCurrentUser().username + ".txt");

    replace(file_name.begin(), file_name.end(), ':', '-');

    file.open(file_name);
    string transaction_code = "00 ";
    transaction_code += AppState::getInstance().getCurrentUser().username;
    for (int i = 0; i < 16 - AppState::getInstance().getCurrentUser().username.length(); i++)
    {
        transaction_code += ' ';
    }

    transaction_code += to_string(AppState::getInstance().getCurrentUser().credit);
    transaction_code = transaction_code.substr(0, transaction_code.length() - 4);
    if (AppState::getInstance().getTransactionBuffer() != "")
    {
        file << setprecision(2) << AppState::getInstance().getTransactionBuffer().substr(0, AppState::getInstance().getTransactionBuffer().length() - 1) << endl;
    }
    file << transaction_code << endl;
    file.close();

    AppState::getInstance().resetCurrentUser();
    cout << "Session terminated, transaction saved" << endl;
}