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

   Player player("MyScript");
   PythonPlayer pythonPlayer(&interpPython);

   player.SetupPlayer(&pythonPlayer);

   Action action = player.ChoseAction();
   std::cout << "Action: " << static_cast<int>(action) << std::endl;

   int code = 0;
   //std::cin >> code;
   interpPython.Uninitialize();
   return 0;
}