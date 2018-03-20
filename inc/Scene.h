/*
** Scene.h for Scene in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 02:24:50 2017 ju
** Last update Sat Jun 17 02:03:57 2017 ju
*/

#ifndef SCENE_H_
# define SCENE_H_

# include "IScene.h"
# include "RuntimeError.h"

# define S_ERR_FROM ("Scene")

class				Scene: public IScene
{
private:
  irr::u32			now;
  irr::IrrlichtDevice		*device;
  EventReceiver const		*events;
  MessagesHandler		*messager;

public:
  Scene();
  virtual ~Scene();

  // PUBLIC METHODS
  virtual void			load() = 0;
  virtual void			run() = 0;
  virtual void			unload() = 0;
  void				setDevice(irr::IrrlichtDevice*);
  void				setEvents(EventReceiver const *);
  void				setMessager(MessagesHandler*);
protected:
  // PROTECTED METHODS
  irr::f32			getFrameDelta();
  void				quit();
  void				go(std::string const&);
  MessagesHandler*		getMessager() const;
  EventReceiver const*		getEvents() const;
  irr::IrrlichtDevice*		getDevice() const;
  irr::video::IVideoDriver*	getDriver() const;
  irr::scene::ISceneManager*	getSmgr() const;
  irr::gui::IGUIEnvironment*	getGUI() const;
};

#endif /* !SCENE_H_ */
