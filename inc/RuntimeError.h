/*
** RuntimeError.h for RuntimeError in /home/ju/tek/cpp/arcade
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Thu Apr  6 15:03:58 2017 ju
** Last update Mon Apr 24 18:38:40 2017 ju
*/

#ifndef RUNTIMEERROR_H_
# define RUNTIMEERROR_H_

# include <exception>
# include <string>

class		RuntimeError: public std::exception
{
  std::string	full;

public:
  // CONSTRUCTION
  RuntimeError(std::string const&, std::string const& = "") throw();
  virtual ~RuntimeError() throw();
  // METHODS
  virtual const char*	what() const throw();
};

#endif /* !RUNTIMEERROR_H_ */
