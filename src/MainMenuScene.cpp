/*
** MainMenuScene.cpp for MainMenuScene in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Thu May 18 17:25:26 2017 ju
** Last update Sun Jun 18 23:47:01 2017 Eddy Chouikha
*/

#include "ScenesHandler.h"
#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(): Scene()
{
}

MainMenuScene::~MainMenuScene()
{

}

/**
 * PUBLIC METHODS
 */

void				MainMenuScene::load()
{
  this->background = this->getGUI()->addImage(this->getDriver()->getTexture("media/img/menuBackground.png"),
                                              irr::core::position2d<irr::s32>(0,0),
					      true, 0, -1, 0);
}

void			MainMenuScene::run()
{
  if (this->getEvents()->isPressed(irr::KEY_ESCAPE))
    this->quit();
  else if (this->getEvents()->isPressed(irr::KEY_KEY_C))
    this->go("Credits");
  else if (this->getEvents()->isPressed(irr::KEY_KEY_G))
    this->go("Game");
  else if (this->getEvents()->isPressed(irr::KEY_KEY_O))
    this->go("Options");
  else if (this->getEvents()->isPressed(irr::KEY_KEY_M))
    this->go("MapEditor");
}

void				MainMenuScene::unload()
{
  this->background->remove();
}
