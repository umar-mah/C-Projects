/*****************************************
** File:    extra_credit.cpp
** Project: CMSC 202 Project 1, Spring 2023
** Author:  Muhammad Umar
** Date:    2/25/23
** Section: 25
** E-mail:  mumar2@umbc.edu
**
** This program creates a large map.
** Based on the map, a balloon will be hidden somewhere in the map.
** The user will then guess coordinates for where the balloon exists. If the user is not successful in guessing
** where the balloon is, the application will indicate which direction the balloon is (north, south, east, or west).
***********************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int rowsY = 20;
const int columnsX = 20;

// Function definitions
void MapAssignment(char map[][columnsX]);
void DisplayMap(char map[][columnsX]);
bool ResultOfChoice(int choice, char userMap[][columnsX], int balloonCoordinateX, int balloonCoordinateY, int oldBalloonCoordinateX, int oldBalloonCoordinateY);
int RandomCoordinateX();
int RandomCoordinateY();
int UserInputX();
int UserInputY();
bool DirectionToBalloon(int balloonX, int balloonY, int userX, int userY, int oldBalloonX, int oldBalloonY);
bool PlayAgain();
int ChoiceInput();
int RandomDirection();
int ChangeNorth(int balloonY);
int ChangeSouth(int balloonY);
int ChangeEast(int balloonX);
int ChangeWest(int balloonX);
bool BalloonMovementVerify(int balloonX, int balloonY, char map[][columnsX]);

int main()
{
    srand(time(NULL)); // Calling the function to generate random numbers
    int balloonCoordinateX;
    int balloonCoordinateY;
    int oldBalloonCoordinateX;
    int oldBalloonCoordinateY;
    int movingDirection;
    int choice;
    int times = 0;
    bool flag = true;
    bool status = false;
    bool correctBalloonPosition = false;
    char userMap[rowsY][columnsX];
    char gameMap[rowsY][columnsX];

    cout << "Welcome to the Surveillance Balloon Tracker"
         << "\n";
    cout << "You are searching for the surveillance balloon"
         << "\n";
    do
    {
        if (flag == true)
        {
            times = 0;
            MapAssignment(userMap);                                // Assigns $ sign to the maps.
            MapAssignment(gameMap);                                // Assigns $ sign to the maps.
            balloonCoordinateX = RandomCoordinateX();              // Generates a random X coordinate.
            balloonCoordinateY = RandomCoordinateY();              // Generates a random Y coordinate
            gameMap[balloonCoordinateY][balloonCoordinateX] = 'B'; // Assigns the 'B' character on the coordinates of the balloon in the map.
        }
        if (times >= 1)
        {                                               // Loop to change location of balloon
            oldBalloonCoordinateX = balloonCoordinateX; // Stores the previous X-Coordinate of the balloon
            oldBalloonCoordinateY = balloonCoordinateY; // Stores the previous Y-Coordinate of the balloon.
            do
            {
                movingDirection = RandomDirection(); // Generates random direction to go to.
                if (movingDirection == 1)
                {                                                            // 1 is towards north
                    balloonCoordinateY = ChangeNorth(oldBalloonCoordinateY); // Moves one unit up
                }
                else if (movingDirection == 2)
                {                                                            // 2 is towards south
                    balloonCoordinateY = ChangeSouth(oldBalloonCoordinateY); // Moves one unit down
                }
                else if (movingDirection == 3)
                {                                                           // 3 is towards east
                    balloonCoordinateX = ChangeEast(oldBalloonCoordinateX); // Moves one unit to the right
                }
                else if (movingDirection == 4)
                {                                                           // 4 is towards west
                    balloonCoordinateX = ChangeWest(oldBalloonCoordinateX); // Moves one unit to the left
                }
                correctBalloonPosition = BalloonMovementVerify(balloonCoordinateX, balloonCoordinateY, userMap); // Verifies whether the new balloon position clashes with previous user inputs
            } while (correctBalloonPosition == true);                                                            // Loops until the new balloon position is valid
        }
        cin.clear();
        choice = ChoiceInput(); // Gives the user choices to choose from.
        flag = ResultOfChoice(choice, userMap, balloonCoordinateX, balloonCoordinateY, oldBalloonCoordinateX, oldBalloonCoordinateY);
        if (choice == 2)
        {
            times++;
        }
        if (flag == true)
        {
            // Checks if the user found the balloon
            cout << "It took you " << times << " guesses to find the balloon"
                 << "\n";
            status = PlayAgain(); // Gives the user the choice to play again.
            cin.clear();
        }
    } while (choice != 3 && (status == false)); // Loops until the balloon is found or the user has chosen the exit option.
    cout << "Thank you for Using the Surveillance Balloon Tracker"
         << "\n";
    return 0;
}

//*****MapAssignment*****
/*
The 2D array is passed as the parameter.
This function should assign the $ sign on each element in the 2D array.
Nothing is returned.
*/

void MapAssignment(char map[][columnsX])
{
    for (int i = 0; i < rowsY; i++)
    // loops until the row limit.
    {
        for (int j = 0; j < columnsX; j++)
        // loops until it reaches the column limit.
        {
            map[i][j] = '$'; // assigns $ sign on the map
        }
    }
}

//*****DisplayMap*****
/*
The 2D array of the map is passed in the function.
This function displays the 2D array with its elements. It displays the map.
Nothing is returned
*/

void DisplayMap(char map[][columnsX])
{
    // Displays the map in the required format
    cout << "   ";
    // Outputs the numbers from 1 to the column limit in the columns
    for (int numbering = 0; numbering < columnsX; numbering++)
    {
        if (numbering <= 8)
        {
            cout << numbering << "  ";
        }
        else
        {
            cout << numbering << " ";
        }
    }
    cout << " "
         << "\n";

    // Outputs the rest of the map with the numbers from 1 to row limit in the rows.
    for (int i = 0; i < rowsY; i++)
    {
        if (i >= 10)
        {
            cout << (i) << " ";
        }
        else
        {
            cout << (i) << "  ";
        }
        for (int j = 0; j < columnsX; j++)
        {
            cout << map[i][j] << "  ";
        }
        cout << ""
             << "\n";
    }
}

//*****ResultOfChoice*****
/*
PreCondition: The user input of the choice, the map, and the new and old balloon coordinates are passed into
function.
This function compares the choice selected by the user. It executes the instructions
after one of the choices is selected.
Post Condition: A status flag is returned to tell if the user selected to exit the program or the user has found the balloon.
*/

bool ResultOfChoice(int choice, char userMap[][columnsX], int balloonCoordinateX, int balloonCoordinateY, int oldBalloonCoordinateX, int oldBalloonCoordinateY)
{
    bool flag = false;
    int userCoordinateX;
    int userCoordinateY;

    switch (choice)
    {
    case 1:
        // First choice is to display the map.
        DisplayMap(userMap);
        break;
    case 2:
        // Asks the user to input their guess
        userCoordinateX = UserInputX();                  // Asks for the X coordinate
        userCoordinateY = UserInputY();                  // Asks for the Y coordinate
        userMap[userCoordinateY][userCoordinateX] = 'G'; // Assigns G to show that the user has selected this option.
        flag = DirectionToBalloon(balloonCoordinateX, balloonCoordinateY, userCoordinateX, userCoordinateY, oldBalloonCoordinateX, oldBalloonCoordinateY);
        // Checks if the balloon is found and guides the user if it is not found.
        break;
    case 3: // Exit case
        break;
    default:
        // If 1,2,3 are not chosen
        cout << "Please choose again "
             << "\n";
        break;
    }
    return flag; // Shows the status of whether the balloon is found or not
}

//*****RandomCoordinateX*****
/*
Nothing is passed
This function generates a random X coordinate within the range defined.
The X coordinate is returned.
*/

int RandomCoordinateX()
{
    int randomX;

    randomX = rand() % (columnsX + 1); // Generates the random X coordinate.
    return randomX;
}

//*****RandomCoordinateY*****
/*
Nothing is passed
This function generates a random Y coordinate within the range defined.
The Y coordinate is returned.
*/

int RandomCoordinateY()
{
    int randomY;
    randomY = rand() % (rowsY + 1); // Generates the random Y coordinate.
    return randomY;
}

//*****UserInputX*****
/*
Nothing is passed
This function allows the user to enter the X coordinate they want to guess.
The X coordinate is returned.
*/

int UserInputX()
{
    int xCoordinate;
    cout << "Where would you like to look for the balloon?"
         << "\n";
    cout << "Enter the X coordinate (0 - " << columnsX - 1 << "): "
         << "\n";
    do
    {
        cin >> xCoordinate; // The user enters their X coordinate
        while (cin.fail())  // Checks for data type errors
        {
            cout << "Enter the X coordinate (0 - " << columnsX - 1 << "): "
                 << "\n";
            cin.clear();           // Clears the input buffer if data type is wrong
            cin.ignore(256, '\n'); // Ignores the input
            cin >> xCoordinate;
        }
        if (xCoordinate < 0 || xCoordinate > columnsX - 1) // Checks if the user has entered the coordinates within the range
        {
            cout << "Please choose again" // Displays error messages
                 << "\n";
        }
    } while (xCoordinate < 0 || xCoordinate > columnsX - 1); // Loops until the X coordinate is correctly entered
    return xCoordinate;
}

//*****UserInputY*****
/*
Nothing is passed
This function allows the user to enter the Y coordinate they want to guess.
The Y coordinate is returned.
*/

int UserInputY()
{
    int yCoordinate;
    cout << "Enter the Y coordinate (0 - " << rowsY - 1 << "): "
         << "\n";
    do
    {
        cin >> yCoordinate; // The user enters their Y coordinate.
        while (cin.fail())  // Checks for data type errors
        {
            cout << "Enter the Y coordinate (0 - " << rowsY - 1 << "): "
                 << "\n";
            cin.clear();           // Clears the input buffer if data type is wrong
            cin.ignore(256, '\n'); // Ignores the input
            cin >> yCoordinate;
        }
        if (yCoordinate < 0 || yCoordinate > rowsY - 1) // Checks if the user has entered the coordinates within the range
        {
            cout << "Please choose again" // Displays error messages
                 << "\n";
        }
    } while (yCoordinate < 0 || yCoordinate > rowsY - 1); // Loops until the Y coordinate is correctly entered
    return yCoordinate;
}

//*****DirectionToBalloon*****
/*
The balloon and user entered coordinates are passed into the function.
This function determines whether the user entered the balloon's coordinates. If not, then
it displays a message to guide the user to the balloon.
A status flag is returned to tell whether the user found the balloon.
*/

bool DirectionToBalloon(int balloonX, int balloonY, int userX, int userY, int oldBalloonX, int oldBalloonY)

{
    // Checks if the balloon coordinates match with the user input
    bool flag = false;
    if ((balloonY == userY) && (balloonX == userX)) // Condition to check if balloon coordinates match
    {
        // Displays congratulation message if found.
        cout << "You found the balloon! "
             << "\n";
        flag = true;
        // Changes the status to true to indicate that the balloon is found.
    }
    else if (balloonY > userY) // Condition to check if Balloon's Y coordinate is greater.
    {
        cout << "You didn't find the balloon"
             << "\n";
        cout << "The balloon is south of your guess."
             << "\n";
        // Guides the user that the ballon is towards the south
    }
    else if (balloonY < userY) // Condition to check if Balloon's Y coordinate is smaller.
    {
        cout << "You didn't find the balloon"
             << "\n";
        cout << "The balloon is north of your guess."
             << "\n";
        // Guides the user that the ballon is towards the north
    }
    else if (balloonX > userX) // Condition to check if Balloon's X coordinate is greater.
    {
        cout << "You didn't find the balloon"
             << "\n";
        cout << "The balloon is east of your guess."
             << "\n";
        // Guides the user that the ballon is towards the east
    }
    else if (balloonX < userX) // Condition to check if Balloon's X coordinate is smaller.
    {
        cout << "You didn't find the balloon"
             << "\n";
        cout << "The balloon is west of your guess."
             << "\n";
        // Guides the user that the ballon is towards the west
    }
    if ((balloonX == oldBalloonX) && (balloonY == oldBalloonY))
    {
    }
    else if (flag == true)
    {
    }
    else
    {
        cout << "The balloon moves in the wind."
             << "\n";
    }

    return flag;
}

//*****PlayAgain*****
/*
Nothing is passed into the function.
This function allows the user to choose whether they can play again or not.
A status flag is returned to tell whether the user entered yes or no.
*/

bool PlayAgain()
{
    char play;
    bool status = false;
    do
    {
        cout << "Would you like to play again? (y or n)"
             << "\n";
        cin >> play;                      // Allows the user to play again after the user has found the balloon.
    } while (play != 'y' && play != 'n'); // Accepts only y or n as the input.
    if (play == 'y')
    {
        status = false; // Shows that the user wants to play again
    }
    else if (play == 'n')
    {
        status = true; // Shows that the user does not want to play
    }
    else
    {
        cout << "Wrong choice"
             << "\n";
        // Displays error message if y or n is not chosen
    }
    return status;
}

//*****ChoiceInput*****
/*
Nothing is passed into the function.
This function displays and lets the user enter their choice.
A variable containing the choice is returned.
*/

int ChoiceInput()
{
    int choice;
    cout << "What would you like to do?: "
         << "\n";
    cout << "1. Display Map "
         << "\n";
    cout << "2. Guess Location of Balloon "
         << "\n";
    cout << "3. Exit "
         << "\n";
    cin >> choice;     // Gives the user choices to perform in the program.
    while (cin.fail()) // Checks for data type errors.
    {
        cout << "What would you like to do?: "
             << "\n";
        cout << "1. Display Map "
             << "\n";
        cout << "2. Guess Location of Balloon "
             << "\n";
        cout << "3. Exit "
             << "\n";
        cin.clear();           // Clears the input buffer if data type is wrong
        cin.ignore(256, '\n'); // Ignores the input
        cin >> choice;
    }
    return choice;
}

//*****RandomDirection*****
/*
PreCondition: Nothing is passed
This function generates a random direction for the balloon to move.
PostCondition: The function returns the random decision to move.
*/

int RandomDirection()
{
    int randomDecision;
    randomDecision = rand() % (4 + 1); // Generates the random X coordinate.
    return randomDecision;
}

//*****ChangeNorth*****
/*
PreCondition: The Y-coordinate of the previous balloon location.
This function moves the balloon one place to the north.
PostCondition: The function returns the new location of the Y-Coordinate.
*/

int ChangeNorth(int balloonY)
{
    if ((balloonY - 1) < 0)
    { // Checks if the balloon is going off the map
        return balloonY;
    }
    balloonY = balloonY - 1; // Moves one place up
    return balloonY;
}

//*****ChangeSouth*****
/*
PreCondition: The Y-coordinate of the previous balloon location.
This function moves the balloon one place to the south.
PostCondition: The function returns the new location of the Y-Coordinate.
*/

int ChangeSouth(int balloonY)
{
    if ((balloonY + 1) > rowsY)
    { // Checks if the balloon is going off the map
        return balloonY;
    }
    balloonY = balloonY + 1; // Moves one place down
    return balloonY;
}

//*****ChangeEast*****
/*
PreCondition: The X-coordinate of the previous balloon location.
This function moves the balloon one place to the east.
PostCondition: The function returns the new location of the X-Coordinate.
*/

int ChangeEast(int balloonX)
{
    if ((balloonX + 1) > columnsX)
    { // Checks if the balloon is going off the map
        return balloonX;
    }
    balloonX = balloonX + 1; // Moves one place right
    return balloonX;
}

//*****ChangeWest*****
/*
PreCondition: The X-coordinate of the previous balloon location.
This function moves the balloon one place to the west.
PostCondition: The function returns the new location of the X-Coordinate.
*/

int ChangeWest(int balloonX)
{ // Checks if the balloon is going off the map
    if ((balloonX - 1) < 0)
    {
        return balloonX;
    }
    balloonX = balloonX - 1; // Moves one place right
    return balloonX;
}

//*****BalloonMovementVerify*****
/*
PreCondition:
The X-coordinate of the balloon location.
The Y-coordinate of the balloon location.
The user map is passed.
This function verifies whether the new balloon location clashes with another user input.
PostCondition: The function returns a flag status to show whether it collides or not.
*/

bool BalloonMovementVerify(int balloonX, int balloonY, char map[][columnsX])
{
    bool flag = false;
    if (map[balloonY][balloonX] == 'G')
    { // Checks for the clash in location.
        flag = true;
    }
    return flag;
}