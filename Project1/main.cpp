//
//  main.cpp
//  Project 1(CS 32)
//
//  Created by Kai Perez on 1/11/23.
//

// rabbits.cpp

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>

#include "globals.h"
#include "Arena.h"
#include "Rabbit.h"
#include "Game.h"

using namespace std;





int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(3, 5, 2);

      // Play the game
    g.play();
}


