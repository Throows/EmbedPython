/* ----------------------------------------------------------------------- */
// Author  :  Romain Berthoule
// Date    :  22/10/2023
// Project :  EmbedPython
// File    :  main.cpp (clang14.0.3)
// Desc    :  This is the entry point file 
/* ----------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include "PythonPlayer.hpp"
#include "Player.hpp"

int main(int argc, char **argv)
{
   std::cout << "------ EmbedPython ------" << std::endl;

   std::filesystem::path exePath = argv[0];
   std::filesystem::current_path(exePath.parent_path());
   std::string scriptPath = std::filesystem::current_path().native() + "/scripts";
   
   PyInterpreter interpPython = PyInterpreter(scriptPath.c_str());
   interpPython.Initialize();

   Player playerOne("PlayerOne");
   Player playerTwo("PlayerTwo");
   PythonPlayer pythonPlayer;

   playerOne.SetupPlayer(&pythonPlayer);
   playerTwo.SetupPlayer(&pythonPlayer);

   while (playerOne.GetHealth() > 0 && playerTwo.GetHealth() > 0) {
      Action actionOne = playerOne.ChoseAction();
      playerOne.Play(actionOne, &playerTwo);
      Action actionTwo = playerTwo.ChoseAction();
      playerTwo.Play(actionTwo, &playerOne);
   }

   if (playerOne.GetHealth() <= 0) {
      std::cout << "Player " << playerTwo.GetName() << " won ! (HP: " << playerTwo.GetHealth() << ")" << std::endl;
   } else {
      std::cout << "Player " << playerOne.GetName() << " won ! (HP: " << playerOne.GetHealth() << ")" << std::endl;
   }

   std::cout << "------ End of EmbedPython ------" << std::endl;

   interpPython.Uninitialize();
   return 0;
}