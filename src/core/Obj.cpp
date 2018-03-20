/*
** Obj.cpp for Obj in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 04:20:52 2017 ju
** Last update Sun Jun 18 00:25:48 2017 ju
*/

#include "Obj.h"

Obj::Obj(irr::IrrlichtDevice *device,
	 MessagesHandler *messager): device(device),
				     messager(messager),
				     now(device->getTimer()->getTime())
{
}

Obj::~Obj()
{
}

/**
 * PROTECTED METHODS
 */

irr::f32		Obj::getFrameDelta()
{
  const irr::u32	now = this->device->getTimer()->getTime();
  const irr::f32	delta = (irr::f32)(now - this->now) / 1000.f;

  this->now = now;
  return (delta);
}

irr::scene::ISceneManager*	Obj::getSmgr() const
{
  return (this->device->getSceneManager());
}

irr::video::IVideoDriver*	Obj::getDriver() const
{
  return (this->device->getVideoDriver());
}

irr::IrrlichtDevice*		Obj::getDevice() const
{
  return (this->device);
}

MessagesHandler*		Obj::getMessager() const
{
  return (this->messager);
}
