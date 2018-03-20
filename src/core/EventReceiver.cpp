/*
** EventReceiver.cpp for EventReceiver in /home/ju/irrlicht/examples/04.Movement
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Wed May 17 15:46:44 2017 ju
** Last update Sat Jun 17 06:07:15 2017 ju
*/

#include "EventReceiver.h"

EventReceiver::EventReceiver(): enabled(true)
{
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    this->keys_down[i] = false;
}

void	EventReceiver::setEnabled(bool enabled)
{
  this->enabled = enabled;
}

bool	EventReceiver::OnEvent(irr::SEvent const &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    this->keys_down[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return false;
}

bool	EventReceiver::isPressed(irr::EKEY_CODE keyCode) const
{
  return (this->enabled && this->keys_down[keyCode]);
}
