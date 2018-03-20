/*
** ScenesHandler.cpp for ScenesHandler in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 02:17:28 2017 ju
** Last update Sun Jun 18 23:26:36 2017 Eddy Chouikha
*/

#include "ScenesHandler.h"

ScenesHandler::ScenesHandler()
{
  if (!(this->device = irr::createDevice(irr::video::EDT_SOFTWARE,
					 irr::core::dimension2d<irr::u32>(1920, 1080),
					 16, true, false, false, &this->events)))
    throw RuntimeError(SH_ERR_FROM, SH_ERR_DEVICE);
  this->device->setWindowCaption(L"Neo Bomberman");
  if (!(this->msgs_handler = new MessagesHandler))
    throw RuntimeError(SH_ERR_FROM, SH_ERR_MSGS);
  this->setup();
}

ScenesHandler::~ScenesHandler()
{
  if (this->device)
    this->device->drop();
}

/**
 * PUBLIC METHODS
 */

void	ScenesHandler::run()
{
  while(this->device->run())
    {
      this->listenMessages();
      this->scenes[this->current]->run();
      this->device->getVideoDriver()->beginScene(true, true, irr::video::SColor(255, 20, 20, 20));
      this->device->getSceneManager()->drawAll();
      this->device->getGUIEnvironment()->drawAll();
      this->device->getVideoDriver()->endScene();
    }
}

void		ScenesHandler::openScene(std::string const &name)
{
  IScene	*scene;

  this->events.setEnabled(false);
  this->closeScene(this->current);
  if (!(scene = this->scenes[name]))
    this->scenes[name] = this->createScene(name);
  scene = this->scenes[name];
  scene->load();
  this->current = name;
  this->events.setEnabled(true);
}

/**
 * PRIVATE METHODS
 */

void		ScenesHandler::closeScene(std::string const &name)
{
  IScene	*scene;

  if ((scene = this->scenes[name]))
    scene->unload();
}

void	ScenesHandler::quit(void *data)
{
  (void)data;
  this->events.setEnabled(false);
  this->device->closeDevice();
}

void		ScenesHandler::transition(void *data)
{
  std::string	*name = static_cast<std::string*>(data);

  this->openScene(*name);
}

void					ScenesHandler::listenMessages()
{
  std::list<Message const*>::iterator	itr;
  Message const				*msg;
  std::list<Message const*>		&list = this->msgs_handler->all();

  itr = list.begin();
  while (itr != list.end())
    {
      msg = *itr;
      if (msg->getCategory() == "_Root")
	{
	  if (!this->receivers[msg->getAction()])
	    throw RuntimeError(SH_ERR_FROM, SH_ERR_RECEIVER);
	  (*this.*(this->receivers[msg->getAction()]))(msg->getData());
	  itr = list.erase(itr);
	}
      else
	++itr;
    }
}

void	ScenesHandler::setup()
{
  this->initializers["MainMenu"] = &ScenesHandler::createMainMenu;
  this->initializers["Credits"] = &ScenesHandler::createCredits;
  this->initializers["Game"] = &ScenesHandler::createGame;
  this->initializers["Options"] = &ScenesHandler::createOptions;
  this->initializers["MapEditor"] = &ScenesHandler::createMapEditor;
  this->initializers["Intro"] = &ScenesHandler::createIntro;
  this->receivers["quit"] = &ScenesHandler::quit;
  this->receivers["transition"] = &ScenesHandler::transition;
}

IScene*		ScenesHandler::createScene(std::string const &name)
{
  IScene	*scene;

  if (!(scene = (*this.*(this->initializers[name]))()))
    throw RuntimeError(SH_ERR_FROM, SH_ERR_CREATE);
  scene->setEvents(&events);
  scene->setMessager(this->msgs_handler);
  scene->setDevice(this->device);
  return (scene);
}

IScene*	ScenesHandler::createMainMenu() const
{
  return (new MainMenuScene);
}

IScene*	ScenesHandler::createCredits() const
{
  return (new CreditsScene);
}

IScene*	ScenesHandler::createGame() const
{
  return (new GameScene);
}

IScene*	ScenesHandler::createOptions() const
{
  return (new OptionsScene);
}

IScene*	ScenesHandler::createMapEditor() const
{
  return (new MapEditorScene);
}

IScene*	ScenesHandler::createIntro() const
{
  return (new IntroScene);
}
