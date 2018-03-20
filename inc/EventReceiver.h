/*
** EventReceiver.h for EventReceiver in /home/ju/irrlicht/examples/04.Movement
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 15:46:59 2017 ju
** Last update Tue Jun 13 00:57:05 2017 ju
*/

#ifndef EVENTRECEIVER_H_
# define EVENTRECEIVER_H_

# include <irrlicht.h>

class		EventReceiver: public irr::IEventReceiver
{
  bool		enabled;
  bool		keys_down[irr::KEY_KEY_CODES_COUNT];

public:
  EventReceiver();
  void		setEnabled(bool);
  virtual bool	OnEvent(const irr::SEvent&);
  virtual bool	isPressed(irr::EKEY_CODE) const;
};


#endif /* !EVENTRECEIVER_H_ */
