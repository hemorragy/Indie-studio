/*
** IntroScene.cpp for IntroScene in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sun Jun 18 22:08:34 2017 ju
** Last update Sun Jun 18 23:34:50 2017 Eddy Chouikha
*/

#include <iostream>
#include "IntroScene.h"
#include "../inc/Score.h"

IntroScene::IntroScene(): Scene(),
			  duration(3)
{
}

IntroScene::~IntroScene()
{

}

/**
 * PUBLIC METHODS
 */

void				IntroScene::load()
{
  this->background = this->getGUI()->addImage(this->getDriver()->getTexture("media/img/intro.jpg"),
					      irr::core::position2d<irr::s32>(0,0),
					      true, 0, -1, 0);
  this->startedAt = this->getDevice()->getTimer()->getTime();
}

void		IntroScene::run()
{
  irr::u32	now;

  if (this->getEvents()->isPressed(irr::KEY_ESCAPE))
    this->quit();
  now = this->getDevice()->getTimer()->getTime();
  if ((this->startedAt + this->duration * 1000) < now)
    this->go("MainMenu");
}

void	IntroScene::unload()
{
  this->background->remove();
}
