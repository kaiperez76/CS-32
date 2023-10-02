//
//  Game.h
//  Project 1(CS 32)
//
//  Created by Kai Perez on 1/11/23.
//

#ifndef Game_h
#define Game_h

#include <string>
using namespace std;


class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Rabbit declaration.


class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      //Helper functions
    string takePlayerTurn();
};


#endif /* Game_h */
