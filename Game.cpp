#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Ingredient.h"
#include "Shop.h"

using namespace std;

// Name - Game() Default Constructor
// Desc - Does nothing explicitly
// Preconditions - None
// Postconditions - None
Game::Game()
{
}
// Default Constructor
//  Name - LoadIngredients
//  Desc - Loads each ingredient into m_ingredients from file.
//         Ingredient names can have spaces (check proj doc for delimiter help)
//  Preconditions - Requires file with valid ingredient data
//  Postconditions - m_ingredient is populated with ingredient structs
void Game::LoadIngredients()
{
  // Variable declaration
  char seperator = ',';
  int counter = 0;
  int occurences = 0;
  int quantity = 0;
  int i = 0;
  string temp;
  string name;
  string type;
  string ingredient1;
  string ingredient2;
  char fileData[100];
  // Opening the file
  ifstream myfile(PROJ2_DATA);
  if (myfile.is_open())
  {
    while (myfile.getline(fileData, 100)) // Fetches data from the file
    {
      i = 0;
      temp = "";
      counter = 0;
      while (fileData[i] != '\0') // Loops until the end of the line in the file
      {
        if (fileData[i] != seperator) // Checks for commas
        {
          temp += fileData[i]; // Adds the character after and before the comma into a single string
        }
        else
        {
          if (counter == 0) // Seperates the name
          {
            name = temp;
            ++counter;
          }
          else if (counter == 1) // Seperates the type
          {
            type = temp;
            ++counter;
          }
          else if (counter == 2) // Seperates the ingredient 1
          {
            ingredient1 = temp;
            ++counter;
          }
          temp = ""; // Resets the temperory string after a comma appears
        }
        i = i + 1;
        if ((counter == 3) && (fileData[i] == '\0'))
        { // Seperates ingredient 2
          ingredient2 = temp;
        }
        cin.clear();
      }
      m_ingredients[occurences] = {name, type, ingredient1, ingredient2, quantity}; // Adds one of the ingredients into the array
      occurences = occurences + 1;                                                  // Increments the counter
    }
  }
  myfile.close();
}
// Name - StartGame()
// Desc - Calls GameTitle then loads the file by calling LoadIngredients
//        Manages the game itself continually calling the main menu until the main menu
//        returns 5 (quit)
// Preconditions - Player is placed in game
// Postconditions - Continually checks to see if player has entered 5
void Game::StartGame()
{
  string name;
  int choice = -1;
  char rank;
  GameTitle();                           // Prints the Game title
  LoadIngredients();                     // Loads all the ingredients into an array
  m_myShop.AddIngredient(m_ingredients); // Adds all the ingredients into the shop
  cout << "32 ingredients loaded"
       << "\n";
  cout << "What is the name of your Shop?"
       << "\n";
  getline(cin, name); // Inputs the name of the shop
  cin.clear();
  m_myShop.SetName(name);              // Sets the name in the shop
  while (choice != 5 && (rank != 'S')) // Loops until user does not enter 5 or completes the game
  {
    choice = MainMenu();       // Calls main menu
    rank = m_myShop.GetRank(); // Finds the current rank
  }
  cout << "Thanks for playing UMBC Potion Craft"
       << "\n";
}
// Name: DisplayMyIngredients()
// Desc - Displays the Shop's ingredients (Uses GetIngredient)
// Preconditions - Player's Shop has ingredients
// Postconditions - Displays a numbered list of ingredients
void Game::DisplayIngredients()
{
  Ingredient tempIngredient;
  string name = "r";
  int quantity = 2;
  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    tempIngredient = m_myShop.GetIngredient(i); // Fetches the ingredient from the array
    name = tempIngredient.m_name;
    quantity = tempIngredient.m_quantity;
    cout << i + 1 << ". " << name << " " << quantity << "\n";
  }
}
// Name: MainMenu()
// Desc - Displays and manages menu. Also checks win condition (Shop reaches S rank).
// Preconditions - Player has a Shop
// Postconditions - Returns number including exit
int Game::MainMenu()
{
  int choice = 0;
  Ingredient ingredient1;
  Ingredient ingredient2;
  string name = m_myShop.GetName(); // Fetches the shop name
  do
  {
    cout << "What would you like to do in " << name << "'s shop?"
         << "\n";
    cout << "1. Display your Shop's Ingredients"
         << "\n";
    cout << "2. Search for Natural Ingredients" << '\n';
    cout << "3. Attempt to Merge Ingredients"
         << "\n";
    cout << "4. See Score"
         << "\n";
    cout << "5. Quit" << '\n';
    cin >> choice;
  } while ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5)); // Displays the choices and repeats until one of the choice is selected

  if (choice == 1) // Displays the ingredient if choice 1 is selected
  {
    DisplayIngredients();
  }
  else if (choice == 2)
  { // Searches an ingredient if choice 2 is selected
    SearchIngredients();
  }
  else if (choice == 3)
  { // Searches an ingredient if choice 3 is selected
    CombineIngredients();
  }
  else if (choice == 4)
  {
    m_myShop.ShopScore(); // Displays the shop score
  }
  else if (choice == 5)
  { // Quit
  }

  return choice;
}
// Name: SearchIngredients()
// Desc - Attempts to search for natural ingredients (must be type "natural")
// Preconditions - Natural ingredients loaded
// Postconditions - Increases quantity in Shop's possession of ingredients
void Game::SearchIngredients()
{
  bool flag = false;
  string tempNatural;
  int randomIndex;
  Ingredient ingredient;

  do
  {
    randomIndex = rand() % (PROJ2_SIZE); // Randomly picks an index of the ingredients
    tempNatural = m_ingredients[randomIndex].m_type;
    if (tempNatural == "natural")
    { // Checks if ingredient is natural
      flag = true;
    }
  } while (flag == false); // Loops until the ingredient randomly selected is natural
  ingredient = m_myShop.GetIngredient(randomIndex);
  m_myShop.IncrementQuantity(ingredient); // Increments the quantity
  cout << m_ingredients[randomIndex].m_name << " Found!"
       << "\n";
}
// Name: CombineIngredients()
// Desc - Attempts to combine known ingredients. If combined, quantity of ingredient decreased
// Preconditions - Shop is populated with ingredients
// Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineIngredients()
{
  int ingredients;
  bool quantityCheck = false;
  int recipeIndex;
  Ingredient ingredient1;
  Ingredient ingredient2;
  Ingredient finalIngredient;
  string name1;
  string name2;
  RequestIngredient(ingredients); // Asks the user for the ingredient
  ingredient1 = m_myShop.GetIngredient(ingredients);
  RequestIngredient(ingredients); // Asks the user for the ingredient
  ingredient2 = m_myShop.GetIngredient(ingredients);
  quantityCheck = m_myShop.CheckQuantity(ingredient1, ingredient2); // Checks if the ingredient is available. (quantity > 0)
  if (quantityCheck == false)
  { // If the ingredient is not available
    cout << "You do not have enough " << ingredient1.m_name << " or " << ingredient2.m_name << " to attempt that merge"
         << "\n";
  }
  else
  { // If the ingredient is not available
    name1 = ingredient1.m_name;
    name2 = ingredient2.m_name;
    recipeIndex = SearchRecipes(name1, name2); // Searches for the recipe
    if (recipeIndex == -1)
    { // If there is no recipe
      cout << "No recipe found"
           << "\n";
    }
    else
    { // If there is a recipe
      finalIngredient = m_myShop.GetIngredient(recipeIndex);
      cout << name1 << " combined with " << name2 << " to make " << finalIngredient.m_name << "!"
           << "\n";
      cout << "You have made " << finalIngredient.m_name << " for your shop."
           << "\n";
      m_myShop.IncrementQuantity(finalIngredient); // Increments the product ingredient
      m_myShop.DecrementQuantity(ingredient1);     // Decrements the starting ingredient
      m_myShop.DecrementQuantity(ingredient2);     // Decrements the starting ingredient
    }
  }
}
// Name: RequestIngredient()
// Desc - Requests ingredient to use to merge
// Preconditions - Shop has ingredients to try and merge
// Postconditions - Returns integer of item selected by user
void Game::RequestIngredient(int &choice)
{
  do
  {
    cout << "Which ingredients would you like to merge?"
         << "\n";
    cout << "To list known ingredients enter -1" << '\n';
    cin >> choice; // Requests for the index of the ingredient they want to combine
    if (choice == -1)
    {
      DisplayIngredients(); // Displays ingredients if -1 is chosen
    }
  } while ((choice <= 0) || (choice >= PROJ2_SIZE)); // Loops until the user chooses an index from the specified range (1 to 23)
  choice = choice - 1;                               // Index starts from zero so 1 can become zero
}
// Name: SearchRecipes()
// Desc - Searches recipes for two strings (name of item)
// Preconditions - m_ingredients is populated
// Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string ingredient1, string ingredient2)
{
  int index = -1;
  for (int i = 0; i < PROJ2_SIZE; i++)
  { // Loops through all the ingredients
    if (ingredient1 == m_ingredients[i].m_ingredient1)
    { // Checks for the ingredient if it matches with the other ingredients
      if (ingredient2 == m_ingredients[i].m_ingredient2)
      { // Checks if the second ingredient matches
        index = i;
      }
    }
    else if (ingredient2 == m_ingredients[i].m_ingredient1)
    { // Checks if the first ingredient matches
      if (ingredient1 == m_ingredients[i].m_ingredient2)
      { // Checks if the second ingredient matches
        index = i;
      }
    }
  }
  return index;
}