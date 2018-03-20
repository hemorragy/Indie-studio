/*
** Obj.h for Obj in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 04:17:20 2017 ju
** Last update Sun Jun 18 19:31:02 2017 Chai Bittan
*/

#ifndef OBJ_H_
# define OBJ_H_

# include "IObj.h"

class				Obj: public IObj
{
  irr::IrrlichtDevice		*device;
  MessagesHandler		*messager;
  irr::u32			now;

public:
  Obj(irr::IrrlichtDevice*, MessagesHandler*);
  virtual ~Obj();
  // PUBLIC METHODS
  virtual void			load() = 0;
  virtual void			update(EventReceiver const&) = 0;
  virtual void			unload() = 0;
  virtual irr::scene::ISceneNode	*getNode() = 0;
  virtual irr::scene::IMesh		*getMesh() = 0;
  // PROTECTED METHODS
protected:
  irr::f32			getFrameDelta();
  irr::scene::ISceneManager*	getSmgr() const;
  irr::video::IVideoDriver*	getDriver() const;
  irr::IrrlichtDevice*		getDevice() const;
  MessagesHandler*		getMessager() const;
};

#endif /* !OBJ_H_ */
