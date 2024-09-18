#include "Mob.h"

#include <iostream>

/**
 * @brief This is the constructor of the mob with all the base parameters
 * 
 * @param health The health of the mob
 * @param attack The damage that can do the mob
 * @param defense The amount of damage that the mob can block
 * @param speed The speed of the mob, if it is high speed he has great chance to perform first
 * @param _race 
 */
Mob::Mob(int health, int attack, int defense, int speed, race _race)
{
    initial_health_ = health;
    health_ = health;
    attack_ = attack;
    speed_ = speed;
    initial_defense_ = defense;
    defense_ = defense;
    race_ = _race;
}

/**
 * @brief The mob attack the other mob and deal his damage - the defender defense point
 * 
 * @param defender The opponent that will receive the damages
 */
void Mob::Attack(Mob& defender)
{
    int damage = attack_ - defender.defense_;
    if(damage <= 0)
    {
        damage = 0; std::cout << "The " << getRace() << " attack but the "
        << defender.getRace() << " blocked all the damage!\n";
    }
    else
    {
        std::cout << "The " << getRace() << " did " << damage <<
            " damage to the " << defender.getRace() << '\n';
    }
    defender.ChangeHealth(-damage);
}

/**
 * @brief A parry allows the mob to increase his defense points to a specific amount
 * 
 * @param point The amount of points to add to the defense
 * 
 */
void Mob::Parry(int point)
{
    defense_ = initial_defense_;
    defense_ += point;
    std::cout << "The " << getRace() << " do a Pary! His defense went from " << initial_defense_ << " to " << defense_ << '\n';
    active_parry_ = 2;
}

/**
 * @brief Allows the mob to heal him self with a specific amount
 * 
 * @param amount The amount of health to add to the mob's life
 */
void Mob::Heal(int amount)
{
    std::cout << "The " << getRace() << " healed his self by " << amount << '\n';
    ChangeHealth(amount);
}

/**
 * @brief This method decrease the active_parry_ by 1, if the active_parry_
 *        is equal to 0 the mob will not parrying anymore and his defense
 *        points will be reset at his default stat from the beginning.
 *        (Obviously called each turn)
 */
void Mob::DecreaseParry()
{
    if(active_parry_ < 1 && defense_ != initial_defense_)
    {
        defense_ = initial_defense_;
        std::cout << "The defense of the " << EnumToString(race_) << " came back to " << defense_ << '\n';
    }
    else active_parry_--;
}

/**
 * @brief It takes a type of race and convert it into a string
 * 
 * @param _race The race to convert
 * 
 * @return It returns the string corresponding to the race
 */
std::string Mob::EnumToString(race _race)
{
    switch (_race)
    {
    case 0: return "Human";
    case 1: return "Orc";
    case 2: return "Ogre";
    case 3: return "Elf";
    }
    return "Unknown";
}

/**
 * @brief Add or decrease the health by a certain amount
 * 
 * @param amount The amount to add to the health (negative to reduce)
 */
void Mob::ChangeHealth(int amount)
{
    setHealth(getHealth() + amount);
    std::cout << "The " << getRace() << " has now " << getHealth() << " health\n";
}

// Setter health
void Mob::setHealth(int value)
{
    if(value > initial_health_) health_ = initial_health_;
    else if(value < 0) health_ = 0;
    else health_ = value;
}
