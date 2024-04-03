#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define PROGRAMTITLE "AUTO-SUPPLY PROGRAM - CLAMONTECH"

const int MAXELEMENTS = 100, PRDOUCTINFOFIELDS = 3;

int elementTracker = 0, i, j;
string productInfo[PRDOUCTINFOFIELDS][MAXELEMENTS] =
    {{""},
    {""},
    {""}};
string supplyName[MAXELEMENTS] = {""};
int supplyQuantity[MAXELEMENTS] = {0};
string userInput;
bool found;

void clearScreen()
{
    system("cls");
}

void showStatus(string message)
{
    clearScreen();
    cout<<"STATUS: "<<message<<endl<<endl;
}

string upperAlpha(string text)
{
    for(i = 0; i < text.length(); i++)
    {
        text[i] = toupper(text[i]);
    }

    return text;
}

bool isDigit(string input)
{
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
    cout<<endl<<"Input anything to continue: ";
    getline(cin, userInput);
}

bool confirmation(string response)
{
    if (response == "Y" || response == "y")
    {
        return true;
    }
        else if (response == "N" || response == "n")
        {
            return false;
        }
            else
            {
                showStatus("INVALID INPUT! Please input Y/N only.");
                return false;
            }
}

bool searchItem(string item)
{
    for (i = 0; i < MAXELEMENTS; i++)
    {
        if (item == supplyName[i])
        {
            return true;
        }
            else
            {
                return false;
            }
    }
}

void checkInventory()
{
    int ctr, row, column;

    ctr = 1;

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
    int productQuantity, productSale, totalSale;
    bool alreadyReported;

    totalSale = 0;

    cout<<"SALES\n\n";

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

    cout<<"TOTAL SALES FOR ALL PRODUCTS IS "<<totalSale <<" PHP\n";

    waitForUser();
    clearScreen();
}

void recordTransaction()
{
    string sendName;
    int productPrice, sendPieces, sendTotal, levelMeter;
    bool correctInput, recording;

    levelMeter = MAXELEMENTS - 1;
    correctInput = false;
    recording = true;

    if (elementTracker == levelMeter)
    {
        levelMeter -= 9;
        recording = false;

        showStatus("WARNING! INVENTORY FULL!");
    }
        else if (elementTracker >= levelMeter)
        {
            levelMeter -= 10;

            showStatus("WARNING! INVENTORY ALMOST FULL!");
        }
            else if (elementTracker >= levelMeter)
            {
                showStatus("WARNING! INVENTORY MIGHT OVERFLOW!");
            }
                else
                {
                    showStatus("INVETORY IS STILL SPACIOUS");
                }

    while (recording)
    {
        cout<<PROGRAMTITLE<<endl<<endl;
        cout<<"Enter nothing to exit.\n";

        cout<<"Enter the name of the product: ";
        getline(cin, sendName);

        sendName = upperAlpha(sendName);
        if (sendName == "")
        {
            clearScreen();

            break;
        }
            else
            {
                found = searchItem(sendName);
                if (found)
                {
                    cout<<"Enter the quantity of the product: ";
                    getline(cin, userInput);

                    correctInput = isDigit(userInput);

                    if (correctInput)
                    {
                        sendPieces = stoi(userInput);

                        cout<<"Enter the price of per product: ";
                        getline(cin, userInput);

                        correctInput = isDigit(userInput);

                        if (correctInput)
                        {
                            productPrice = stoi(userInput);
                            sendTotal = sendPieces * productPrice;

                            cout<<endl<<sendName<<" : "<<sendPieces<<"x : "<<sendTotal<<" PHP"<<endl;
        
                            cout<<"Is the record above correct? (Y/N): ";
                            getline(cin, userInput);

                            if (confirmation(userInput))
                            {
                                productInfo[0][elementTracker] = sendName;
                                productInfo[1][elementTracker] = to_string(sendPieces);
                                productInfo[2][elementTracker] = to_string(sendTotal);

                                for (i = 0; i < MAXELEMENTS; i++)
                                {
                                    if (sendName == supplyName[i])
                                    {
                                        supplyQuantity[i] -= sendPieces;

                                        break;
                                    }
                                }
                                elementTracker++;

                                showStatus("TRANSACTION RECORDED!");
                            }
                        }
                            else
                            {
                                showStatus("INVALID INPUT! Please input numbers only.");
                            }
                    }
                        else
                        {
                            showStatus("INVALID INPUT! Please input numbers only.");
                        }
                }
                    else
                    {
                        showStatus("Could not find the item. Please ensure the supply of the item.");
                    }
            }           
    }
}

void checkSupply()
{
    string product, amount;
    int ctr;

    ctr = 1;

    cout<<"SUPPLY CENTER\n\n";

    for (i = 0; i < MAXELEMENTS; i++)
    {
        if (supplyName[i] == "")
        {
            break;
        }
            else
            {
                cout<<"("<<ctr<<")\n";
                cout<<"PRODUCT NAME: "<<supplyName[i]<<endl;
                cout<<"AMOUNT LEFT: "<<supplyQuantity[i]<<"x\n\n";

                ctr++;
            }
    }

    cout<<"Would you like to request for supplies? (Y/N): ";
    getline(cin, userInput);

    if (confirmation(userInput))
    {
        ifstream supply("supplyDrop.clt");

        if (supply.is_open())
        {
            while (getline(supply, product))
            {
                getline(supply, amount);

                product = upperAlpha(product);
                found = false;

                for (i = 0; supplyName[i] != ""; i++)
                {
                    if (product == supplyName[i])
                    {
                        supplyQuantity[i] += stoi(amount);
                        found = true;
                    }
                }

                if (!found)
                {
                    for(i = 0; i < MAXELEMENTS; i++)
                    {
                        if (supplyName[i] == "")
                        {
                            supplyName[i] = product;
                            supplyQuantity[i] = stoi(amount);

                            break;
                        }
                    }
                }
            }

            supply.close();
            remove("supplyDrop.clt");

            showStatus("Request for supply has been sent!");
        }
            else
            {
                showStatus("The supply invoice seems to be missing. Request has been sent!");
            }
    }
        else
        {
            showStatus("Request Cancelled!");
        }
}

string logIn()
{
    string line, filename, key, username;
    int attempts;

    attempts = 1;
    found = false;

    while (!found)
    {
        key = "";

        clearScreen();

        if (attempts > 1)
        {
            showStatus("INVALID USERNAME OR PASSWORD");
        }

        cout<<PROGRAMTITLE<<endl<<endl;
        cout<<"Log In\n\n";

        cout<<"Username: ";
        getline(cin, userInput);

        filename = userInput + ".clt";
        ifstream account(filename);

        username = userInput;
        if (account.is_open())
        {
            getline(account, line);

            for(i = 0; i < line.length(); i++)
            {
                if (i > 9)
                {
                    key += line[i];
                }
            }
            cout<<"Password: ";
            getline(cin, userInput);

            if (userInput == key)
            {
                found = true;

                account.close();
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

    clearScreen();

    return username;
}

int main()
{
    string name;
    int option;
    bool correctInput;

    name = logIn();
    do
    {
        do
        {
            cout<<PROGRAMTITLE<<endl<<endl;
            cout<<"Welcome, "<<name<<"!\n\n";
            cout<<"1.) Supply Check \n2.) Inventory \n3.) Sales \n4.) Record \n5.) Exit \n\n";

            cout<<"Select an option above (1/2/3/4/5): ";
            getline(cin, userInput);

            correctInput = isDigit(userInput);

            if (!correctInput)
            {
                showStatus("INVALID INPUT! Please enter numbers only.");
            }
        }while (!correctInput);

        option = stoi(userInput);

        clearScreen();

        switch (option)
        {
            case 1:
                checkSupply();

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

    return EXIT_SUCCESS;
}