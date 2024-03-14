#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define maxElements 100
#define programTitle "AUTO-SUPPLY PROGRAM - CLAMONTE TECH\n\n\n"

void clearScreen()
{
    system("cls");
}

void showStatus(string message)
{
    cout<<"STATUS: "<<message<<endl<<endl;
}

string upperAlpha(string text)
{
    int i;

    for(i = 0; i < text.length(); i++)
    {
        text[i] = toupper(text[i]);
    }

    return text;
}

string inventory(int choice, string name, int quantity, int price)
{
    static string productInfo[3][maxElements] =
    {{""},
    {""},
    {""}};
    string waitForUser;
    static int elementTracker = 0;
    int column, row, ctr, total;

    if (choice == 2)
    {
        ctr = 1;

        clearScreen();
        cout<<"INVENTORY\n";
        cout<<"PRODUCT NAME : QUANTITY : PRICE\n\n";

        for(row = 0; row < maxElements; row++)
        {
            cout<<ctr<<".) ";
                
            for(column = 0; column < 3; column++)
            {
                if (productInfo[column][row] != "")
                {
                    cout<<productInfo[column][row];

                    if (column < 2)
                    {
                        cout<<" : ";
                    }
                        else
                        {
                            cout<<" PHP";
                        }
                }
                    else
                    {
                        row = maxElements - 1;
                    }
            }
                
            cout<<endl;

            ctr++;
        }

            cout<<endl<<"Input anything to continue (except blanks): ";
            cin>>waitForUser;

            clearScreen();
    }
        else if (choice == 3)
        {
            total = 0;

            for (row = 0; productInfo[2][row] != ""; row++)
            {
                total += stoi(productInfo[2][row]);
            }

            cout<<"SALES\n\n";
            cout<<"TOTAL SALES FOR ALL PRODUCTS IS "<<" PHP"<<total;

            cout<<endl<<"\nInput anything to continue (except blanks): ";
            cin>>waitForUser;

            clearScreen();
        }
            else if (choice == 4)
            {
                
                productInfo[0][elementTracker] = name;
                productInfo[1][elementTracker] = to_string(quantity);
                productInfo[2][elementTracker] = to_string(price);

                elementTracker++;
            }
}

void checkInventory()
{
    inventory(2, "", 0, 0);
}

void checkSales()
{
    inventory(3, "", 0, 0);
}

void recordTransaction()
{
    string sendName;
    int productPrice, sendPieces, sendTotal, row;
    char answer;
    bool sendReport;

    sendReport = false;

    cin.ignore();
    do
    {
        cout<<programTitle;

        cout<<"Enter the name of the product: ";
        getline(cin, sendName);
        cout<<"Enter the quantity of the product: ";
        cin>>sendPieces;
        cout<<"Enter the price of per product: ";
        cin>>productPrice;

        sendTotal = productPrice * sendPieces;

        sendName = upperAlpha(sendName);

        cout<<endl<<sendName<<" : "<<sendPieces<<"x : "<<sendTotal<<" PHP"<<endl;
        
        cout<<"Is the record above correct? (Y/N): ";
        cin>>answer;

        switch (answer)
        {
        case 'Y':
        case 'y':
            sendReport = true;

            break;
        case 'N':
        case 'n':

            break;
        default:
            clearScreen();
            showStatus("INVALID INPUT");
        }

        if (sendReport)
        {   
            clearScreen();
            inventory(4, sendName, sendPieces, sendTotal);
            showStatus("RECORD ADDED");
        }
    }while (!sendReport);
}

void requestSupply()
{
    char answer;

    cout<<"Would you like to send a re-supply request? (Y/N): ";
    cin>>answer;

    switch (answer)
        {
        case 'Y':
        case 'y':
            clearScreen();
            showStatus("REQUEST SENT");

            break;
        case 'N':
        case 'n':
            clearScreen();
            showStatus("REQUEST CANCELLED");

            break;
        default:
            clearScreen();
            showStatus("INVALID INPUT");
        }
}

void showMenu()
{
    int choice;

    clearScreen();

    do
    {
        cout<<programTitle;
        cout<<"1.) Supply Check \n2.) Inventory \n3.) Sales \n4.) Record \n5.) Exit \n\n";

        cout<<"Select an option above (1/2/3/4/5): ";
        cin>>choice;

        clearScreen();

        switch (choice)
        {
            case 1:
                requestSupply();

                break;
            case 2:
                checkInventory();

                break;
            case 3:
                checkSales();
                
                break;
            case 4:
                recordTransaction();

                break;
            case 5:
                cout<<"PROGRAM HAS EXITED\n\n";

                break;
            default:
                showStatus("INVALID INPUT!");
        }
    }while (choice != 5);
}

void logIn()
{
    string username, password, userInput;
    int attempts;
    bool found;

    attempts = 1;
    found = false;

    ifstream accountFile("account.txt");

    if (!accountFile.is_open())
    {
        showStatus("UNABLE TO LOCATE ACCOUNT");
    }

    getline(accountFile, username);
    getline(accountFile, password);

    while (!found)
    {
        clearScreen();

        if (attempts > 1)
        {
            showStatus("STATUS: INVALID USERNAME OR PASSWORD");
        }

        cout<<programTitle;
        cout<<"Log In\n\n";

        cout<<"Username: ";
        cin>>userInput;

        if (userInput == username)
        {
            cout<<"Password: ";
            cin>>userInput;

            if (userInput == password)
            {
                found = true;
            }
                else
                {
                    attempts++;
                }
        }
            else
            {
                attempts++;
            }
    }

    if (found)
    {
        showMenu();
    } 
}

int main()
{
    logIn();

    return EXIT_SUCCESS;
}