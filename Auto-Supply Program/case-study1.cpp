#include <iostream> //Includes the input and output functionality using streams.
#include <cstdlib> //Includes arithmetics stuff and a set of general-purpose functions.
#include <fstream> //Includes the input and output for files using streams. FILE HANDLING

using namespace std;

int main()
{
    string userName, userPass, filename, key;
    int logInAttempts = 0; //A variable to limit the log in attempts to enhance security features. It is similar to how passcodes in phones works.
    bool found = false;

    //LOG IN VERIFICATION - SECURITY PURPOSES
    while (!found && logInAttempts <= 3)
    {

        system("cls"); // This code will clear the output screen of the terminal for a clean look.

        cout<<"CLAMONTE TECH - AUTO SUPPLY"<<endl<<endl<<endl;
        cout<<"Log In"<<endl<<endl;

        if (logInAttempts > 0) //This will display an error message if a user entered a wrong username.
        {
            cout<<"ERROR: INCORRECT USERNAME!"<<endl<<endl;
        }

        cout<<"Username: ";
        cin>>userName;

        filename = userName + ".txt"; //Creates a filename to be accessed.

        ifstream account(filename); //Opens the specified file as an input stream to take the PASSWORD KEY in it.
        if (account.is_open()) //This is only for the Input of password, if the user's account is found.
        {
            getline(account, key); //This code will get the whole first line of the text file.

            logInAttempts = 0;  //Resets the log in attempts to be used for the password.
            while (!found && logInAttempts <= 3)
            {
                if (logInAttempts > 0) //This will be used to redisplay what was displayed earlier after the screen is cleared.
                {
                    system("cls");

                    cout<<"CLAMONTE TECH - AUTO SUPPLY"<<endl<<endl;
                    cout<<"Log In"<<endl<<endl;
                    cout<<"ERROR: INCORRECT PASSWORD!"<<endl<<endl;
                    cout<<"Username: "<<userName<<endl;
                }

                //The program will now ask for the password of the account.
                cout<<"Password: ";
                cin>>userPass;

                //This will display a LOG IN SUCCESS for testing purposes.
                if (userPass == key)
                {
                    cout<<"SUCCESS!"<<endl;
                    found = true;
                }
                    else
                    {
                        logInAttempts++;
                    }
            }
        }
            else
            {
                logInAttempts++;
            }

    }

    return EXIT_SUCCESS;
}