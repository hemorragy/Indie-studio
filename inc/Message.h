/*
** Message.h for Message in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 14:57:59 2017 ju
** Last update Wed May 17 14:58:15 2017 ju
*/

#ifndef MESSAGE_H_
# define MESSAGE_H_

# include <string>

class			Message
{
  std::string		category;
  std::string		action;
  void			*data;

public:
  Message(std::string const&,
	  std::string const&,
	  void*);
  ~Message();
  // PUBLIC METHODS
  std::string const&	getCategory() const;
  std::string const&	getAction() const;
  void*			getData() const;
};

#endif /* !MESSAGE_H_ */
