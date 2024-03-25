#include <iostream>
#include <cstdlib>

using namespace std;

#define PROGRAMTITLE "AUTO-SUPPLY PROGRAM - CLAMONTECH"

const int MAXELEMENTS = 100, PRDOUCTINFOFIELDS = 3;
const string USERNAME = "admin", PASSWORD = "admin";

int elementTracker = 0;
string productInfo[PRDOUCTINFOFIELDS][MAXELEMENTS] =
    {{""},
    {""},
    {""}};

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

bool isDigit(string input)
{
    int i;
    char alphaNum;
    bool found;

    found = false;

    for(i = 0; i < input.length(); i++)
    {
        alphaNum = input[i];

        if (alphaNum >= '0' && alphaNum <= '9')
        {
            continue;
        }
            else
            {
                found = true;
            }
    }

    if (found)
    {
        return false;
    }
        else
        {
            return true;
        }
}

void waitForUser()
{
    string response;

    cin.ignore();

    cout<<endl<<"Input anything to continue: ";
    getline(cin, response);
}

bool confirmation(string response)
{
    if (response == "Y" || response == "y")
    {
        clearScreen();
        return true;
    }
        else if (response == "N" || response == "n")
        {
            clearScreen();
            return false;
        }
            else
            {
                clearScreen();
                showStatus("INVALID INPUT! Please input Y/N only.");
                return false;
            }
}

void checkInventory()
{
    int ctr, row, column;

    ctr = 1;

    clearScreen();
    cout<<"INVENTORY\n";
    cout<<"PRODUCT NAME : QUANTITY : PRICE\n\n";

    for(row = 0; row < MAXELEMENTS; row++)
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
                    row = MAXELEMENTS - 1;
                }
        }
                
        cout<<endl;

        ctr++;
    }

        waitForUser();
        clearScreen();
}

void checkSales()
{
    string productName;
    int productQuantity, productSale, totalSale, i, j;
    bool alreadyReported;

    totalSale = 0;

    clearScreen();
    cout << "SALES\n\n";

    for (int row = 0; row < MAXELEMENTS; row++)
    {
        if (productInfo[0][row] != "")
        {
            productQuantity = stoi(productInfo[1][row]);
            productSale = stoi(productInfo[2][row]);
            productName = productInfo[0][row];
            totalSale += productSale;

            alreadyReported = false;
            for (i = 0; i < row; i++)
            {
                if (productName == productInfo[0][i])
                {
                    alreadyReported = true;

                    break;
                }
            }

            if (!alreadyReported)
            {
                for (j = row + 1; j < MAXELEMENTS; j++)
                {
                    if (productName == productInfo[0][j])
                    {
                        productQuantity += stoi(productInfo[1][j]);
                        productSale += stoi(productInfo[2][j]);
                    }
                }

                cout<<productName<<"\nQUANTITY SOLD: "<<productQuantity<<"\nTOTAL SALE: "<<productSale<<" PHP\n\n";
            }
        }
    }

    cout << "TOTAL SALES FOR ALL PRODUCTS IS " << totalSale << " PHP\n";

    waitForUser();
    clearScreen();
}

void recordTransaction()
{
    string sendName, input, answer;
    int productPrice, sendPieces, sendTotal;
    bool correctInput, recording;

    correctInput = false;
    recording = true;

    if (elementTracker == 99)
    {
        showStatus("WARNING! INVENTORY FULL!");

        recording = false;
    }
        else if (elementTracker >= 90)
        {
            showStatus("WARNING! INVENTORY ALMOST FULL!");
        }
            else if (elementTracker >= 80)
            {
                showStatus("WARNING! INVENTORY MIGHT OVERFLOW!");
            }
                else
                {
                    showStatus("INVETORY IS STILL SPACIOUS");
                }


    cin.ignore();
    while (recording)
    {
        cout<<PROGRAMTITLE<<endl<<endl;
        cout<<"Enter nothing to exit.\n";

        cout<<"Enter the name of the product: ";
        getline(cin, sendName);

        if (sendName.empty())
        {
            clearScreen();

            break;
        }
            else
            {
                sendName = upperAlpha(sendName);

                cout<<"Enter the quantity of the product: ";
                cin>>input;
                cin.ignore();

                correctInput = isDigit(input);

                if (correctInput)
                {
                    sendPieces = stoi(input);

                    cout<<"Enter the price of per product: ";
                    cin>>input;
                    cin.ignore();

                    correctInput = isDigit(input);

                    if (correctInput)
                    {
                        productPrice = stoi(input);
                        sendTotal = sendPieces * productPrice;

                        cout<<endl<<sendName<<" : "<<sendPieces<<"x : "<<sendTotal<<" PHP"<<endl;
    
                        cout<<"Is the record above correct? (Y/N): ";
                        cin>>answer;
                        cin.ignore();

                        if (confirmation(answer))
                        {
                            productInfo[0][elementTracker] = sendName;
                            productInfo[1][elementTracker] = to_string(sendPieces);
                            productInfo[2][elementTracker] = to_string(sendTotal);

                            elementTracker++;

                            showStatus("TRANSACTION RECORDED!");

                            continue;
                        }
                    }
                        else
                        {
                            clearScreen();
                            showStatus("INVALID INPUT! Please input numbers only.");

                            continue;
                        }
                }
                    else
                    {
                        clearScreen();
                        showStatus("INVALID INPUT! Please input numbers only.");

                        continue;
                    }
            }           
    }
}

void requestSupply()
{
    string answer;

    cout<<"Would you like to send a re-supply request? (Y/N): ";
    cin>>answer;

    if (confirmation(answer))
    {
        showStatus("STATUS: REQUEST SENT!");
    }
        else
        {
            showStatus("STATUS: REQUEST CANCELLED!");
        }
}

void showMenu()
{
    string choice;
    int option;
    bool correctInput;

    clearScreen();

    do
    {
        do
        {

            cout<<PROGRAMTITLE<<endl<<endl;
            cout<<"Welcome, "<<USERNAME<<"!\n\n";
            cout<<"1.) Supply Check \n2.) Inventory \n3.) Sales \n4.) Record \n5.) Exit \n\n";

            cout<<"Select an option above (1/2/3/4/5): ";
            cin>>choice;

            correctInput = isDigit(choice);

            if (!correctInput)
            {
                clearScreen();
                showStatus("INVALID INPUT! Please enter numbers only.");
            }
        }while (!correctInput);

        option = stoi(choice);

        clearScreen();

        switch (option)
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
                showStatus("INVALID INPUT! Please select a valid option.");
        }
    }while (option != 5);
}

void logIn()
{
    string userInput;
    int attempts;
    bool found;

    attempts = 1;
    found = false;

    while (!found)
    {
        clearScreen();

        if (attempts > 1)
        {
            showStatus("STATUS: INVALID USERNAME OR PASSWORD");
        }

        cout<<PROGRAMTITLE<<endl<<endl;
        cout<<"Log In\n\n";

        cout<<"Username: ";
        cin>>userInput;

        if (userInput == USERNAME)
        {
            cout<<"Password: ";
            cin>>userInput;

            if (userInput == PASSWORD)
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