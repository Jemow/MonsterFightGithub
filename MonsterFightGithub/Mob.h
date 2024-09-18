#pragma once
#include <string>

class Mob
{
public:

    enum race
    {
        Human,
        Orc,
        Ogre,
        Elf,
    };
    
    Mob(int health, int attack, int defense, int speed, race _race);

    void Attack(Mob& defender);
    void Parry(int amount);
    void Heal(int amount);
    void DecreaseParry();
    std::string EnumToString(race _race);

    int getHealth() {return health_;}
    int getSpeed() {return speed_;}
    std::string getRace() {return EnumToString(race_);}

    

private:
    void ChangeHealth(int amount);
    
    void setHealth(int value);

    int health_;
    int attack_;
    int defense_;
    int speed_;
    int initial_defense_;
    int initial_health_;
    int active_parry_ = 0;
    race race_;
};
