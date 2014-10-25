// Header Files
# include <fstream>
# include <iostream>
# include "formatted_cmdline_io_v09.h"

using namespace std;

// Global Constants
const char DASH = '-', SPACE = ' ', END_LINE = '\n'; 
const int MAX_VALUE = 100, MAX_LETTERS = 26, FIRST_LETTER = 0, MAX_NAME = 25, MAX_NUM = 35, MAX_GRADE = 10;
const string BLANK = "  ";


// Function Prototypes

int acquireGradesAndSize(int studentNumArr[], double gradeArr[], string nameArr[]);
/*
name: acquireGrades 
process: opens file with data, loads data into arrays, closes file
function input/parameters: arrays for student info (int, double, string)
function output/parameters: none
function output/returned: int size
device input: file input
device output/monitor: none
dependencies: fstream
*/

char getUserChoice();
/*
name: displayMenu
process: displays the menu
function input/parameters: none
function output/parameters: none
function output/returned: none
device input: none
device output/monitor: displayed menu
dependencies: iostream I/O tools
*/

char toUpperCase( char lowerCase );
/*
name: toUpperCase
process: makes letter uppercase
function input/parameters: letter (char)
function output/parameters: none
function output/returned: uppercase letter (char)
device input: none
device output/monitor: none
dependencies: none
*/

int addStudent( string wholeName, int studentNum, double grade, int size, string nameArr[], int studentNumArr[], double gradeArr[] );
/*
name: addStudent
process: adds student info to array
function input/parameters: name (string), student number (int), grade (double), size (int)
function output/parameters: none
function output/returned: size (int)
device input: none
device output/monitor: none
dependencies: none
*/

void editStudent( string wholeName, int studentNum, double grade, int size, string nameArr[], int studentNumArr[], double gradeArr[] );
/*
name: editStudent
process: edits student info in array
function input/parameters: name (string), student number (int), grade (double), size (int)
function output/parameters: none
function output/returned: none
device input: none
device output/monitor: none
dependencies: none
*/

int removeStudent( int studentNum, double grade, int size, string nameArr[], int studentNumArr[], double gradeArr[] );
/*
name: removeStudent
process: removes student info in array
function input/parameters: name (string), student number (int), grade (double), size (int)
function output/parameters: none
function output/returned: size (int)
device input: none
device output/monitor: none
dependencies: none
*/

void displayStudent( char letter, int studentNumArr[], double gradeArr[], string nameArr[], int size );
/*
name: displayStudent
process: displays student list and info
function input/parameters: initial (char), student number array (int), grade array (int), name arrays (string)
function output/parameters: none
function output/returned: none
device input: none
device output/monitor: displayed data
dependencies: iostream I/O tools
*/

void saveNewFile( int studentNumArr[], double gradeArr[], string nameArr[], int size );
/*
name: saveNewFile
process: saves edited data to new file
function input/parameters: student number array (int), grade array (int), name arrays (string)
function output/parameters: none
function output/returned: none
device input: none
device output/monitor: outputted data file
dependencies: fstream
*/

void displayError( const string &message);
/*
name: displayError
process: displays error message
function input/parameters: error message text (string)
function output/parameters: none
function output/returned: none
device input: none
device output/monitor: displayed error message
dependencies: iostream I/O tools
*/

char askFinalize( const string &prompt );
/*
 name: askFinalize
 process: asks user of they want to finish data change
 function input/parameters: prompt (string)
 function output/parameters: none
 function output/returned: answer (char)
 device input: none
 device output/monitor: displayed prompt
 dependencies: iostream I/O tools
 */

// Main Function
int main()
{
    // initialize program/function
    int studentNum, studentNumArr[MAX_VALUE], index = 0, size;
    double grade, gradeArr[MAX_VALUE];
    string nameArr[MAX_VALUE], wholeName;
    char dummy, choice, choiceYN, initial;
    
    // aquire data from file
       // function: acquireGrades
    size = acquireGradesAndSize(studentNumArr, gradeArr, nameArr);
           
    // loop menu display and options until user want to quit
    do
    {
        // initialize variables
        index = 0;
        bool error;

        // get user's input
           // function: getUserChoice
        choice = getUserChoice();
    
        // clear screen
        system( "CLS" );
    
        // if user wants to add student
        if( choice == 'a'|| choice == 'A' || choice == '1' )
        {
            // set error flag
            error = false;
            
            // display add students module
               // function: iostream <<
            cout << endl << "Add Student Module" << endl;
            cout << "------------------" << endl << endl;
            
            // aquire user input
               // function: iostream >>
            cout << "Enter new student ID number     : ";
            cin >> studentNum;
            
            // loop to find if student number exists
            while( index < size )
            {
                // if student number exists aready
                if( studentNum == studentNumArr[ index ] )
                   {
                       // display error message
                       displayError( "Dupicate student ID found, Add Student Module aborted"); 
                       error = true;
                   }
                // increment index
                index++;
            }
            
            // if error is false
            if ( error == false )
            {
                // acquire the rest of user input
                   // function: iostream <<, >>
                cout << endl;
                cout << "Enter student name <last, first>: ";
                cin >> wholeName;
                cout << endl;
                cout << "Enter student grade             : ";
                cin >> grade;
                cout << endl << endl << endl;
                
                // ask user to finalize changes
                   // function: iostream <<, >>
                choiceYN = askFinalize("Complete student addition process <y/n>: ");

            
                // if yes 
                if( choiceYN == 'Y' || choiceYN == 'y' )
                {
                    // add student
                       // function: addStudent
                    addStudent( wholeName, studentNum, grade, size, nameArr, studentNumArr, gradeArr );
                }
            }
        }
    
        // if user wants to edit student info
            else if( choice == 'e'|| choice == 'E' || choice == '2' )
            {
                
                // reset index
                index = 0;
                
                // set error flag
                error = true;
                
                // display edit students module
                   // function: iostream <<
                cout << endl << "Edit Student Module" << endl;
                cout << "-------------------" << endl << endl;
                
                // acquire user input
                   // function: iostream <<, >>
                cout << "Enter edited student ID number      : ";
                cin >> studentNum;
                
                // loop until student number is found

                while ( index < size )
                {
                        
                    // if student number is found
                    if( studentNum == studentNumArr[ index ] )
                    {
                        // set corresponding values
                        wholeName = nameArr[ index ];
                        grade = gradeArr[ index ];
                        
                        // turn off error flag
                        error = false;
                    }
                       
                    // increment index
                    index++;
                        
                }
                
                // if error
                if( error == true )
                {
                    // display error message
                       // function: iostream <<
                    displayError( "Dupicate student ID found, Edit Student Module aborted" );
                }
                
                // otherwise, if no error
                else
                {
                    // acquire the rest of user input
                       // function: iostream <<, >>
                    cout << "Present student name                : " << wholeName << endl;
                    cout << "Enter new student name <last, first>: ";
                    cin >> wholeName;
                    cout << "Present student grade               : " << grade << endl;
                    cout << "Enter new student grade             : ";
                    cin >> grade;
                    cout << endl << endl;
                    
                    // ask user to finalize changes
                       // function: iostream <<, >>
                    choiceYN = askFinalize("Complete student editing process <y/n>: ");

                
                    // if yes
                    if( choiceYN == 'Y' || choiceYN == 'y' )
                    {
                        // edit student
                           // function: editStudent
                        editStudent( wholeName, studentNum, grade, size, nameArr, studentNumArr, gradeArr );

                    }
                }
    
            }
        // if user wants to remove student
            else if( choice == 'r'|| choice == 'R' || choice == '3' )
            {
                
                // reset index
                index = 0;
                
                // set error flag
                error = true;
                
                // display remove student module
                   // function: iostream <<
                cout << endl << "Remove Student Module" << endl;
                cout << "---------------------" << endl << endl;
                
                // acquire user input
                   // function: iostream <<, >>
                cout << "Enter remove student ID number      : ";
                cin >> studentNum;
                
                // loop until student number is found
                while ( index < size )
                {
                        
                    // if student number is found
                    if( studentNum == studentNumArr[ index ] )
                    {
                        // set corresponding values
                        wholeName = nameArr[ index ];
                        grade = gradeArr[ index ];
                            
                        // turn off error flag
                        error = false;
                    }
                    
                    // increment index
                    index++;
                }
                
                // if error
                if( error == true )
                {
                    // display error message
                       // function: iostream <<
                    displayError( "Student ID not found, Remove Student Module aborted" );
                }
                
                // otherwise, if no error
                else
                {
                    // acquire rest of user input
                       // function: iostream <<, >>
                    cout << "Present student name                : " << wholeName << endl;
                    cout << "Present student grade               : " << grade << endl << endl << endl;
                    
                    // ask user to finalize changes
                       // function: iostream <<, >>
                    choiceYN = askFinalize("Complete student removal process <y/n>: ");
                
                   // if yes
                   if( choiceYN == 'Y' || choiceYN == 'y' )
                   {
                       // remove student
                          // function: removeStudent
                       removeStudent( studentNum, grade, size, nameArr, studentNumArr, gradeArr );

                   }
                }
                
            }
        
        // if user wants to display students
        else if( choice == 'd'|| choice == 'D' || choice == '4' )
        {
            // display display students module
               // function: iostream <<
            cout << "Display Students Module" << endl;
            cout << "-----------------------" << endl << endl;
            
            // acquire user input
            cout << "Enter first letter of last name: ";
            cin >> initial;
            
            // display data
               // function: displayStudent
            displayStudent( initial, studentNumArr, gradeArr, nameArr, size );

        }
    
    // end loop when user wants to quit
       if ( choice == 'q' || choice == 'Q' || choice == '5')
       {
           // output new data to file
              // function: saveNewFile
           saveNewFile( studentNumArr, gradeArr, nameArr, size );
           
           // shut down program
           system( "PAUSE" );
        
           // return
           return 0;
       }
        
    // repeat loop until user wants to quit
    }
    while( choice != 'q' || choice != 'Q' || choice != '5');

}

// Supporting Function Implementations

int acquireGradesAndSize(int studentNumArr[], double gradeArr[], string nameArr[])
{
    // initialize function/variables
    ifstream fin;
    int studentNum, index = 0, size = 0;
    double grade;
    string name;
    char dummy;
    
    // clear/open file
    fin.clear();
    fin.open("studentsSmall.txt");
    
    // input data
    
    // loop while data is good
    while ( fin.good() )
    {
        // input data from file
        fin >> studentNum >> dummy >> grade >> dummy;
        getline( fin, name, END_LINE );
        
        // fill in arrays
        studentNumArr[ index ] = studentNum;
        gradeArr[ index ] = grade;
        nameArr[ index ] = name;
        
        // increment index and size
        index ++;
        size ++;
    }
    
    // close file
    fin.close();
    
    // return
    return size;
}

char getUserChoice()
{
    
    // initialize function/variables
    char choice;
    
    // display menu
       // function: iostream <<, >>
    cout << "Student Grade Menu" << endl;
    cout << "==================" << endl << endl;
    cout << "1. <A>dd Student with grade" << endl;
    cout << "2. <E>dit Student or grade" << endl;
    cout << "3. <R>emove Student and grade" << endl;
    cout << "4. <D>isplay Students with grade" << endl;
    cout << "5. <Q>uit Program" << endl << endl << endl;
    
    // aquire user input
       // function: iostream <<, >>
    cout << "    Enter Selection: ";
    cin >> choice;
    
    // return
    return choice;
}

char toUpperCase( char lowerCase )
{
    // initialize function/ variables
    int index = 0;
    string lowerCaseLetters = "abcdefghijklmnopqrstuvwxyz";
    string UpperCaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // loop to find letter
    while( index < MAX_LETTERS && lowerCase <= 'z' && lowerCase >= 'a' )
    {
        // if letter is found
        if( lowerCase == lowerCaseLetters.at( index ))
        {
            // return uppercase
            return UpperCaseLetters.at( index );
        }
        
        index++;
    }
    
    // if letter is already uppercase
    if( lowerCase <= 'Z' && lowerCase >= 'A')
    {
        // return letter
        return lowerCase;
    }
}

int addStudent(  string wholeName, int studentNum, double grade, int size, string nameArr[], int studentNumArr[], double gradeArr[] )
{
    char initial;
    int letter = 0, index = 0, topIndex, insertIndex;
    
    // set initial to uppercase
       // function: toUpperCase
    initial = toUpperCase( wholeName.at( FIRST_LETTER ));
    
    // loop through names
    while( index <  size )
    {

            // loop while letters are the same
            while( wholeName.at(letter) == nameArr[ index ].at( letter ))
            {
                
                // if letter is larger
                if( wholeName.at(letter) > nameArr[ index ].at( letter ) && wholeName.at(letter) < nameArr[ index + 1 ].at( letter ))
                {
                    size++;
                    topIndex = size - 1;
                    insertIndex = index + 1;
                    
                    // loop to move data up in arrays
                    while( topIndex > insertIndex )
                    {
                        nameArr[ topIndex ] = nameArr[ topIndex - 1 ];
                        studentNumArr[ topIndex ] = studentNumArr[ topIndex - 1 ];
                        gradeArr[ topIndex ] = gradeArr[ topIndex - 1 ];
                        topIndex--;
                    }
                    
                    // assign new data to array index location
                    nameArr[ insertIndex ] = wholeName;
                    gradeArr[ insertIndex ] = grade;
                    studentNumArr[ insertIndex ] = studentNum;
                    
                    // return
                    return size;
                    
                    
                }
                
                // increment letter
                letter++;
                
            }
        
        // increment index
        index++;    
        letter = 0;
    } 
}


void editStudent( string wholeName, int studentNum, double grade, int size, string nameArr[], int studentNumArr[], double gradeArr[] )

{
    // initialize function/variables
    int index = 0;
    
    // loop to find student number
    while ( index < size )
    {
        // if student number is found
        if ( studentNum == studentNumArr[index] )
        {
            // edit info
            nameArr[index] = wholeName;
            gradeArr[index] = grade;
        }
        
        // increment index
        index ++;
    }
}

int removeStudent( int studentNum, double grade, int size, string nameArr[], int studentNumArr[], double gradeArr[] )
{
    // initialize function/variables
    int index = 0;
    
    // loop to find student number
    while ( index < size )
    {
        // if student is found
        if( studentNum == studentNumArr[ index ])
        {
            // loop to move data down
            while( index < size - 1)
            {
                studentNumArr[ index ] = studentNumArr[ index + 1];
                nameArr[ index ] = nameArr[ index + 1];
                gradeArr[ index ] = gradeArr[ index + 1];
                
                // increment index
                index++;
            }
            
            // increment size
            size--;
            
            // return
            return size;
        }
        
        // increment index
        index++;
    }
}

void displayStudent( char letter, int studentNumArr[], double gradeArr[], string nameArr[], int size )
{
    // initialize function/variables
    int index = 0;
    double studentNumber;
    char initial, firstLetter;
    
    // set user letter to uppercase
    initial = toUpperCase( letter );
    
    // display titles
       // function: iostream <<
    cout << "     Name               Student ID     Grade" << endl;
    cout << "     ----               ----------     -----" << endl << endl;
    
    // loop though names
    while( index < size )
    {
        // set name initial to uppercase
        firstLetter = toUpperCase( nameArr[index].at(FIRST_LETTER));
        
        // if last name initial is found
        if( firstLetter == initial )
        {
            // print out info
               // function: printString, printInt, printDouble, printEndLines
            studentNumber = ( studentNumArr[ index ] / 1.0 );
            printString( nameArr[ index ], MAX_NAME, "LEFT");
            printDouble( studentNumber, 0, MAX_NUM, "CENTER");
            printDouble( gradeArr[ index ], 2, MAX_GRADE, "RIGHT");
            printEndLines(1);

        }
        
        // increment index
        index++;
    }
}

void saveNewFile( int studentNumArr[], double gradeArr[], string nameArr[], int size )
{
    // initialize function/variables
    ofstream fout;
    int index;
    
    // open file
       // function: .open
    fout.open("students_bkp.txt");
    
    // output data
    
       // loop until all data is outputted
       while( index < size )
       {
           // output data line
              // function: fstream <<
           fout << studentNumArr[index] << DASH << gradeArr[index] << DASH << nameArr[index] << endl;
           index++;
       }
    
    // close file
       // function: .close
    fout.close();
}

void displayError( const string &message)
{
    // initialize function/variables
    
    // display error message
       // function: iostream <<
    cout << endl << "ERROR: " << message << endl;
    
    // hold program
       // function: system/pause
    system( "PAUSE ");
}

char askFinalize( const string &prompt )
{
    // initialize function/variables
    char choiceYN;
    
    // display prompt
       // function: iosteam <<, >>
    cout << prompt;
    cin >> choiceYN;
}
