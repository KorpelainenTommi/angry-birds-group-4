#include <Application.hpp>
#include <iostream>


///Entry point for the program
int main()
{
    std::cout << "Starting" << std::endl;
    Application app;
    std::cout << "App created" << std::endl;
    while(app.Loop());
    std::cout << "Exit" << std::endl;
    return 0;
}