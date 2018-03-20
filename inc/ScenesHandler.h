/*
** ScenesHandler.h for ScenesHandler in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 02:17:10 2017 ju
** Last update Sun Jun 18 22:12:48 2017 ju
*/

#ifndef SCENESHANDLER_H_
# define SCENESHANDLER_H_

// TO REMOVE
#include <iostream>

# include <map>
# include <irrlicht.h>
# include "EventReceiver.h"
# include "MessagesHandler.h"
# include "CreditsScene.h"
# include "MainMenuScene.h"
# include "GameScene.h"
# include "OptionsScene.h"
# include "MapEditorScene.h"
# include "IntroScene.h"

# define SH_ERR_FROM ("Scenes Handler")
# define SH_ERR_MSGS ("Could not initialize messages handler")
# define SH_ERR_DEVICE ("Could not initialize device")
# define SH_ERR_CREATE ("Could not initialize a scene")
# define SH_ERR_RECEIVER ("Received an unknown event")

class					ScenesHandler
{
  irr::IrrlichtDevice			*device;
  std::map<std::string, IScene*>	scenes;
  MessagesHandler			*msgs_handler;
  EventReceiver				events;
  std::string				current;

  typedef IScene* (ScenesHandler::*initializer)() const;
  std::map<std::string, initializer>	initializers;

  typedef void (ScenesHandler::*event)(void*);
  std::map<std::string, event>		receivers;

public:
  ScenesHandler();
  ~ScenesHandler();

  // PUBLIC METHODS
  void					run();
  void					openScene(std::string const&);

private:
  // PRIVATE METHODS
  void					closeScene(std::string const&);
  void					setup();
  void					transition(void*);
  void					quit(void*);
  void					listenMessages();
  IScene*				createScene(std::string const&);
  IScene*				createMainMenu() const;
  IScene*				createCredits() const;
  IScene*				createGame() const;
  IScene*				createOptions() const;
  IScene*				createMapEditor() const;
  IScene*				createIntro() const;
};

#endif /* !SCENESHANDLER_H_ */
