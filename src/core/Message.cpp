/*
** Message.cpp for Message in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 14:58:21 2017 ju
** Last update Wed May 17 15:05:26 2017 ju
*/

#include "Message.h"

Message::Message(std::string const &category,
		 std::string const &action,
		 void *data): category(category),
			      action(action),
			      data(data)
{
}

Message::~Message()
{
}

/**
 * PUBLIC METHODS
 */
std::string const&	Message::getCategory() const
{
  return this->category;
}

std::string const&	Message::getAction() const
{
  return this->action;
}

void*			Message::getData() const
{
  return this->data;
}
