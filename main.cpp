/* Name: Odin Lindal
 * Date: 4/10/24
 * CS132
 * Programming Challenge #2
 *
 * This is the primary initial file for
 * CS 132 Assignment #2.  The purpose of this file
 * is to create a simplistic encryption tool to store and
 * reload user access codes.   In doing so
 * the user will use stings and string manipulation.
 *
 * The purpose of this program is to let a user save a encrypted password to a file 
 * name "masterFile.txt", and chcek codes against it to see if they are added to the file already.
 * The encryption consists of converting all the characters in the user inputted string into
 * morse code. 
 * Input validation checks that the code contains 8 letters, 4 numbers, and 1 special character.
 *
 * version 4.3 - Minor tweaks.
 * version 4.2 - Bug Fix.
 * version 4.1 - Modified for new Version of assignment.  Changed from password to entry code.
 * version 4.0 - Modified for new version of assignment.
 * version 3.1 - Fixed the cin error
 * version 3.0 - updated to new assignment.
 * version 2.0 - updated to new assignment.
*/

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;


void addToFile(string fname);
void checkFile(string fname);
string charToMorse(char);
void makeTrim(string&);


 int main()
 {
     int option;

     cout << "***************************************************************" << endl;
     cout << "Hello and welcome to the CS132 Ultra Secure Code Checker       " << endl;
     cout << "***************************************************************" << endl;

     while (true)
     {
        const string fileName = "masterFile.txt";
        string input; //initialize string for user input
        do
        {
            //user menu
            cout << "Would you like to test an entry code in the list, or add an entry code?" << endl;
            cout << "  1 : for test a code"<< endl;
            cout << "  2 : for add a code" << endl;
            cout << "  3 : to quit" << endl;
            cout << "  >>> ";

            getline(cin,input); //capture user input, menu choice
            option = stoi("0"+input);
        } while (option < 1 || option > 3); //keep looping if user enters options outside valid choices


        if (option == 1) //menu choice 1
        {
            checkFile(fileName); //call the function to check if a code exists in the file
        }
        else if (option == 2) //menu choice 2
        {
            addToFile(fileName); //call function to add a code to the file
        }
        else if (option == 3) //menu choice 3, to exit the program
        {
            cout << "Thank you, have a good day." << endl;
            return 0;
        }
        else
        {
         // This is an error state, this should never happen.
         cerr << "ERROR invalid option" << endl;
         return 99;

        }

     } // End of the while(true);

    // The program did not leave correctly.
    cerr << "ERROR illegal loop exit." << endl;
    return 100;

 }

void addToFile(string fname)
{
    ofstream outFile; //create output file object
    outFile.open(fname, ios_base::app); //start at the next empty line
    //initialize temporary variables for the strings
    string passString;
    string tempString;
    //ask the user to input the code they want to add to the file
    cout << "Please enter the code you wish to add: ";
    getline(cin, passString); //capture the entire line
    
    //initialize counter variables
    int letterCount = 0;
    int numCount = 0;
    //loop through every character in the string the user inputted
    for(char ch : passString)
    {
        if(isalpha(ch))
            letterCount++; //increase the count of letters by one if alphabetical character is detected
        else if(isdigit(ch))
            numCount++; //increase the count of numbers by one if number is detected
    }
    
    //validate the code inputted
    if(passString.length() >= 15) //check the length of the string to make sure it is 15 characters or longer
    {
        //check if the string contains one of the required special characters
        if(passString.find("!") >= 1 || passString.find(".") >= 1 || passString.find(" ") >= 1 || passString.find("?") >= 1)
        {
            if(letterCount >= 8) //check that there are at least 8 letters
            {
                if(numCount >= 4) //check that there are at least 4 numbers
                {
                    cout << "The code is valid!" << endl; //let the user know the code is valid
                    //loop through the string
                    for(int i = 0; i < passString.length(); i++)
                    {
                        //pass every character in the string to the charToMorse function
                        //and add it to the temporary string
                        tempString.append(charToMorse(passString[i]));
                        tempString.append(" "); //add a space after every original character
                        if(passString[i] == ' ') //if there is a space, add a / and a space
                        {
                            tempString.append("/"); //add /
                            tempString.append(" "); //add space
                        }
                    }
                    //cout << tempString << endl; //debug
                    outFile << tempString << endl; //write the morse string to the output file
                    //let the user know that the code has saved to the file
                    cout << "Code saved to file successfully!" << endl;
                }
            }
        }
    }
    else
        //let the user know if the code is not valid
        cout << "The code is not valid. Try again" << endl;
    
    outFile.close(); //close the output file
}

void checkFile(string fname)
{
    ifstream inFile; //create an input file object
    inFile.open(fname); //open the input file with our filename
    if(!inFile.is_open()) //check if the file opens correctly
        cout << "File not found! Add the textfile to your directory and try again." << endl;
    else{ //if file is opened correctly, continue
    //initialize temporary strings
    string tempString = "";
    string passString;
    string fileString = "";
    int count = 0; //counter variable
    
    //ask the user to input the code they want to test
    cout << "Please enter the code you want to test: ";
    getline(cin, passString); //capture the entire line
    
    //loop through the inputted code and convert to morse, as done in addToFile()
    for(int i = 0; i < passString.length(); i++)
    {
        tempString.append(charToMorse(passString[i]));
        tempString.append(" ");
        if(passString[i] == ' ')
        {
            tempString.append("/");
            tempString.append(" ");
        }
    }
    
    //loops while there are lines to read from file
    while(getline(inFile, fileString))
    {
        makeTrim(fileString); //trim extra whitespaces and newlines from string
        makeTrim(tempString); //trim extra whitespaces and newlines from string
        if(fileString == tempString) //check if the inputted string matches the line read from the file
        {
            count++; //increase the counter variable
            break; //if match is found, break the loop to avoid unnecessary time spent on checking
        }
    }
    
    //check if the counter variable if bigger than 0, the let user know that the code is valid
    if(count > 0)
        cout << "The code is valid!" << endl;
    //if the counter variable is not bigger than 0, no match has been found in the file, so the code is not valid
    else
        cout << "The code is not valid! Try again." << endl;
    
    inFile.close(); //close the input file
    }
}

string charToMorse(char x)
{
    x = toupper(x); //convert character to uppercase
    
    string temp; //initialize temporary string
    
    //check every character and convert to morse
    if(x == 'A') temp = "*~";
    else if(x == 'B') temp = "~***";
    else if(x == 'C') temp = "~*~*";
    else if(x == 'D') temp = "~**";
    else if(x == 'E') temp = "*";
    else if(x == 'F') temp = "**~*";
    else if(x == 'G') temp = "~~*";
    else if(x == 'H') temp = "****";
    else if(x == 'I') temp = "**";
    else if(x == 'J') temp = "*~~~";
    else if(x == 'K') temp = "~*~";
    else if(x == 'L') temp = "*~**";
    else if(x == 'M') temp = "~~";
    else if(x == 'N') temp = "~*";
    else if(x == 'O') temp = "~~~";
    else if(x == 'P') temp = "*~~*";
    else if(x == 'Q') temp = "~~*~";
    else if(x == 'R') temp = "*~*";
    else if(x == 'S') temp = "***";
    else if(x == 'T') temp = "~";
    else if(x == 'U') temp = "**~";
    else if(x == 'V') temp = "***~";
    else if(x == 'W') temp = "*~~";
    else if(x == 'X') temp = "~**~";
    else if(x == 'Y') temp = "~*~~";
    else if(x == 'Z') temp = "~~**";
    else if(x == '0') temp = "~~~~~";
    else if(x == '1') temp = "*~~~~";   
    else if(x == '2') temp = "**~~~";
    else if(x == '3') temp = "***~~";
    else if(x == '4') temp = "****~";
    else if(x == '5') temp = "*****";
    else if(x == '6') temp = "~****";
    else if(x == '7') temp = "~~***";
    else if(x == '8') temp = "~~~**";
    else if(x == '9') temp = "~~~~*";
    else if(x == '.') temp = "*~*~*~";
    else if(x == '?') temp = "**~~**";
    else if(x == '!') temp = "~*~*~~";
    else temp = ""; //if no match is found, return blank
    
    return temp; //return the morse conversion
}
//function copied from assignment instructions
void makeTrim(string &x)
{
    //trim extra space characters from passed string
    const char* ws = " \t\n\r\f\v"; //list of space characters
    x.erase(0, x.find_first_not_of(ws)); //prefixing spaces
    x.erase(x.find_last_not_of(ws)+1); //surfixing spaces
}

