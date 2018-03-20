/*
** RuntimeError.cpp for RuntimeError in /home/ju/tek/cpp/arcade
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Thu Apr  6 15:24:11 2017 ju
** Last update Mon Apr 24 18:38:29 2017 ju
*/

#include "RuntimeError.h"

RuntimeError::RuntimeError(std::string const &err,
			   std::string const &quote) throw()
{
  this->full = err;
  if (quote != "")
    this->full += ": " + quote;
}

RuntimeError::~RuntimeError() throw()
{
}

const char*		RuntimeError::what() const throw()
{
  return (this->full.c_str());
}
