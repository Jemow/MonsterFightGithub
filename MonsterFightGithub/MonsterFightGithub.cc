/**
 * @jemoelablay
 *
 * MonsterFight.cpp
 *
 * 11.09.2024
 *
 * Description : This is a game where we have a fight between 2 mob,
 * at the beginning, the player has to choose each mob are going to
 * fight. The mobs which are going to fight must have distinct races,
 * all the mobs can, deal damage (damage dealt are subtracted by
 * the opponent's defense point), heal them self and parry which allows
 * the mob to enforce his defense points. The fight end only if one
 * of the mob are dead.
 */

#include <iostream>

#include "Mob.h"

// Initialisation of all mobs
Mob Jemo(20, 13, 4,  110, Mob::Human);
Mob Orc(60, 8, 3,60, Mob::Orc);
Mob Ogre(75, 6, 3, 20, Mob::Ogre);
Mob Elf(30, 12, 2, 200, Mob::Elf);

/**
 * @brief Get the choice of the mob until the inputs are valid
 * 
 * @param choice The actual choice given by the player
 * 
 */
void Select(int &choice)
{
    do
    {
        std::cout << "1. Jemo \n"
        << "2. Orc \n"
        << "3. Ogre \n"
        << "4. Elf \n\n";
        std::cout << "Select : ";
        std::cin >> choice;

        // Check valid inputs
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
        }
    }
    while (choice < 1 || choice > 4);
    std::cin.ignore();
    std::cout << '\n';
}

/**
 * @brief Relate the choice of the player with the specified mob
 * 
 * @param choice The actual choice given by the player
 * 
 * @return It returns the selected mob
 */
Mob DefineMob(int choice)
{
    switch (choice)
    {
    case 1: return Jemo;
    case 2: return  Orc;
    case 3: return  Ogre;
    case 4: return  Elf;
    }
    return Jemo; // Default
}

/**
 * @brief This is what perform a mob each turn, he can Attack, Parry or Heal
 * 
 * @param attacker 
 * @param defender 
 */
void Action(Mob& attacker, Mob& defender)
{
    int action = rand() % 3;
    switch (action)
    {
        case 0: attacker.Attack(defender); break;
        case 1: attacker.Parry(3); break;
        case 2: attacker.Heal(3); break;
    }
}

/**
 * @brief Check if one of the mobs are dead
 * 
 * @param mob1 // First mob health
 * 
 * @param mob2 // Second mob health
 * 
 * @return True if one of them are dead otherwise false
 */
bool OneMobDead(Mob mob1, Mob mob2)
{
    return mob1.getHealth() <= 0 || mob2.getHealth() <= 0;
}

int main()
{
    // Generate a seed by time (1970 January)
    srand(time(nullptr));

    // Choices of the player input
    int choice1;
    int choice2;

    // Number of round
    int round = 0;

    do
    {
        std::cout << "Select a first mob to fight \n";
        Select(choice1);
        std::cout << "Select a second mob to fight \n";
        Select(choice2);
    }
    // Races of mobs mustn't be the same
    while (choice1 == choice2);

    // Initialise the fighters
    Mob mob1 = DefineMob(choice1);
    Mob mob2 = DefineMob(choice2);

    std::cout << "The " << mob1.getRace() << " has " << mob1.getHealth() << " health and"
    << " the " << mob2.getRace() << " has " << mob2.getHealth() << " health\n";
    std::cin.get();

    // Keep fighting until one of the mob dies
    while (true)
    {
        // Next round
        round++;
        std::cout << "------- Round " << round << " -------\n";
        
        // Decrease their parry round by 1
        mob1.DecreaseParry();
        mob2.DecreaseParry();

        Mob &first = mob1;
        Mob &second = mob2;

        // If mob2 is faster than mob1, mob2 will do his action first
        if(mob1.getSpeed() < mob2.getSpeed()) std::swap(first, second);
        
        Action(first, second);
        // Check if one of the mob are dead
        if(OneMobDead(mob1, mob2)) break;
        std::cin.get();
        Action(second, first);
        if(OneMobDead(mob1, mob2)) break;
        std::cin.get();
    }

    // Who's winning
    Mob winner = mob1;
    if(mob1.getHealth() < mob2.getHealth()) winner = mob2;
    std::cout << '\n' << "The " << winner.getRace() << " won in " << round << " rounds!\n";
}