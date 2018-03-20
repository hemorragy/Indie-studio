/*
** IObj.h for IObj in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 04:43:42 2017 ju
** Last update Sun Jun 18 19:31:10 2017 Chai Bittan
*/

#ifndef IOBJ_H_
# define IOBJ_H_

# include <irrlicht.h>
# include "EventReceiver.h"
# include "MessagesHandler.h"

class					IObj
{
public:
  ~IObj(){}
  // PUBLIC METHODS
  virtual void				load() = 0;
  virtual void				update(EventReceiver const&) = 0;
  virtual void				unload() = 0;
  virtual irr::scene::ISceneNode	*getNode() = 0;
  virtual irr::scene::IMesh		*getMesh() = 0;
  // PROTECTED METHODS
protected:
  virtual irr::f32			getFrameDelta() = 0;
  virtual irr::scene::ISceneManager*	getSmgr() const = 0;
  virtual irr::video::IVideoDriver*	getDriver() const = 0;
  virtual irr::IrrlichtDevice*		getDevice() const = 0;
  virtual MessagesHandler*		getMessager() const = 0;
};

#endif /* !IOBJ_H_ */
