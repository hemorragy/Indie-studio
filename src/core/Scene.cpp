/*
** Scene.cpp for Scene in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 02:22:58 2017 ju
** Last update Sat Jun 17 07:21:41 2017 ju
*/

#include <iostream>
#include "Scene.h"

Scene::Scene(): now(0)
{
}

Scene::~Scene()
{
}

/**
 * PUBLIC METHODS
 */

void	Scene::setDevice(irr::IrrlichtDevice *device)
{
  this->device = device;
  this->now = this->device->getTimer()->getTime();
}

void	Scene::setEvents(EventReceiver const *events)
{
  this->events = events;
}

void	Scene::setMessager(MessagesHandler *handler)
{
  this->messager = handler;
}

/**
 * PROTECTED METHODS
 */

irr::f32		Scene::getFrameDelta()
{
  const irr::u32	now = this->device->getTimer()->getTime();
  const irr::f32	delta = (irr::f32)(now - this->now) / 1000.f;

  this->now = now;
  return (delta);
}

void	Scene::quit()
{
  this->messager->send(new Message("_Root",
				   "quit",
				   NULL));
}

void	Scene::go(std::string const &dest)
{
  this->messager->send(new Message("_Root",
				   "transition",
				   new std::string(dest)));
}

MessagesHandler*	Scene::getMessager() const
{
  return (this->messager);
}

EventReceiver const*	Scene::getEvents() const
{
  return (this->events);
}

irr::IrrlichtDevice*	Scene::getDevice() const
{
  return (this->device);
}

irr::video::IVideoDriver*	Scene::getDriver() const
{
  return (this->device->getVideoDriver());
}

irr::scene::ISceneManager*	Scene::getSmgr() const
{
  return (this->device->getSceneManager());
}

irr::gui::IGUIEnvironment*	Scene::getGUI() const
{
  return (this->device->getGUIEnvironment());
}
