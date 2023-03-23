#include "Ingredient.h" //Include for the ingredient struct
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "Shop.h"
#include "Game.h"
using namespace std;

// Constants (Do not edit)

// Name: Shop() - Default Constructor
// Desc: Used to build a new Player Shop
// Preconditions - Requires default values (Name = Test, numIngredients = 0, Rank = F
// Postconditions - Creates a new Player Shop
Shop::Shop() {}
// Name: Shop(name) - Overloaded constructor
// Desc - Used to build a new Player Shop (m_numIngredients = 0, m_shopRank = F)
// Preconditions - Requires name
// Postconditions - Creates a new Player Shop
Shop::Shop(string name)
{
  m_shopName = name;
  m_numIngredients = 0;
  m_shopRank = 'F';
  // Sets everything to default
}
// Name: GetName()
// Desc - Getter for the Player Shop's name
// Preconditions - Player Shop exists
// Postconditions - Returns the name of the Player Shop
string Shop::GetName()
{
  return m_shopName;
}
// Name: SetName(string)
// Desc - Allows the user to change the name of the Player Shop
// Preconditions - Player Shop exists
// Postconditions - Sets name of Player Shop
void Shop::SetName(string name)
{
  m_shopName = name; // Sets the name of the shop
}
// Name: CheckIngredient(Ingredient)
// Desc - Checks to see if the Shop has a ingredient
// Preconditions - Shop already has ingredients
// Postconditions - Returns index of ingredient if the Shop has it else -1
int Shop::CheckIngredient(Ingredient ingredients)
{
  int index = -1;
  for (int i = 0; i < PROJ2_SIZE; i++)
  { // Loops until the ingredient is found in the array
    if (m_myIngredients[i].m_name == ingredients.m_name)
    {
      index = i; // Stores the index of the ingredient in the array
    }
  }
  return index;
}
// Name: AddIngredient(Ingredient)
// Desc - Inserts a ingredient into the Shop's list of ingredients.
//        Increments m_numIngredients
// Preconditions - Shop exists
// Postconditions - Add a ingredient to the Shop's m_myIngredients with a quantity of 0
void Shop::AddIngredient(Ingredient ingredients[PROJ2_SIZE])
{
  string name;
  string type;
  string ingredient1;
  string ingredient2;
  int quantity;
  for (int index = 0; index < PROJ2_SIZE; index++) // loops until all the ingredients are added
  {
    name = ingredients[index].m_name;                                          // Stores the name of the ingredient
    type = ingredients[index].m_type;                                          // Stores the type of the ingredient
    ingredient1 = ingredients[index].m_ingredient1;                            // Stores the ingredient 1 to make it
    ingredient2 = ingredients[index].m_ingredient2;                            // Stores the ingredient 2 to make it
    quantity = ingredients[index].m_quantity;                                  // Stores the quantity of the ingredient
    m_myIngredients[index] = {name, type, ingredient1, ingredient2, quantity}; // Adds the ingredient into the Shop list
    m_numIngredients = m_numIngredients + 1;
  }
}
// Name: IncrementQuantity(Ingredient)
// Desc - Increases the quantity for an ingredient the Shop knows
// Preconditions - Shop exists
// Postconditions - Increases quantity of ingredient for the Shop
void Shop::IncrementQuantity(Ingredient ingredient)
{
  int index;
  index = CheckIngredient(ingredient);
  m_myIngredients[index].m_quantity += 1; // Increments the quantity
}
// Name: DecrementQuantity(Ingredient)
// Desc - Reduces quantity from the Shop's inventory with true, if no quantity false
// Preconditions - A Shop exists
// Postconditions - Reduces quantity of ingredient for the Shop
void Shop::DecrementQuantity(Ingredient ingredient)
{
  int index;
  index = CheckIngredient(ingredient);
  if (m_myIngredients[index].m_quantity > 0)
  {                                         // Decrements only if quantity > 0
    m_myIngredients[index].m_quantity -= 1; // Decrements the quantity
  }
  else
  {
    m_myIngredients[index].m_quantity = 0; // Avoids going negative
  }
}
// Name: CheckQuantity(Ingredient, Ingredient)
// Desc - Checks to see if quantity of two merge ingredients are available
// Preconditions - Shop exists with ingredients
// Postconditions - Returns true if both are available (including two of same ingredient)
bool Shop::CheckQuantity(Ingredient ingredient1, Ingredient ingredient2)
{
  int quantity1;
  int quantity2;
  bool status = false;

  quantity1 = ingredient1.m_quantity; // Fetches the quantity of ingredient 1
  quantity2 = ingredient2.m_quantity; // Fetches the quantity of ingredient 2

  if (quantity1 >= 1)
  {
    if (quantity2 >= 1)
    {
      status = true; // Status is true when both the quantity is greater than 1
    }
  }

  return status;
}
// Name: GetIngredient(int)
// Desc - Checks to see if the Shop has any ingredients
// Preconditions - The Shop already has ingredients
// Postconditions - Returns ingredient at specific index
Ingredient Shop::GetIngredient(int index)
{
  Ingredient tempIngredient;
  string name;
  string type;
  string ingredient1;
  string ingredient2;
  int quantity;

  name = m_myIngredients[index].m_name;                              // Fetches the name of the ingredient
  type = m_myIngredients[index].m_type;                              // Fetches the type of the ingredient
  ingredient1 = m_myIngredients[index].m_ingredient1;                // Fetches the starting ingredient to make the ingredient
  ingredient2 = m_myIngredients[index].m_ingredient2;                // Fetches the starting ingredient to make the ingredient
  quantity = m_myIngredients[index].m_quantity;                      // Fetches the quantity of the ingredient
  tempIngredient = {name, type, ingredient1, ingredient2, quantity}; // Seperates the ingredient from the array

  return tempIngredient;
}
// Name: CalcRank()
// Desc - Divides the total available ingredients, by the IngredientCount()
// Updates the rank based on percentages
//      0-29 = F, 30-49 = D, 50-69 = C, 70-89 = B, 90-99 = A, 100 = S
// Preconditions - Shop exists and has a rank
// Postconditions - m_shopRank will be updated
void Shop::CalcRank()
{
  int counter;
  int rank;
  counter = IngredientCount();                       // Stores the number of ingredients that are greater than 1
  rank = (double(counter) / m_numIngredients) * 100; // Finds the rank percentage
  if (rank < RANK_D)
  { // Less than Rank D
    m_shopRank = 'F';
  }
  else if (rank < RANK_C)
  { // Less than Rank C
    m_shopRank = 'D';
  }
  else if (rank < RANK_B)
  { // Less than Rank B
    m_shopRank = 'C';
  }
  else if (rank < RANK_A)
  { // Less than Rank A
    m_shopRank = 'B';
  }
  else if (rank < RANK_S)
  { // Less than Rank S
    m_shopRank = 'A';
  }
  else
  {
    m_shopRank = 'S';
  }
}
// Name: GetRank()
// Desc - Returns the current shop's rank
// Preconditions - The shop exists
// Postconditions - Returns the character indicating the rank of the shop
char Shop::GetRank()
{
  return m_shopRank;
}
// Name: IngredientCount()
// Desc - Loops through m_myIngredients to see how many ingredients have a quantity > 0
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Returns the count of ingredients with a quantity > 0
int Shop::IngredientCount()
{
  int quantity = 0;
  int counter = 0;
  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    quantity = m_myIngredients[i].m_quantity;
    if (quantity >= 1)
    {
      counter = counter + 1; // Checks for ingredients greater than 1
                             // Counter is incremented
    }
  }
  return counter;
}
// Name: ShopScore()
// Desc - Displays information about the shop: name, ingredients found, total available,
//        percentage found, and rank
// Preconditions - The shop exists, m_myIngredients populated
// Postconditions - Displays name, ingredient count, total ingredients, percentage, and rank
void Shop::ShopScore()
{
  int counter = IngredientCount();                       // Stores the number of ingredients greater than 1
  int rank = (double(counter) / m_numIngredients) * 100; // Finds the rank percentage
  cout << counter << "\n";
  cout << "***The Potion Shop***"
       << "\n";
  cout << "Owned by: " << GetName() << "\n";
  cout << "There are " << m_numIngredients << " available products."
       << "\n";
  cout << "This shop has " << counter << " products in stock."
       << "\n"; // Displays the shop score
  if (counter == 0)
  { // when counter is == 0. Avoids going to negative
    cout << "Which is "
         << "0%"
         << "\n";
    cout << "Shop Rank: F"
         << "\n";
  }
  else
  {
    cout << "Which is " << rank << "%"
         << "\n";
    CalcRank(); // Calculates the rank
    cout << "Shop Rank: " << m_shopRank << "\n";
  }
  cout << "*********************"
       << "\n";
}