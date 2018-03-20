/*
** GameScene.cpp for GameScene in /home/ju/tek/cpp/cpp_indie_studio
**
** Made by ju
** Login   <ju@ju-virtual>
**
** Started on  Sat Jun 17 16:37:23 2017 ju
** Last update Sun Jun 18 23:37:10 2017 ju
*/

#include "ScenesHandler.h"
#include "GameScene.h"
#include <algorithm>
#include "Score.h"

GameScene::GameScene(): Scene()
{
  this->creators["Bomb"] = &GameScene::createBomb;
  this->creators["Player"] = &GameScene::createPlayer;
  this->creators["Map"] = &GameScene::createMap;
  this->receivers["GameNames"] = &GameScene::setNames;
  this->receivers["GameBomb"] = &GameScene::addBomb;
  this->receivers["GameRemove"] = &GameScene::removeObject;
  this->receivers["GameExplode"] = &GameScene::explodeBomb;
  this->receivers["GameDie"] = &GameScene::end;
  this->metaCollisionSelector = NULL;
}

GameScene::~GameScene()
{

}

/**
 * PUBLIC METHODS
 */

void				GameScene::load()
{
  irr::scene::ISceneManager	*smgr = this->getSmgr();

  this->setupPlayers();
  smgr->addCameraSceneNode(0,
			   irr::core::vector3df(0, 22, -5),
			   irr::core::vector3df(0, 0, 0));
  this->listenMessages();
}

void	GameScene::run()
{
  this->listenMessages();
  for (auto &e: this->objs)
    e->update(*this->getEvents());
  if (this->getEvents()->isPressed(irr::KEY_ESCAPE))
    this->quit();
  this->player1->update(*this->getEvents());
  this->player2->update(*this->getEvents());
}

void					GameScene::listenMessages()
{
  std::list<Message const*>::iterator	itr;
  Message const				*msg;
  std::list<Message const*>		&list = this->getMessager()->all();

  itr = list.begin();
  while (itr != list.end())
    {
      msg = *itr;
      if (this->receivers[msg->getCategory()])
	{
	  (*this.*(this->receivers[msg->getCategory()]))(msg);
	  itr = list.erase(itr);
	}
      else
	++itr;
    }
}

void	GameScene::unload()
{
  if (this->getSmgr()->getActiveCamera())
    this->getSmgr()->getActiveCamera()->remove();
  for (auto &e: this->objs)
    {
      e->unload();
    }
  this->objs.clear();
}

/**
 * PRIVATE METHODS
 */

void	GameScene::blockCollision(Map *map)
{
  int	x = 0;
  int	y;

  while (x < 12)
    {
      y = 0;
      while (y < 12)
	{
	  std::vector<irr::scene::IMeshSceneNode*> *curr = map->tray->at(x);
	  irr::scene::IMeshSceneNode *node = curr->at(y);
	  this->addSelector(node, node->getMesh());
	  ++y;
	}
      ++x;
    }
}

void		GameScene::end(Message const *msg)
{
  Score		score;
  Player	*player = static_cast<Player*>(msg->getData());

  if (player == this->player1)
    std::cout << this->player2->getName() << " wins!" << std::endl;
  else
    std::cout << this->player1->getName() << " wins!" << std::endl;
  score.add(this->getDevice(), this->player1->getName(), (int)this->player1->getScore());
  score.add(this->getDevice(), this->player2->getName(), (int)this->player2->getScore());
  this->quit();
}

void			GameScene::setupPlayers()
{
  irr::core::vector3df	pos1;
  irr::core::vector3df	pos2;

  pos1 = irr::core::vector3df(-9, -5, 9);
  pos2 = irr::core::vector3df(9, -5, -8);
  this->map = static_cast<Map*>(this->createObj("Map", pos1));
  if (!(this->player1 = static_cast<Player*>(this->createObj("Player", pos1))) ||
      !(this->player2 = static_cast<Player*>(this->createObj("Player", pos2))))
    throw new RuntimeError("Could not initialize a player");
  this->player1->setKey("up", irr::KEY_KEY_Z);
  this->player1->setKey("down", irr::KEY_KEY_S);
  this->player1->setKey("left", irr::KEY_KEY_Q);
  this->player1->setKey("right", irr::KEY_KEY_D);
  this->player1->setKey("bomb", irr::KEY_KEY_A);
  this->player2->setKey("up", irr::KEY_UP);
  this->player2->setKey("down", irr::KEY_DOWN);
  this->player2->setKey("left", irr::KEY_LEFT);
  this->player2->setKey("right", irr::KEY_RIGHT);
  this->player2->setKey("bomb", irr::KEY_SPACE);
  this->addSelector(this->map->getNode(), this->map->getMesh());
  this->blockCollision(this->map);
  this->collide(static_cast<irr::scene::IAnimatedMeshSceneNode*>(this->player1->getNode()), true, irr::core::vector3df(0.5, 0.5, 0.5));
  this->collide(static_cast<irr::scene::IAnimatedMeshSceneNode*>(this->player2->getNode()), true, irr::core::vector3df(0.5, 0.5, 0.5));
}

void		GameScene::addSelector(irr::scene::ISceneNode *node,
				       irr::scene::IMesh *mesh)
{
  irr::scene::ITriangleSelector		*selector;

  if (std::find(this->collisionList.begin(), this->collisionList.end(), node)
      != this->collisionList.end())
    return ;
  if ((selector = this->getSmgr()->createTriangleSelector(mesh, node)))
    {
      node->setTriangleSelector(selector);
      if (!this->metaCollisionSelector)
	this->metaCollisionSelector = this->getSmgr()->createMetaTriangleSelector();
      this->metaCollisionSelector->addTriangleSelector(selector);
    }
  this->collisionList.push_back(node);
  selector->drop();
}

void					GameScene::collide(irr::scene::IMeshSceneNode *node,
							   bool gravity,
							   irr::core::vector3df hitbox)
{
  irr::scene::ISceneNodeAnimator	*animator;

  animator = this->getSmgr()->createCollisionResponseAnimator
    (this->metaCollisionSelector, node,
     hitbox,
     irr::core::vector3df(0, gravity ? -0.3 : 0, 0));
  node->addAnimator(animator);
  animator->drop();
}

void					GameScene::collide(irr::scene::IAnimatedMeshSceneNode *node,
							   bool gravity,
							   irr::core::vector3df hitbox)
{
  irr::scene::ISceneNodeAnimator	*animator;

  animator = this->getSmgr()->createCollisionResponseAnimator
    (this->metaCollisionSelector, node,
     hitbox,
     irr::core::vector3df(0, gravity ? -0.3 : 0, 0));
  node->addAnimator(animator);
  animator->drop();
}

void		GameScene::setNames(Message const *msg)
{
  std::string	*name = static_cast<std::string*>(msg->getData());

  this->player1->setName(msg->getAction());
  if (name)
    this->player2->setName(*name);
}

void		GameScene::addBomb(Message const *msg)
{
  Player	*player = static_cast<Player*>(msg->getData());
  Bomb		*bomb = static_cast<Bomb*>(this->createObj("Bomb", player->getPosition()));

  bomb->setPlayer(player);
}

void				GameScene::explodeBomb(Message const *msg)
{
  Bomb				*bomb = static_cast<Bomb*>(msg->getData());
  irr::core::vector3df		pos = bomb->getNode()->getPosition();
  Player			*tab[2];

  tab[0] = this->player1;
  tab[1] = this->player2;
  this->map->deleteBlock(pos.X, pos.Z, bomb->getRange(), tab);
  this->removeObject(msg);
}

void				GameScene::removeObject(Message const *msg)
{
  IObj				*cur;
  std::list<IObj*>::iterator	itr;

  itr = this->objs.begin();
  while (itr != this->objs.end())
    {
      cur = *itr;
      if (cur == msg->getData())
	{
	  cur->unload();
	  itr = this->objs.erase(itr);
	}
      else
	++itr;
    }
}

IObj*	GameScene::createObj(std::string const &name,
			     irr::core::vector3df pos)
{
  IObj	*obj;

  if (this->creators[name])
    {
      if ((obj = (*this.*(this->creators[name]))(pos)))
	{
	  obj->load();
	  this->objs.push_back(obj);
	  return (obj);
	}
    }
  return (NULL);
}

IObj*		GameScene::createBomb(irr::core::vector3df pos) const
{
  return (new Bomb(pos, this->getDevice(), this->getMessager()));
}

IObj*		GameScene::createPlayer(irr::core::vector3df pos) const
{
  return (new Player(pos, this->getDevice(), this->getMessager()));
}

IObj*		GameScene::createMap(irr::core::vector3df pos) const
{
  return (new Map(pos, this->getDevice(), this->getMessager(),
		  "./media/map/map_base.map"));
}
