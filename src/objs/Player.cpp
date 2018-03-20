/*
** Player.cpp for Player in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 04:32:01 2017 ju
** Last update Sun Jun 18 20:48:02 2017 ju
*/

#include "Player.h"

Player::Player(irr::core::vector3df pos,
	       irr::IrrlichtDevice *device,
	       MessagesHandler *messager): Obj(device, messager),
					   speed(5),
					   dropCooldown(3),
					   droppedAt(0),
					   name(""),
					   initialPos(pos)
{
}

Player::~Player()
{
}

/**
 * PUBLIC METHODS
 */

void					Player::load()
{
  irr::video::IVideoDriver		*driver = this->getDriver();
  irr::scene::ISceneManager		*smgr = this->getSmgr();
  irr::scene::IAnimatedMesh		*mesh;
  irr::scene::IAnimatedMeshSceneNode	*node;

  this->score = 0;
  if (!(mesh = smgr->getMesh("./media/player/Rukifellth.obj")))
    throw RuntimeError("Media", "Missing Character 3D Object");
  if (!(node = smgr->addAnimatedMeshSceneNode(mesh)))
    throw RuntimeError("Node", "Could not create node");
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setScale(irr::core::vector3df(0.6, 0.6, 0.6));
  node->setPosition(this->initialPos);
  if (!driver->getTexture("./media/player/Rukifellth.png"))
    throw RuntimeError("Media", "Could not load Character's texture");
  node->setMaterialTexture( 0, driver->getTexture("./media/player/Rukifellth.png"));
  this->node = node;
}

void			Player::update(EventReceiver const &events)
{
  const irr::f32	delta = this->getFrameDelta();
  const irr::f32	dist = this->speed * delta;

  if (events.isPressed(this->keys["up"]))
    this->moveUp(dist);
  if (events.isPressed(this->keys["left"]))
    this->moveLeft(dist);
  if (events.isPressed(this->keys["right"]))
    this->moveRight(dist);
  if (events.isPressed(this->keys["down"]))
    this->moveDown(dist);
  if (events.isPressed(this->keys["bomb"]))
    this->dropBomb();
}

void	Player::unload()
{
  this->node->remove();
  delete this;
}

irr::scene::ISceneNode	*Player::getNode()
{
  return (this->node);
}

irr::scene::IMesh	*Player::getMesh()
{
  return (this->node->getMesh());
}

unsigned int		Player::getScore() const
{
  return (this->score);
}

void			Player::addScore(unsigned int score)
{
  this->score += score;
}

std::string const&	Player::getName() const
{
  return (this->name);
}

void		Player::setName(std::string const &name)
{
  this->name = name;
}

void		Player::setKey(std::string const &str, irr::EKEY_CODE event)
{
  this->keys[str] = event;
}

irr::core::vector3df	Player::getPosition() const
{
  return (this->node->getPosition());
}

/**
 * PRIVATE METHODS
 */

void					Player::dropBomb()
{
  irr::u32				curr;

  curr = this->getDevice()->getTimer()->getTime();
  if (this->droppedAt != 0 &&
      (this->droppedAt + this->dropCooldown * 1000) > curr)
    return ;
  this->droppedAt = curr;
  this->getMessager()->send(new Message("GameBomb", "", this));
}

void	Player::moveUp(irr::f32 dist)
{
  this->move(irr::core::vector3df(0, 0, dist));
}

void	Player::moveLeft(irr::f32 dist)
{
  this->move(irr::core::vector3df(-dist, 0, 0));
}

void	Player::moveRight(irr::f32 dist)
{
  this->move(irr::core::vector3df(dist, 0, 0));
}

void	Player::moveDown(irr::f32 dist)
{
  this->move(irr::core::vector3df(0, 0, -dist));
}

void			Player::move(irr::core::vector3df vec)
{
  irr::core::vector3df	pos = this->node->getPosition();

  pos.X += vec.X;
  pos.Y += vec.Y;
  pos.Z += vec.Z;
  this->node->setPosition(pos);
}
