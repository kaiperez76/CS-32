#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;



GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}



StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_bankBalance = 0;
    
}

StudentWorld::~StudentWorld(){
    cleanUp();
}



int StudentWorld::init()
{
   
    
    string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
    Board::LoadResult result = m_bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found || result == Board::load_fail_bad_format)
        return GWSTATUS_BOARD_ERROR;
    
    
    for(int y = 0; y < BOARD_WIDTH; y++){
        for(int x = 0; x < BOARD_HEIGHT; x++){
            Board::GridEntry ge = m_bd.getContentsOf(x,y);
            switch (ge){
                case Board::empty:
                    break;
                case Board::player:
                    m_peach = new Player(this, 1, IID_PEACH, x, y);
                    m_actors.push_back(m_peach);
                    m_yoshi = new Player(this, 2, IID_YOSHI, x, y);
                    m_actors.push_back(m_yoshi);
                    m_actors.push_back(new CoinSquare(3, this, IID_BLUE_COIN_SQUARE, x, y));
                    break;
                case Board::blue_coin_square:
                    m_actors.push_back(new CoinSquare(3, this, IID_BLUE_COIN_SQUARE, x, y));
                    break;
                case Board::red_coin_square:        //how do I ensure different coinsquares act differently
                    m_actors.push_back(new CoinSquare(-3, this, IID_RED_COIN_SQUARE, x, y));
                    break;
                case Board::up_dir_square:
                    m_actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, x, y, 90));
                    break;
                case Board::down_dir_square:
                    m_actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, x, y, 270));
                    break;
                case Board::left_dir_square:
                    m_actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, x, y, 180));
                    break;
                case Board::right_dir_square:
                    m_actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, x, y, 0));
                    break;
                case Board::event_square:
                    m_actors.push_back(new EventSquare(this, IID_EVENT_SQUARE, x, y));
                    break;
                case Board::bank_square:
                    m_actors.push_back(new BankSquare(this, IID_BANK_SQUARE, x, y));
                    break;
                case Board::star_square:
                    m_actors.push_back(new StarSquare(this, IID_STAR_SQUARE, x, y));
                    break;
                case Board::bowser:
                    m_actors.push_back(new Bowser(this, IID_BOWSER, x, y));
                    m_actors.push_back(new CoinSquare(3, this, IID_BLUE_COIN_SQUARE, x, y));
                    break;
                case Board::boo:
                    m_actors.push_back(new Boo(this, IID_BOO, x, y));
                    m_actors.push_back(new CoinSquare(3, this, IID_BLUE_COIN_SQUARE, x, y));
                    break;
            }
        }
    }

    
	startCountdownTimer(99);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    //deciding game winner setting final stats and returning
    if (timeRemaining() <= 0){
        playSound(SOUND_GAME_FINISHED);
        if(m_peach->getStars() > m_yoshi->getStars()){
            setFinalScore(m_peach->getStars(), m_peach->getCoins());
            return GWSTATUS_PEACH_WON;
        }
        if(m_peach->getStars() < m_yoshi->getStars()){
            setFinalScore(m_yoshi->getStars(), m_yoshi->getCoins());
            return GWSTATUS_YOSHI_WON;
        }
        if(m_peach->getStars() == m_yoshi->getStars()){
            if(m_peach->getCoins() > m_yoshi->getCoins()){
                setFinalScore(m_peach->getStars(), m_peach->getCoins());
                return GWSTATUS_PEACH_WON;}
            if(m_peach->getCoins() < m_yoshi->getCoins()){
                setFinalScore(m_yoshi->getStars(), m_yoshi->getCoins());
                return GWSTATUS_YOSHI_WON;}
            if(m_peach->getCoins() == m_yoshi->getCoins()){
                int winner = randInt(1,2);
                if(winner == 1){
                    setFinalScore(m_peach->getStars(), m_peach->getCoins());
                    return GWSTATUS_PEACH_WON;}
                if(winner == 2){
                    setFinalScore(m_yoshi->getStars(), m_yoshi->getCoins());
                    return GWSTATUS_YOSHI_WON;}
                }
            }
        }
    
        
 
    
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    

   while(it != m_actors.end()){
       if((*it)->getAlive()){
            (*it)->doSomething();
            it++;
        }
        else{
            delete *it;
            it = m_actors.erase(it);
        }
    }
    
    
    
    
    
    
   
    ostringstream gameText;
    gameText << "P1 Roll: " << getPeach()->getCurrRoll() <<" Stars: " << getPeach()->getStars();
    gameText << " $$: " << getPeach()->getCoins();
    if(getPeach()->getHasVortex()){
        gameText << " VOR";}
    gameText << " | Time: " << timeRemaining() << " | Bank: " << getBankBalance() << " | ";
    gameText << "P2 Roll: " << getYoshi()->getCurrRoll() <<" Stars: " << getYoshi()->getStars();
    gameText << " $$: " << getYoshi()->getCoins();
    if(getYoshi()->getHasVortex()){
        gameText << " VOR";}
    setGameStatText(gameText.str());
    
    
    
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    
    
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    
    while(it != m_actors.end()){
            delete *it;
            it = m_actors.erase(it);
        }
       
        
    
    
}





bool StudentWorld::notEmpty(int x, int y) const{
    
    vector<Actor*>::const_iterator it;
    it = m_actors.cbegin();
    if((x % SPRITE_WIDTH) == 0 && (y % SPRITE_HEIGHT) == 0){
        while(it != m_actors.cend()){
            if((*it)->getX() == (x) && (*it)->getY() == (y)){
                return true;}
            it++;
        }
        return false;
    }
    
    
    return true;
    
}


void StudentWorld::addActor(Actor* actor){
    m_actors.push_back(actor);
}



Actor* StudentWorld::squareOrImpactableAt(int x, int y, int squareOrImpactable) const{
    
    vector<Actor*>::const_iterator it;
    it = m_actors.cbegin();
    while(it != m_actors.cend()){
        if((*it)->getIsASquare() && (*it)->getX() == x && (*it)->getY() == y && squareOrImpactable == SQUARE){
            return *it;}
        if((*it)->getIsImpactable() && (*it)->getX() == x && (*it)->getY() == y && squareOrImpactable == IMPACTABLE){
            return *it;}
        it++;
    }
    
    
    return nullptr;
}





Actor* StudentWorld::getRandomSquare(int x, int y) const{
    int sizeVec = static_cast<int>(m_actors.size()) - 1;
    
    for(;;){
        int random = randInt(0, sizeVec);
        if(m_actors[random]->getX() != x && m_actors[random]->getY() != y && m_actors[random]->getIsASquare()){
            return m_actors[random];}
        
    }
    
    return nullptr;
}

Player* StudentWorld::getOtherPlayer(Player* player) const{
    if(player == getPeach()){
        return getYoshi();
    }
    return getPeach();
    
}



