/******************************************************************************

Prajit Alexander
Pxa220044

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const string database = "freeplay.dat";

struct gameDat//Structure that holds all the variables for the game database
{
    string name;
    int highScore;
    string initials;
    int plays;
    double revenue;
    gameDat* next = nullptr;
};
//Function prototypes
void createLinkedList(gameDat *&head, string nodeLine);
void addRecord(gameDat *&head, string nodeLine);
void searchRecord(gameDat *&head, string nodeLine);
void editRecord(gameDat *&head, string nodeLine);
gameDat* deleteRecord(gameDat *&head, string nodeLine);
gameDat *swapNodes(gameDat *ptr1, gameDat *ptr2);
void sortRecord(gameDat **head, string nodeLine);
void printList(gameDat *traversePtr);
void printToConsole(gameDat* traversePtr);


int main()
{
    string temp;  //variable for database filename
    string batch; //variable for batch filename

    cout << "Enter Database Name: ";
    cin >> temp;

    
    string line;

    gameDat* head = nullptr;//Creates a head pointer for the starting point
    cout << "Enter a batch name: ";//Allows the user to enter the name of the batch file
    cin >> batch;
    cout << endl;

    fstream batchFile(batch);//Opens the batch file
    fstream databaseFile(temp);//Opens the database file
    if (databaseFile)//Checks if the file opened properly
    {
        while (getline(databaseFile, line))
        {
            createLinkedList(head, line);//Takes info in file and places them into linked list
        }
    }
    
    databaseFile.close();
    
    if (batchFile)//Checks if batchfile opened
    {
        while (getline(batchFile, line))//Reads each line a a time
        {
            if (line[0] == '1')
            {
                addRecord(head, line);//Creates and adds the record into the database file
                cout << endl;
            }
            else if (line[0] == '2')//Searched the records in the database file
            {
                searchRecord(head, line);
                cout << endl;
            }
            else if (line[0] == '3')//Edits a record in the database file
            {
                editRecord(head, line);
                cout << endl;
            }
            else if (line[0] == '4')//Deletes a record from the database file
            {
                gameDat* deleted = deleteRecord(head, line);
                delete deleted;
                cout << endl;
            }
            else if (line[0] == '5')//Sorts the records by either name or amount of plays
            {
                sortRecord(&head, line);
                printToConsole(head);//Prints out to console
                cout << endl;
            }
            else
            {
                cout << "Command does not exist\n\n";//If the command is not on the list
            }
        }
    }
    batchFile.close();
    ofstream newDatFile(database);
    newDatFile.close();
    if (head != nullptr)//Checks to see if the list is empty
    {
        printList(head);
    }
    head = nullptr;
    delete head;//Deletes the head pointer
    return 0;
}

void createLinkedList(gameDat *&head, string nodeLine)
{
    gameDat* datEntry = new gameDat;
    gameDat* traversePtr = head;
    //Parses out each line in the database file
    datEntry->name = nodeLine.substr(0, nodeLine.find(','));
    nodeLine = nodeLine.substr(nodeLine.find(',') + 2);
    
    datEntry->highScore = stoi(nodeLine.substr(0, nodeLine.find(',')));
    nodeLine = nodeLine.substr(nodeLine.find(',') + 2);
    
    datEntry->initials = nodeLine.substr(0, nodeLine.find(','));
    nodeLine = nodeLine.substr(nodeLine.find(',') + 2);
    
    datEntry->plays = stoi(nodeLine.substr(0, nodeLine.find(',')));
    nodeLine = nodeLine.substr(nodeLine.find(',') + 3);
    
    datEntry->revenue = stod(nodeLine);
    
    if (head == nullptr)//If the file is empty
    {
        head = datEntry;
    }
    else//File is not empty
    {
        while (traversePtr->next != nullptr)
        {
            traversePtr = traversePtr->next;
        }
        traversePtr->next = datEntry;
    }
    //Deletes the pointers
    datEntry = nullptr;
    traversePtr = nullptr;
    delete datEntry;
    delete traversePtr;
}

void addRecord(gameDat *&head, string nodeLine)
{
    gameDat* newEntry = new gameDat;
    gameDat* traversePtr = head;
    //Parses through the line from the batch file
    nodeLine = nodeLine.substr(3, nodeLine.length() - 1);
    newEntry->name = nodeLine.substr(0, nodeLine.find('"'));
    
    nodeLine = nodeLine.substr(nodeLine.find('"') + 2, nodeLine.length() - 1);;
    newEntry->highScore = stoi(nodeLine.substr(0, nodeLine.find(" ")));
    
    nodeLine = nodeLine.substr(nodeLine.find(" ") + 1, nodeLine.length() - 1);
    newEntry->initials = nodeLine.substr(0, nodeLine.find(" "));
    
    nodeLine = nodeLine.substr(nodeLine.find(" ") + 1, nodeLine.length() - 1);
    newEntry->plays = stoi(nodeLine.substr(0, nodeLine.find(" ")));
    
    nodeLine = nodeLine.substr(nodeLine.find(" ") + 2);
    newEntry->revenue = stod(nodeLine);
    
    if (head == nullptr)//If first entry
    {
        head = newEntry;
    }
    else//If second or later entry
    {
        while (traversePtr->next != nullptr)
        {
            traversePtr = traversePtr->next;
        }
        traversePtr->next = newEntry;
    }
    //Prints out the results
    cout << "RECORD ADDED" << endl
    << "Name: " << newEntry->name << endl
    << "High Score: " << newEntry->highScore << endl
    << "Initials: " << newEntry->initials << endl
    << "Plays: " << newEntry->plays << endl
    << "Revenue: $" << fixed << setprecision(2) << newEntry->revenue << endl;
    //Deletes the pointers
    newEntry = nullptr;
    traversePtr = nullptr;
    delete newEntry;
    delete traversePtr;
}

void searchRecord(gameDat *&head, string nodeLine)
{
    nodeLine = nodeLine.substr(2);//Makes sure the search term is all thats left in the line
    if (head == nullptr)//If the list is empty
    {
        cout << nodeLine << " NOT FOUND" << endl;
        return;
    }
    bool recFound = false;
    gameDat* traversePtr = head;
    
    while (traversePtr)
    {
        //Looks through the names in each node and checks if they match search term
        if ((traversePtr->name).find(nodeLine) <= (traversePtr->name).length())
        {
            cout << traversePtr->name << " FOUND" << endl
            << "High Score: " << traversePtr->highScore << endl
            << "Initials: " << traversePtr->initials << endl
            << "Plays: " << traversePtr->plays << endl
            << "Revenue: $" << setprecision(2) <<  traversePtr->revenue << endl;
            recFound = true;
        }
        traversePtr = traversePtr->next;
    }
    if (recFound == false)//If the search term was not found in the list
    {
        cout << nodeLine << " NOT FOUND" << endl;
    }
    traversePtr = nullptr;
    delete traversePtr;//Deletes the pointer
}

void editRecord(gameDat *&head, string nodeLine)
{
    gameDat* traversePtr = head;
    nodeLine = nodeLine.substr(3);//Parses to the needed command
    string checkName = nodeLine.substr(0, nodeLine.find('"'));//Checks to see which name
    nodeLine = nodeLine.substr(nodeLine.find('"') + 2);//Parses to the final command number
    string fieldNum = nodeLine.substr(0, 1);//Attaches field number to variable to check
    
    while (traversePtr)//As long as end of list has not been reached
    {
        if ((traversePtr->name) == checkName)//Checks if the name in the list is same as in batchfile
        {
            cout << traversePtr->name << " UPDATED" << endl;
            if (fieldNum == "1")//Checks if high score is to be updated
            {
                traversePtr->highScore = stoi(nodeLine.substr(2));
                cout << "UPDATE TO high score - VALUE " << traversePtr->highScore << endl;
            }
            else if (fieldNum == "2")//Checks if initials is to be updated
            {
                traversePtr->initials = nodeLine.substr(2);
                cout << "UPDATE TO initials - VALUE " << traversePtr->initials << endl;
            }
            else if (fieldNum == "3")//Checks if plays and revenue is to be updated;
            {
                traversePtr->plays = stoi(nodeLine.substr(2));
                traversePtr->revenue = (traversePtr->plays) / 4.00;
                cout << "UPDATE TO plays - VALUE " << traversePtr->plays << endl;
            }
            //Prints out the results onto the console
            cout << "Name: " << traversePtr->name << endl;
            cout << "High Score: " << traversePtr->highScore << endl;
            cout << "Initials: " << traversePtr->initials << endl;
            cout << "Plays: " << traversePtr->plays << endl;
            cout << "Revenue: $" << fixed << setprecision(2) << traversePtr->revenue << endl;
            break;
        }
        traversePtr = traversePtr->next;
    }
    traversePtr = nullptr;
    delete traversePtr;//Deletes the normal pointer
}

void printList(gameDat *traversePtr)
{
    ofstream databaseFile(database, ios::app);
    if (traversePtr->next == nullptr)//Prints out to file if there is only one node
    {
        databaseFile << traversePtr->name << ", " << traversePtr->highScore << ", "
        << traversePtr->initials << ", " << traversePtr->plays << ", $" << fixed << setprecision(2)
        << traversePtr->revenue << endl;
        databaseFile.close();
    }
    else//If there is more than one node
    {
        databaseFile << traversePtr->name << ", " << traversePtr->highScore << ", "
        << traversePtr->initials << ", " << traversePtr->plays << ", $" << fixed << setprecision(2)
        << traversePtr->revenue << endl;
        databaseFile.close();
        printList(traversePtr->next);
    }
}

void printToConsole(gameDat *traversePtr)
{
    if (traversePtr->next == nullptr)//Prints out there is only one node
    {
        cout << traversePtr->name << ", " << traversePtr->highScore << ", "
        << traversePtr->initials << ", " << traversePtr->plays << ", $" << fixed << setprecision(2)
        << traversePtr->revenue << endl;
    }
    else//If there is more than one node
    {
        cout << traversePtr->name << ", " << traversePtr->highScore << ", "
        << traversePtr->initials << ", " << traversePtr->plays << ", $" << fixed << setprecision(2)
        << traversePtr->revenue << endl;
        printToConsole(traversePtr->next);
    }
}

gameDat* deleteRecord(gameDat *&head, string nodeLine)
{
    gameDat *traversePtr = head;
    nodeLine = nodeLine.substr(2);//Parses so the delete term is all thats left
    gameDat *hold = nullptr;
    bool isFound = false;
    if ((head->name) == nodeLine)//If the delete term is found in the first node
    {
        isFound = true;
        hold = head;
        head = head->next;
        hold->next = nullptr;
    }
    else//Delete term is found in the second or later nodes
    {
        while (traversePtr->next)
        {
            if (((traversePtr->next)->name) == nodeLine)
            {
                isFound = true;
                hold = traversePtr->next;
                traversePtr->next = hold->next;
                hold->next = nullptr;
                break;
            }
            traversePtr = traversePtr->next;
        }
    }
    if (isFound == true)//Prints out the results only if a delete term was found
    {
        cout << "RECORD DELETED" << endl;
        cout << "Name: " << hold->name << endl;
        cout << "High Score: " << hold->highScore << endl;
        cout << "Initials: " << hold->initials << endl;
        cout << "Plays: " << hold->plays << endl;
        cout << "Revenue: $" << hold->revenue << endl;
    }
    else//If a delete term was not found
    {
        cout << "RECORD NOT FOUND" << endl;
    }
    traversePtr = nullptr;
    delete traversePtr;//Deletes the pointer
    return hold;//Returns the node to be deleted
}

gameDat *swapNodes(gameDat *ptr1, gameDat *ptr2)
{
    gameDat* tempPtr = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tempPtr;
    tempPtr = nullptr;
    delete tempPtr;//Deletes the pointer
    return ptr2;//Returns the node
}

void sortRecord(gameDat **head, string nodeLine)
{
    gameDat **traversePtr;//To help with the sorting
    gameDat *counterPtr = *head;
    gameDat *ptr1;//Node for the greater name or plays
    gameDat *ptr2;//Node for the lesser name or plays
    int linkedListLength = 0;
    int a, b;
    
    nodeLine = nodeLine.substr(2);
    while (counterPtr)//Sifts through linked list to see size of list
    {
        linkedListLength++;
        counterPtr = counterPtr->next;
    }
    if (nodeLine == "name")//If the records need to be sorted by name
    {
        cout << "RECORDS SORTED BY name" << endl;
        for (a = 0; a < linkedListLength; a++)//Bubble sorts through the linked list
        {
            traversePtr = head;
            for (b = 0; b < linkedListLength - a - 1; b++)
            {
                ptr1 = *traversePtr;
                ptr2 = ptr1->next;
                if (ptr1->name > ptr2->name)
                {
                    *traversePtr = swapNodes(ptr1, ptr2);
                }
                traversePtr = &(*traversePtr)->next;
            }
        }
    }
    else if (nodeLine == "plays")//If the records need to be sorted by name
    {
        cout << "RECORDS SORTED BY plays" << endl;
        for (a = 0; a < linkedListLength; a++)//Bubble sorts through the linked list
        {
            traversePtr = head;
            for (b = 0; b < linkedListLength - a - 1; b++)
            {
                ptr1 = *traversePtr;
                ptr2 = ptr1->next;
                if (ptr1->plays > ptr2->plays)
                {
                    *traversePtr = swapNodes(ptr1, ptr2);
                }
                traversePtr = &(*traversePtr)->next;
            }
        }  
    }
    //Deletes the pointers
    traversePtr = nullptr;
    counterPtr = nullptr;
    ptr1 = nullptr;
    ptr2 = nullptr;
    delete traversePtr;
    delete counterPtr;
    delete ptr1;
    delete ptr2;
}
