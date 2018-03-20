/*
** Credits.cpp for Credits in /home/ju/tek/cpp/bomber
**
** Made by ju
** Login   <ju@ju-virtual>
**
** Started on  Wed May 17 03:00:00 2017 ju
** Last update Mon Jun 19 01:27:11 2017 Chai Bittan
*/

#include <iostream>
#include "CreditsScene.h"
#include "../inc/Score.h"

CreditsScene::CreditsScene(): Scene()
{
}

CreditsScene::~CreditsScene()
{

}

/**
 * PUBLIC METHODS
 */

void				CreditsScene::load()
{
  Score score;

  score.printScore(this->getDevice());
}

void	CreditsScene::run()
{
  if (this->getEvents()->isPressed(irr::KEY_ESCAPE))
    this->quit();
}

void	CreditsScene::unload()
{
  //test.unprintScore();
}

void    CreditsScene::callFunc(std::string playerName, int score)
{
  Score test;
  test.add(this->getDevice(), playerName, score);

}

/**
 * PRIVATE METHODS
 */
