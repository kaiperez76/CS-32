#include "Actor.h"
#include "StudentWorld.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Actor::Actor(StudentWorld* World, int imageID, double startX, double startY, int startDirection, int depth, double size): GraphObject(imageID, startX*SPRITE_WIDTH, startY*SPRITE_HEIGHT, startDirection, depth, size){
    
    m_world = World;
    m_alive = true;
    
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


MovingAvatar::MovingAvatar(StudentWorld* World, int imageID, double startX, double startY):Actor(World, imageID, startX, startY, 0, 0, 1){
    m_waitingToRoll = true;
    m_ticksOnSquare = 0;
    m_direction = 0;
    m_ticks_to_move = 0;
    m_isASquare = false;
    m_beingTeleported = false;
 
}



void MovingAvatar::move(int dir){
    switch(dir){
        case right:
            moveTo(getX() + 2, getY());
            setDirection(right);
            break;
        case up:
            moveTo(getX(), getY() + 2);
            setDirection(right);
            break;
        case left:
            moveTo(getX() - 2, getY());
            setDirection(left);
            break;
        case down:
            moveTo(getX(), getY() - 2);
            setDirection(right);
            break;
    }
}

bool MovingAvatar::checkFork(int x, int y){
    int possibleDirs = 0;
    
 
    
    if((x % SPRITE_WIDTH) == 0 && (y % SPRITE_HEIGHT) == 0){
        if((getWorld()->notEmpty(x+SPRITE_WIDTH, y))){
            possibleDirs += 1;
        }
        if((getWorld()->notEmpty(x-SPRITE_WIDTH, y))){
            possibleDirs += 1;
        }
        if((getWorld()->notEmpty(x, y+SPRITE_HEIGHT))){
            possibleDirs += 1;
        }
        if((getWorld()->notEmpty(x, y-SPRITE_HEIGHT))){
            possibleDirs += 1;
        }
    }

    
    return possibleDirs > 2;
}

bool MovingAvatar::landOrMoveOn(int x, int y, bool land){
    
    if((this->getX() % SPRITE_WIDTH) == 0 && (this->getY() % SPRITE_HEIGHT) == 0 ){
        if((this->getX() == x) && (this->getY() == y)){
            if(getTicksOnSquare() == 0 && getWaitingToRoll() && land){
                setTicksOnSquare(getTicksOnSquare() + 1);
                return true;}
            if(getTicksOnSquare() == 0 && !getWaitingToRoll() && !land){
                setTicksOnSquare(getTicksOnSquare() + 1);
                return true;}
         
        }
    }

    else {
        setTicksOnSquare(0);
        return false;
    }
    
    
return false;
}




   
void MovingAvatar::findDirection(){
    
    int newX = getX();
    int newY = getY();
    
    if(getMoveDirection() == up || getMoveDirection() == down){
        if(getWorld()->notEmpty(newX + SPRITE_WIDTH, newY)){
            setMoveDirection(right);
            setDirection(right);
            return;
        }
        else{
            setMoveDirection(left);
            setDirection(left);
            return;
        }
            }
 
            
    if(getMoveDirection() == right || getMoveDirection() == left){
        if(getWorld()->notEmpty(newX , newY + SPRITE_HEIGHT)){
            setMoveDirection(up);
            setDirection(right);
            return;
        }
        else{
            setMoveDirection(down);
            setDirection(right);
            return;
        }
    }
}


void MovingAvatar::findRandomDirection(){
    int random = randInt(0, 23);
    
    int permutations[24][4] = {
        {1, 2, 3, 4},
        {1, 2, 4, 3},
        {1, 3, 2, 4},
        {1, 3, 4, 2},
        {1, 4, 2, 3},
        {1, 4, 3, 2},
        {2, 1, 3, 4},
        {2, 1, 4, 3},
        {2, 3, 1, 4},
        {2, 3, 4, 1},
        {2, 4, 1, 3},
        {2, 4, 3, 1},
        {3, 1, 2, 4},
        {3, 1, 4, 2},
        {3, 2, 1, 4},
        {3, 2, 4, 1},
        {3, 4, 1, 2},
        {3, 4, 2, 1},
        {4, 1, 2, 3},
        {4, 1, 3, 2},
        {4, 2, 1, 3},
        {4, 2, 3, 1},
        {4, 3, 1, 2},
        {4, 3, 2, 1}
    };

    for(int k = 0; k < 4; k++){
            switch(permutations[random][k]){
                case 1:
                    if(getWorld()->notEmpty(getX() + SPRITE_WIDTH, getY())){
                        setMoveDirection(right);
                        setDirection(right);
                        return;
                    }
                    break;
                case 2:
                    if(getWorld()->notEmpty(getX() - SPRITE_WIDTH, getY())){
                        setMoveDirection(left);
                        setDirection(left);
                        return;
                    }
                    break;
                case 3:
                    if(getWorld()->notEmpty(getX(), getY() + SPRITE_HEIGHT)){
                        setMoveDirection(up);
                        setDirection(right);
                        return;
                    }
                    break;
                case 4:
                    if(getWorld()->notEmpty(getX(), getY() - SPRITE_HEIGHT)){
                        setMoveDirection(down);
                        setDirection(right);
                        return;
                    }
                    break;
            }
        }
    }


int MovingAvatar::getCurrRoll() const{
    if((getX() % SPRITE_WIDTH) == 0 && (getY() % SPRITE_HEIGHT) == 0){
        return m_ticks_to_move/8;
    }
    return (m_ticks_to_move/8) + 1;
        
}




Square::Square(StudentWorld* World, int imageID, double startX, double startY, int startDirection):Actor(World, imageID, startX, startY, startDirection, 1, 1){
    m_isASquare = true;
    m_isImpactable = false;
 
}


void Square::doSomething(){
    Player* peachPointer = getWorld()->getPeach();
    Player* yoshiPointer = getWorld()->getYoshi();
    
    
    if(peachPointer->landOrMoveOn(getX(), getY(), LAND)){
        landOnAction(peachPointer);
    }
    
    
    if(yoshiPointer->landOrMoveOn(getX(), getY(), LAND)){
        landOnAction(yoshiPointer);
    }
    
    

    if(peachPointer->landOrMoveOn(getX(), getY(), MOVE)){
        moveOnAction(peachPointer);
    }
    
    
    
    if(yoshiPointer->landOrMoveOn(getX(), getY(), MOVE)){
        moveOnAction(yoshiPointer);
    }
    
    
    

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




Vortex::Vortex(StudentWorld* World, int imageID, double startX, double startY, int moveDirection): MovingAvatar(World, imageID, startX, startY){
    setMoveDirection(moveDirection);
    m_isImpactable = false;
}

void Vortex::doSomething(){
    
    if(!getAlive()){
        return;
    }
    
    if(getX() < 0 || getX() >= VIEW_WIDTH || getY() < 0 || getY() >= VIEW_HEIGHT){
        setDead();
    }
    
    
    
    
    //checking current space in case it spawns on a monster
    Actor* HitActor = getWorld()->squareOrImpactableAt(getX(), getY(), IMPACTABLE);
    if(HitActor != nullptr){
        HitActor->setBeingTeleported(true);
        setDead();
        getWorld()->playSound(SOUND_HIT_BY_VORTEX);
        return;
    }
    
    int newX = getX();
    int newY = getY();
    
    //checking at space ahead so it works at overlap
    getPositionInThisDirection(getMoveDirection(), SPRITE_WIDTH, newX, newY);
    Actor* HitActor2 = getWorld()->squareOrImpactableAt(newX, newY, IMPACTABLE);
    if(HitActor2 != nullptr){
        HitActor2->setBeingTeleported(true);
        setDead();
        getWorld()->playSound(SOUND_HIT_BY_VORTEX);
        return;
    }
    
    
 
    move(getMoveDirection());
}



Player::Player(StudentWorld* World, int playerNum, int imageID, double startX, double startY): MovingAvatar(World, imageID, startX, startY){
    m_coins = 0;
    m_stars = 0;
    m_hasVortex = false;
    m_playerNum = playerNum;
    m_onDirSquare = false;
    m_isImpactable = false;
}

void Player::doSomething(){
    
    if(getBeingTeleported()){
        Actor* Square = getWorld()->getRandomSquare(getX(), getY());
        moveTo(Square->getX(), Square->getY());
        setTicksOnSquare(0);
        if(!getOnDirSquare()){
            findRandomDirection();}
        setBeingTeleported(false);
    }
    
  
    if(getWaitingToRoll()){
       
        int currAction = getWorld()->getAction(m_playerNum);
        if(currAction == ACTION_ROLL){
            int roll = randInt(1, 10);
            setTicksToMove(roll * 8);
            setWaitingToRoll(false);
            }
        if(currAction == ACTION_FIRE){
            if(getHasVortex()){
                int newX = getX();
                int newY = getY();
                
                getPositionInThisDirection(getMoveDirection(), SPRITE_WIDTH, newX, newY);
                Actor* newVortex = new Vortex(getWorld(),IID_VORTEX, newX/SPRITE_WIDTH, newY/SPRITE_HEIGHT, getMoveDirection());
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                getWorld()->addActor(newVortex);
                setHasVortex(false);
            }
        
        }
        
        else{
            return;}
        }
        
        
    
    
    
    
    if(!getWaitingToRoll()){
        
        //directional square doSomething deals with player direction when it is on a directional square
        if (checkFork(getX(), getY()) && !getOnDirSquare()){
           
            int newX = getX();
            int newY = getY();
            switch(getWorld()->getAction(m_playerNum)){
                case ACTION_UP:
                    if(getMoveDirection() == down){
                        return;}
                    if(getWorld()->notEmpty(newX, newY + SPRITE_HEIGHT)){
                            setMoveDirection(up);
                            setDirection(right);}
                    else{
                        return;}
                    break;
                case ACTION_DOWN:
                    if(getMoveDirection() == up){
                        return;}
                    if(getWorld()->notEmpty(newX, newY - SPRITE_HEIGHT)){
                        setMoveDirection(down);
                        setDirection(right);}
                    else{
                        return;}
                    break;
                case ACTION_LEFT:
                    if(getMoveDirection() == right){
                        return;}
                    if(getWorld()->notEmpty(newX - SPRITE_WIDTH, newY)){
                        setMoveDirection(left);
                        setDirection(left);
                    }
                    else{
                        return;}
                    break;
                case ACTION_RIGHT:
                    if(getMoveDirection() == left){
                        return;}
                    if(getWorld()->notEmpty(newX + SPRITE_WIDTH, newY)){
                        setMoveDirection(right);
                        setDirection(right);}
                    else{
                        return;}
                    break;
                default:
                    return;
            }
        }
        
        setOnDirSquare(false);
        
        
        
        int newX = getX();
        int newY = getY();
        
        getPositionInThisDirection(getMoveDirection(), SPRITE_WIDTH, newX, newY);
        if(!getWorld()->notEmpty(newX, newY)){
            findDirection();
        }
        //create move function with parameter direction
        move(getMoveDirection());
        setTicksToMove(getTicksToMove() - 1);
        if(getTicksToMove() == 0)
            setWaitingToRoll(true);
    }
 
  
}




Monster::Monster(int roll, StudentWorld* World, int imageID, double startX, double startY): MovingAvatar(World, imageID, startX, startY){
    m_rollNum = roll;
    m_pauseTicks = 180;
    m_isImpactable = true;
}

void Monster::doSomething(){
    Player* peachPointer = getWorld()->getPeach();
    Player* yoshiPointer = getWorld()->getYoshi();
    

    
    if(getBeingTeleported()){
        Actor* Square = getWorld()->getRandomSquare(getX(), getY());
        moveTo(Square->getX(), Square->getY());
        setWaitingToRoll(true);
        setDirection(0);
        setMoveDirection(0);
        setTicksToMove(0);
        setTicksOnSquare(0);
        m_pauseTicks = 180;
        setBeingTeleported(false);
    }
    
    if(getWaitingToRoll()){
       
        //if player lands on monster (spending more than one tick on the same square)
        if(peachPointer->landOrMoveOn(getX(), getY(), LAND)){
            monsterAction(peachPointer);}
        //if monster lands on player (spending more than one tick on the same square)
        if(this->landOrMoveOn(peachPointer->getX(),peachPointer->getY(), LAND)){
            monsterAction(peachPointer);}
        
        if(yoshiPointer->landOrMoveOn(getX(), getY(), LAND)){
            monsterAction(yoshiPointer);}
        if(landOrMoveOn(yoshiPointer->getX(), yoshiPointer->getY(), LAND)){
            monsterAction(yoshiPointer);}
        
        m_pauseTicks--;
        if(m_pauseTicks == 0){
            int roll = randInt(1, m_rollNum);
            setTicksToMove(roll * 8);
            findRandomDirection();
            setWaitingToRoll(false);
        }
    }
    
    
    
    if(!getWaitingToRoll()){
        setTicksOnSquare(0);
        if(checkFork(getX(), getY())){
            int currDir = getMoveDirection();
            int oppositeDirection = 1;
            while (oppositeDirection != 0) {        //Makes sure doesn't move back in same direction
                findRandomDirection();
                oppositeDirection = 0;
                switch (getMoveDirection()) {
                    case up:
                        if(currDir == down)
                            oppositeDirection++;
                        break;
                    case down:
                        if(currDir == up)
                            oppositeDirection++;
                        break;
                    case right:
                        if(currDir == left)
                            oppositeDirection++;
                        break;
                    case left:
                        if(currDir == right)
                            oppositeDirection++;
                        break;
                }
            }
        }
        
        int newX = getX();
        int newY = getY();
        
        getPositionInThisDirection(getMoveDirection(), SPRITE_WIDTH, newX, newY);
        if(!getWorld()->notEmpty(newX, newY)){
            findDirection();
        }
        
        move(getMoveDirection());
        setTicksToMove(getTicksToMove() - 1);
        if(getTicksToMove() == 0){
            setWaitingToRoll(true);
            m_pauseTicks = 180;
            ifMonsterLand();
        }
    }
    
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Boo::Boo(StudentWorld* World, int imageID, double startX, double startY):Monster(3, World, imageID, startX, startY){
    
}

void Boo::monsterAction(Player* player){
    int random = randInt(1, 2);
    int currCoinsPlayer = player->getCoins();
    int currCoinsPlayer2 = getWorld()->getOtherPlayer(player)->getCoins();
    int currStarsPlayer = player->getStars();
    int currStarsPlayer2 = getWorld()->getOtherPlayer(player)->getStars();
    
    
    switch(random){
        case 1:
            player->setCoins(currCoinsPlayer2);
            getWorld()->getOtherPlayer(player)->setCoins(currCoinsPlayer);
            break;
        case 2:
            player->setStars(currStarsPlayer2);
            getWorld()->getOtherPlayer(player)->setStars(currStarsPlayer);
            break;
    }
    getWorld()->playSound(SOUND_BOO_ACTIVATE);
}



Bowser::Bowser(StudentWorld* World, int imageID, double startX, double startY):Monster(10, World, imageID, startX, startY){
   
}


void Bowser::monsterAction(Player* player){
    
    int random = randInt(1, 2);
    int currCoinsPlayer = player->getCoins();
    
    if(random == 1){
        player->setCoins(currCoinsPlayer - currCoinsPlayer);
        getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
    }
    
    
}

void Bowser::ifMonsterLand(){
    int random = randInt(1, 4);
    if(random == 1){
        
        Actor* randSquare = getWorld()->squareOrImpactableAt(getX(), getY(), SQUARE);
        randSquare->setDead();
        Actor* droppingSquare = new DroppingSquare(getWorld(),IID_DROPPING_SQUARE, getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT);
        getWorld()->addActor(droppingSquare);
        getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


DirectionalSquare::DirectionalSquare(StudentWorld* World, int imageID, double startX, double startY, int direction):Square(World, imageID, startX, startY, direction){
    m_direction = direction;
}

void DirectionalSquare::landOnAction(Player* player){

    
    if(getWorld()->squareOrImpactableAt(player->getX(), player->getY(), SQUARE) == this){
  
        player->setOnDirSquare(true);
        switch(m_direction){
            case up:
                player->setMoveDirection(up);
                player->setDirection(right);
                break;
            case down:
                player->setMoveDirection(down);
                player->setDirection(right);
                break;
            case left:
                player->setMoveDirection(left);
                player->setDirection(left);
                break;
            case right:
                player->setMoveDirection(right);
                player->setDirection(right);
                break;
        }
    }
}

void DirectionalSquare::moveOnAction(Player* player){
    landOnAction(player);
}

EventSquare::EventSquare(StudentWorld* World, int imageID, double startX, double startY):Square(World,imageID, startX, startY, 0){
    
}

void EventSquare::landOnAction(Player* player){
    int random = randInt(1, 3);
    
    if(random == 1){
        player->setBeingTeleported(true);
        getWorld()->playSound(SOUND_PLAYER_TELEPORT);
    }
    if(random == 2){
        Player* otherPlayer = getWorld()->getOtherPlayer(player);
        int tempX = player->getX();
        int tempY = player->getY();
        int tempTicksMove = player->getTicksToMove();
        int tempTicksOnSquare = player->getTicksOnSquare();
        int tempMoveDir = player->getMoveDirection();
        int tempSpriteDir = player->getDirection();
        int tempWaitingRoll = player->getWaitingToRoll();
        
        player->moveTo(otherPlayer->getX(), otherPlayer->getY());
        player->setTicksToMove(otherPlayer->getTicksToMove());
        player->setTicksOnSquare(0);
        player->setMoveDirection(otherPlayer->getMoveDirection());
        player->setDirection(otherPlayer->getDirection());
        player->setWaitingToRoll(otherPlayer->getWaitingToRoll());
        
        otherPlayer->moveTo(tempX, tempY);
        otherPlayer->setTicksToMove(tempTicksMove);
        otherPlayer->setTicksOnSquare(tempTicksOnSquare);
        otherPlayer->setMoveDirection(tempMoveDir);
        otherPlayer->setDirection(tempSpriteDir);
        otherPlayer->setWaitingToRoll(tempWaitingRoll);
        getWorld()->playSound(SOUND_PLAYER_TELEPORT);
    }
    if(random == 3){
        player->setHasVortex(true);
        getWorld()->playSound(SOUND_GIVE_VORTEX);
    }
}



DroppingSquare::DroppingSquare(StudentWorld* World, int imageID, double startX, double startY):Square(World, imageID, startX, startY, 0){
  
    
}

void DroppingSquare::landOnAction(Player* player){
    int currCoinsPlayer = player->getCoins();
    int currStarsPlayer = player->getStars();
    
    int random = randInt(1, 2);
    if(random == 1){
        if(currCoinsPlayer >= 10){
            player->setCoins(currCoinsPlayer - 10);}
        else{
            player->setCoins(currCoinsPlayer - currCoinsPlayer);}
    }
    if(random == 2){
        if(currStarsPlayer > 0){
            player->setStars(currStarsPlayer - 1);
        }
    }
    getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
}





CoinSquare::CoinSquare(int grantAmount, StudentWorld* World, int imageID, double startX, double startY): Square(World, imageID, startX, startY, 0){
    m_grantAmount = grantAmount;
}

void CoinSquare::landOnAction(Player* player){
    int currCoinsPlayer = player->getCoins();
    
    if(getGrantAmount() < 0){
        if(player->getCoins() >= (getGrantAmount()*-1)){
            player->setCoins(currCoinsPlayer + getGrantAmount());}
        else{
            player->setCoins(currCoinsPlayer - currCoinsPlayer);
        }
        getWorld()->playSound(SOUND_TAKE_COIN);
    }
    
    if(getGrantAmount() > 0){
        player->setCoins(currCoinsPlayer + getGrantAmount());
        getWorld()->playSound(SOUND_GIVE_COIN);
    }
    
   
        
}
    



StarSquare::StarSquare(StudentWorld* World, int imageID, double startX, double startY):Square(World, imageID, startX, startY, 0){
}



void StarSquare::moveOnAction(Player* player){
    int currCoinsPlayer = player->getCoins();
    
    if(player->getCoins() >= 20){
        player->setCoins(currCoinsPlayer - 20);
        player->setStars(player->getStars() + 1);
        getWorld()->playSound(SOUND_GIVE_STAR);
    }
}

void StarSquare::landOnAction(Player* player){
    moveOnAction(player);
}



BankSquare::BankSquare(StudentWorld* World, int imageID, double startX, double startY): Square(World, imageID, startX, startY, 0){
  
}



void BankSquare::moveOnAction(Player* player){
    int currCoinsPlayer = player->getCoins();
    
    if(player->getCoins() < 5){
        player->setCoins(currCoinsPlayer - currCoinsPlayer);
        getWorld()->setBankBalance(getWorld()->getBankBalance() + currCoinsPlayer);}
    else{
        player->setCoins(currCoinsPlayer - 5);
        getWorld()->setBankBalance(getWorld()->getBankBalance() + 5);}
    
    getWorld()->playSound(SOUND_DEPOSIT_BANK);
}

void BankSquare::landOnAction(Player* player){
    player->setCoins((getWorld()->getBankBalance() + player->getCoins()));
    getWorld()->setBankBalance(0);
    getWorld()->playSound(SOUND_WITHDRAW_BANK);
}
 
