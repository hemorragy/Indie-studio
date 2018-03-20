/*
** Bomb.cpp for Bomb in /home/ju/tek/cpp/cpp_indie_studio
**
** Made by ju
** Login   <ju@ju-virtual>
**
** Started on  Sat Jun 17 04:32:01 2017 ju
** Last update Sun Jun 18 21:22:12 2017 ju
*/

#include "Bomb.h"

Bomb::Bomb(irr::core::vector3df playerPosition,
	   irr::IrrlichtDevice *device,
	   MessagesHandler *messager): Obj(device, messager),
				       _playerPosition(playerPosition),
				       _range(1),
				       _duration(3)
{
}

Bomb::~Bomb()
{
}

/**
 * PUBLIC METHODS
 */

void					Bomb::load()
{
  irr::video::IVideoDriver		*driver = this->getDriver();
  irr::scene::ISceneManager		*smgr = this->getSmgr();
  irr::scene::IAnimatedMesh		*mesh;
  irr::scene::IAnimatedMeshSceneNode	*node;

  this->_startedAt = this->getDevice()->getTimer()->getTime();
  if (!(mesh = smgr->getMesh("./media/bomb/FireBomb/Bomb.obj")))
    throw RuntimeError("Media", "Missing Sydney");
  if (!(node = smgr->addAnimatedMeshSceneNode(mesh)))
    throw RuntimeError("Node", "Could not create node");
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
  node->setPosition(this->_playerPosition);
  if (!driver->getTexture("./media/bomb/FireBomb/texture.png"))
    throw RuntimeError("Media", "Could not load texture of sydney");
  node->setMaterialTexture(0, driver->getTexture("./media/bomb/FireBomb/texture.png"));
  this->node = node;
}

void		Bomb::update(EventReceiver const &events)
{
  (void)events;
  if (this->getDevice()->getTimer()->getTime() >
      (this->_startedAt + this->_duration * 1000))
  {
    this->_startedAt = 0;
    this->explode();
  }
}

void		Bomb::unload()
{
  this->node->remove();
  delete this;
}

irr::scene::ISceneNode	*Bomb::getNode()
{
  return (this->node);
}

irr::scene::IMesh	*Bomb::getMesh()
{
  return (this->node->getMesh());
}

unsigned int		Bomb::getRange() const
{
  return (this->_range);
}

Player*			Bomb::getPlayer() const
{
  return (this->_player);
}

void			Bomb::setPlayer(Player *player)
{
  this->_player = player;
}

void		Bomb::explode()
{
  std::cout << "Hallah Akbah" << std::endl;
  this->getMessager()->send(new Message("GameExplode", "Bomb", this));
}
