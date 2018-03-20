/*
** IScene.h for IScene in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 02:20:01 2017 ju
** Last update Thu Jun  1 15:57:15 2017 ju
*/

#ifndef ISCENE_H_
# define ISCENE_H_

# include <irrlicht.h>
# include "MessagesHandler.h"
# include "EventReceiver.h"

class					IScene
{
public:
  virtual ~IScene() {}

  // PUBLIC METHODS
  virtual void				load() = 0;
  virtual void				run() = 0;
  virtual void				unload() = 0;
  virtual void				setDevice(irr::IrrlichtDevice*) = 0;
  virtual void				setEvents(EventReceiver const *) = 0;
  virtual void				setMessager(MessagesHandler*) = 0;
protected:
  // PROTECTED METHODS
  MessagesHandler*			getMessager() const;
  EventReceiver const*			getEvents() const;
  irr::IrrlichtDevice*			getDevice() const;
  virtual irr::video::IVideoDriver*	getDriver() const = 0;
  virtual irr::scene::ISceneManager*	getSmgr() const = 0;
  virtual irr::gui::IGUIEnvironment*	getGUI() const = 0;
};

#endif /* !ISCENE_H_ */
