#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>
#include <vector>
#include "Actor.h"

class Actor;
class Player;

bool const LAND = true;
bool const MOVE = false;

int const IMPACTABLE = 0;
int const SQUARE = 1;








//change roll back to ten for monsters and player


//go through checklist
//write the report
//go through one last time









class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    
    
    

    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    void addActor(Actor* actor);
    bool notEmpty(int x, int y) const;
    Actor* squareOrImpactableAt(int x, int y, int squareOrImpactable) const;
    Actor* getRandomSquare(int x, int y) const;
    Player* getOtherPlayer(Player* p) const;
    
    int getBankBalance() const {return m_bankBalance;}
    void setBankBalance(int newBalance){m_bankBalance = newBalance;}
    
    
    Player* getPeach()const {return m_peach;}
    Player* getYoshi()const {return m_yoshi;}

private:
    std::vector<Actor *> m_actors;
    Board m_bd;
    Player* m_peach;
    Player* m_yoshi;
    int m_bankBalance;
};

#endif // STUDENTWORLD_H_
