/*
1;2802;0c** main.cpp for indie in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@epitech.net>
** 
** Started on  Wed May 17 02:04:00 2017 ju
** Last update Sun Jun 18 22:11:36 2017 ju
*/

#include <iostream>
#include "ScenesHandler.h"

int		main()
{
  ScenesHandler	handler;

  srand(time(NULL));
  try {
    handler.openScene("Intro");
    handler.run();
  } catch (RuntimeError &e) {
    std::cerr << "[Fatal Error] " << e.what() << std::endl;
    return (1);
  }
  return (0);
}
