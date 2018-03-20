/*
** OptionsScene.cpp for OptionsScene in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 21:22:37 2017 ju
** Last update Sun Jun 18 23:33:36 2017 Eddy Chouikha
*/

#include "OptionsScene.h"
#include <iostream>

OptionsScene::OptionsScene()
{
}

OptionsScene::~OptionsScene()
{
}

/**
 * PUBLIC METHODS
 */

void				OptionsScene::load()
{
  irr::core::dimension2d<irr::u32>	screenSize;

  screenSize = this->getDriver()->getScreenSize();
  this->background = this->getGUI()->addImage(this->getDriver()->getTexture("media/img/menuBackground.jpg"),
					      irr::core::position2d<irr::s32>(0,0),
				       true, 0, -1, 0);
  this->logo = this->getGUI()->addImage(this->getDriver()->getTexture("media/img/bomberman-title.png"),
				       irr::core::position2d<irr::s32>((screenSize.Width / 2) - 500, 0),
				       true, 0, -1, 0);
  this->box1 = this->getGUI()->addEditBox(L"Name of Player 1",
					  irr::core::rect<irr::s32>((screenSize.Width / 5) * 1,
								    (screenSize.Height / 5) * 3,
								    (screenSize.Width / 5) * 2,
								    (screenSize.Height / 5) * 4),
					  true, 0, -2);
  this->box2 = this->getGUI()->addEditBox(L"Name of Player 2",
					  irr::core::rect<irr::s32>((screenSize.Width / 5) * 3,
								    (screenSize.Height / 5) * 3,
								    (screenSize.Width / 5) * 4,
								    (screenSize.Height / 5) * 4),
					  true, 0, -1);
  this->player1 = box1->getText();
  this->player2 = box2->getText();
}

void	OptionsScene::run()
{
  if (this->getEvents()->isPressed(irr::KEY_ESCAPE))
    this->quit();
  else if (this->getEvents()->isPressed(irr::KEY_KEY_G))
    {
      std::wstring ws(this->player1);
      std::wstring ws2(this->player2);
      this->getMessager()->send(new Message("GameNames", std::string(ws.begin(), ws.end()),
					    new std::string(std::string(ws2.begin(), ws2.end()))));
      this->go("Game");
    }
}

void	OptionsScene::unload()
{
  if (this->box1 && this->box2)
    {
      this->box1->remove();
      this->box2->remove();
      this->background->remove();
      this->logo->remove();
    }
}
