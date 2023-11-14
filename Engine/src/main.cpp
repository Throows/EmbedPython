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

#include "Application.hpp"

int main(int argc, char **argv)
{
   std::cout << "------ EmbedPython ------" << std::endl;

   std::filesystem::path exePath = argv[0];
   std::filesystem::current_path(exePath.parent_path());
   std::string scriptPath = std::filesystem::current_path().native() + "/scripts";
   
   Application app(scriptPath.c_str());
   app.Initialize();
   app.Run();

   std::cout << "------ End of EmbedPython ------" << std::endl;
   return 0;
}