#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;
class Player;

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* World, int imageID, double startX, double startY, int startDirection, int depth, double size);
    virtual ~Actor(){}    
    virtual void doSomething() = 0;
    virtual void setBeingTeleported(bool beingTeleported) = 0;
    
    virtual bool getBeingTeleported() const = 0;
    virtual bool getIsASquare() const = 0;
    virtual bool getIsImpactable() const = 0;
  
    StudentWorld* getWorld() const {return m_world;}
    void setDead(){m_alive = false;}
    bool getAlive() const {return m_alive;}
    
private:
    bool m_alive;
    StudentWorld* m_world;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Actor Sub-Classes//////////////////////////////////////////////////////////////////////////////////////////
class MovingAvatar : public Actor
{
public:
  
    MovingAvatar(StudentWorld* World, int imageID, double startX, double startY);
    
    
    void move(int dir);
    
    
    bool checkFork(int x, int y);
    bool landOrMoveOn(int x, int y, bool land);
    void findDirection();
    void findRandomDirection();
    
    
    void setMoveDirection(int direction) {m_direction = direction;}
    void setTicksOnSquare(int ticks) {m_ticksOnSquare = ticks;}
    void setWaitingToRoll(bool waitingToRoll){m_waitingToRoll = waitingToRoll;}
    void setTicksToMove(int setTicks){m_ticks_to_move = setTicks;}
    virtual void setBeingTeleported(bool beingTeleported){m_beingTeleported = beingTeleported;}
   
 
    virtual bool getIsASquare() const {return m_isASquare;}
    int getTicksToMove() const {return m_ticks_to_move;}
    int getCurrRoll() const;
    int getMoveDirection() const{return m_direction;}
    int getTicksOnSquare() const{return m_ticksOnSquare;}
    bool getWaitingToRoll() const{return m_waitingToRoll;}
    bool getBeingTeleported() const {return m_beingTeleported;}
    
private:
 
    bool m_isASquare;
    int m_direction;
    int m_ticksOnSquare;
    bool m_waitingToRoll;
    int m_ticks_to_move;
    bool m_beingTeleported;
};



class Square : public Actor
{
public:
    Square(StudentWorld* World, int imageID, double startX, double startY, int startDirection);
    virtual void doSomething();
    virtual bool getIsASquare() const {return m_isASquare;}
    virtual void setBeingTeleported(bool beingTeleported){}     //dummy implementation because squares cant teleport
    
    
    //make pure virtual
    
    virtual bool getBeingTeleported() const {return false;}
    virtual bool getIsImpactable() const {return m_isImpactable;}
    virtual void moveOnAction(Player* player) = 0;
    virtual void landOnAction(Player* player) = 0;
  
private:
    bool m_isASquare;
    bool m_isImpactable;

};





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Moving Actor Sub-Classes//////////////////////////////////////////////////////////////////////////////////////////
class Vortex : public MovingAvatar
{
public:
    Vortex(StudentWorld* World, int imageID, double startX, double startY, int moveDirection);
    virtual void doSomething();
    
    virtual bool getIsImpactable() const {return m_isImpactable;}
    
private:

    bool m_isImpactable;
};





class Player : public MovingAvatar
{
public:
    Player(StudentWorld* World, int playerNum, int imageID, double startX, double startY);
    
    virtual void doSomething();
 
    
   
    void setCoins(int newCoins){m_coins = newCoins;}
    void setStars(int newStars){m_stars = newStars;}
    void setOnDirSquare(bool onDirSquare){m_onDirSquare = onDirSquare;}
    void setHasVortex(bool hasVortex){m_hasVortex = hasVortex;}
    
    virtual bool getIsImpactable() const {return m_isImpactable;}
    bool getOnDirSquare(){return m_onDirSquare;}
    int getCoins() const {return m_coins;}
    int getStars() const {return m_stars;}
    bool getHasVortex() const {return m_hasVortex;}


private:
    bool m_isImpactable;
    int m_coins;
    int m_stars;
    bool m_hasVortex;
    int m_playerNum;
    bool m_onDirSquare;


};


class Monster : public MovingAvatar
{
public:
    Monster(int roll, StudentWorld* World, int imageID, double startX, double startY);
    virtual void doSomething();
    
    
    virtual void monsterAction(Player* player) = 0;
    virtual void ifMonsterLand() = 0;
   
    virtual bool getIsImpactable() const {return m_isImpactable;}
    int getPauseTicks() const {return m_pauseTicks;}
    
private:
    int m_pauseTicks;
    int m_rollNum;
    bool m_isImpactable;
};





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Monster Sub-Classes////////////////////////////////////////////////////////////////////////////////////////

class Boo : public Monster
{
public:
    Boo(StudentWorld* World, int imageID, double startX, double startY);
    virtual void monsterAction(Player* player);
    virtual void ifMonsterLand(){}
    
    
private:

};


class Bowser : public Monster
{
public:
    Bowser(StudentWorld* World, int imageID, double startX, double startY);

    virtual void monsterAction(Player* player);
    virtual void ifMonsterLand();
private:
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Square Sub-Classes/////////////////////////////////////////////////////////////////////////////////////////
class DirectionalSquare : public Square
{
public:
    DirectionalSquare(StudentWorld* World, int imageID, double startX, double startY, int direction);
    virtual void moveOnAction(Player* player);
    virtual void landOnAction(Player* player);
private:
    int m_direction;
};



class EventSquare : public Square
{
public:
    EventSquare(StudentWorld* World, int imageID, double startX, double startY);
    
    virtual void moveOnAction(Player* player){}
    virtual void landOnAction(Player* player);
private:
};



class DroppingSquare : public Square
{
public:
    DroppingSquare(StudentWorld* World, int imageID, double startX, double startY);
    virtual void moveOnAction(Player* player){}
    virtual void landOnAction(Player* player);
private:
};
 
 


class CoinSquare : public Square
{
public:
    CoinSquare(int grantAmount, StudentWorld* World, int imageID, double startX, double startY);
    virtual void moveOnAction(Player* player){}
    virtual void landOnAction(Player* player);
    
    int getGrantAmount() const {return m_grantAmount;}
    void setGrantAmountLand(int grantAmount){m_grantAmount = grantAmount;}
    
private:
    int m_grantAmount;
};


class StarSquare : public Square
{
public:
    StarSquare(StudentWorld* World, int imageID, double startX, double startY);
    virtual void moveOnAction(Player* player);
    virtual void landOnAction(Player* player);
private:
};


class BankSquare : public Square
{
public:
    BankSquare(StudentWorld* World, int imageID, double startX, double startY);
    virtual void moveOnAction(Player* player);
    virtual void landOnAction(Player* player);
private:
  
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#endif // ACTOR_H_
