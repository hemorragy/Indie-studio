/*
** MessagesHandler.cpp for MessagesHandler in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 14:38:36 2017 ju
** Last update Sat Jun 17 22:48:45 2017 ju
*/

#include "MessagesHandler.h"

MessagesHandler::MessagesHandler()
{

}

MessagesHandler::~MessagesHandler()
{

}

/**
 * PUBLIC METHODS
 */

void	MessagesHandler::send(Message const *msg)
{
  if (msg)
    this->msgs.push_back(msg);
}

MessagesHandler::t_msgs&	MessagesHandler::all()
{
  return this->msgs;
}
