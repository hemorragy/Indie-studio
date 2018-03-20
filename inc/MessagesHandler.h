/*
** MessagesHandler.h for MessagesHandler in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 14:39:24 2017 ju
** Last update Tue Jun 13 00:42:39 2017 ju
*/

#ifndef MESSAGESHANDLER_H_
# define MESSAGESHANDLER_H_

# include <list>
# include "Message.h"

class			MessagesHandler
{
  typedef std::list<Message const*> t_msgs;
  t_msgs		msgs;

public:
  MessagesHandler();
  ~MessagesHandler();

  t_msgs&		all();
  void			send(Message const*);
};

#endif /* !MESSAGESHANDLER_H_ */
