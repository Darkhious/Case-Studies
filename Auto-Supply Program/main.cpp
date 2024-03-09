#include <iostream> // Includes the input and output functionality using streams.
#include <cstdlib> // Includes arithmetics stuff and a set of general-purpose functions.
#include <fstream> // Includes the input and output for files using streams. FILE HANDLING

#define companyName "CLAMONTE TECH - AUTO SUPPLY"
#define maxElements 100

using namespace std;

void adminLevel(string name)
{
    string product[maxElements] = {""}; // Holder for Product Names
    string answer;
    int quantity[maxElements] = {0}; // Holder for the Products' Quantity
    int choice, i, counter;

    system("cls");

    cout<<companyName<<endl<<endl<<endl;
    cout<<"Welcome "<<name<<endl<<endl;
    do
    {
        cout<<"1.) Supply Check \n2.) Inventory \n3.) Sales \n4.) Exit \n\n";

        cout<<"Select an option above (1/2/3/4): ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                // This for loop will scan through the arrays product and quantity, and display its contents.
                // It will also check whether a product is low on supply by matching the same index.
                for(i = 0; i < maxElements; i++)
                {
                    if (product[i] != "")
                    {
                        if (quantity[i] != 0)
                        {
                            cout<<product[i]<<": ";
                            cout<<quantity[i]<<endl;

                            if (quantity[i] <= 10)
                            {
                                counter++;
                            }
                        }
                    }
                    
                }
                if (counter > 0) // If the loop detects products low on supply, it will ask the user if he/she wants to resupply.
                {
                    cout<<"\n\nItems low in supplies found: "<<counter<<endl;

                    cout<<"Would you like to order supplies? (Y/N): ";
                    cin>>answer;

                    if (answer.size() == 1 && !answer.empty()) //This If-else statement will check if the user entered a 1 character only.
                    {
                        if (answer == "Y" || answer == "y") //If the user entered 1 character, it will check if it is among the choices.
                        {
                            system("cls");
                            cout<<"STATUS: ORDER REQUEST HAS BEEN SENT!"<<endl<<endl;
                        }
                            else if (answer == "N" || answer == "n")
                            {
                                system("cls");
                                cout<<"STATUS: RE-SUPPLYING CANCELLED!"<<endl<<endl;
                            }
                                else
                                {
                                    system("cls");
                                    cout<<"STATUS: ERROR: INVALID INPUT!"<<endl<<endl;
                                }
                    }
                        else
                        {
                            system("cls");
                            cout<<"STATUS: ERROR: YOU ENTERED MORE THAN 1 CHARACTER!"<<endl<<endl;
                        }
                }

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                
                break;
            default:
                cout<<"ERROR: INVALID INPUT!";
        }
    }while (choice != 4);
    
}

void employeeLevel(string name)
{
    system("cls");

    cout<<companyName<<endl<<endl<<endl;
    cout<<"Welcome "<<name<<endl<<endl;
}

int main()
{
    const int logInLimit = 5;

    string userName, userPass, filename, key, userLevel;
    int logInAttempts; // A variable to limit the log in attempts to enhance security features. It is similar to how passcodes in phones works.
    bool found = false;

    logInAttempts = 1;

    // LOG IN VERIFICATION - SECURITY PURPOSES
    while (!found && logInAttempts <= logInLimit)
    {

        system("cls"); // This code will clear the output screen of the terminal for a clean look.

        cout<<companyName<<endl<<endl<<endl;
        cout<<"Log In"<<endl<<endl;

        if (logInAttempts > 1) // This will display an error message if a user entered a wrong username.
        {
            cout<<"ERROR: INCORRECT USERNAME!"<<endl<<endl;
        }

        cout<<"Username: ";
        getline(cin, userName);

        filename = userName + ".txt"; // Creates a filename to be accessed.

        ifstream account(filename); // Opens the specified file as an input stream to take the PASSWORD KEY in it.
        if (account.is_open()) // This is only for the Input of password, if the user's account is found.
        {
            getline(account, key); // This code will get the whole first line of the text file.

            logInAttempts = 1;  // Resets the log in attempts to be used for the password.
            while (!found && logInAttempts <= logInLimit)
            {
                if (logInAttempts > 1) // This will be used to redisplay what was displayed earlier after the screen is cleared.
                {
                    system("cls");

                    cout<<companyName<<endl<<endl;
                    cout<<"Log In"<<endl<<endl;
                    cout<<"ERROR: INCORRECT PASSWORD!"<<endl<<endl;
                    cout<<"Username: "<<userName<<endl;
                }

                // The program will now ask for the password of the account.
                cout<<"Password: ";
                getline(cin, userPass);

                // This will display a LOG IN SUCCESS for testing purposes.
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

    // Once found this will activate certain users levels.
    if (found)
    {
        ifstream account(filename);
        getline(account, userLevel);
        getline(account, userLevel); // We used 2 getline to get where the user level is located within the .txt file.

        if (userLevel == "ADMIN")
        {
            adminLevel(userName);
        }
            else if (userLevel == "EMPLOYEE")
            {
                employeeLevel(userName);
            }
                else
                {
                    cout<<"ERROR: CANNOT DETERMINE ACCOUNT LEVEL!"<<endl;
                }
    }

    return EXIT_SUCCESS;
}