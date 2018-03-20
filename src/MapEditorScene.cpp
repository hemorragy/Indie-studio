/*
** MapEditorScene.cpp for MapEditorScene in /home/bittan_c/rendu/cpp_indie_studio/src
** 
** Made by Chai Bittan
** Login   <bittan_c@epitech.net>
** 
** Started on  Sun Jun 18 21:13:09 2017 Chai Bittan
** Last update Mon Jun 19 00:34:04 2017 Chai Bittan
*/

#include "ScenesHandler.h"
#include "MapEditorScene.h"
#include <algorithm>
#include <iostream>
#include <fstream>

MapEditorScene::MapEditorScene(): Scene()
{
  this->creators["Player"] = &MapEditorScene::createPlayer;
  this->creators["Map"] = &MapEditorScene::createMap;
  this->receivers["GameNames"] = &MapEditorScene::setNames;
  this->receivers["GameRemove"] = &MapEditorScene::removeObject;
  this->metaCollisionSelector = NULL;
  this->finish = false;
}

MapEditorScene::~MapEditorScene()
{

}

/**
 * PUBLIC METHODS
 */

using namespace irr;

void				MapEditorScene::load()
{
  irr::scene::ISceneManager	*smgr = this->getSmgr();

  this->setupPlayers();
  smgr->addCameraSceneNode(0,
			   irr::core::vector3df(0, 22, -5),
			   irr::core::vector3df(0, 0, 0));
  this->listenMessages();

 scene::IParticleSystemSceneNode* ps =
   smgr->addParticleSystemSceneNode(false);
 scene::IParticleEmitter* em = ps->createBoxEmitter(
						    core::aabbox3d<f32>(-2,0,-2,2,1,2), // emitter size
						    core::vector3df(0.02f,0.f,0.0f),   // initial direction
						    80,100,                             // emit rate
						    video::SColor(0,255,255,0),       // darkest color
						    video::SColor(0,255,255,0),       // brightest color
						    100,300,0,                         // min and max age, angle
						    core::dimension2df(0.2f,0.2f),         // min size
						    core::dimension2df(1.f,1.f));        // max size

 ps->setEmitter(em); // this grabs the emitter
 em->drop(); // so we can drop it here without deleting it

 scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

 ps->addAffector(paf); // same goes for the affector
 paf->drop();
 ps->setPosition(core::vector3df(0, -4, 0));
 ps->setScale(core::vector3df(0.1, 0.1, 0.1));
 ps->setMaterialFlag(video::EMF_LIGHTING, false);
 ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
 ps->setMaterialTexture(0, this->getDriver()->getTexture("./media/bomb/fireball.bmp"));
 ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

void	MapEditorScene::generateMap()
{
  int	x = 0;
  int	y;
  int posx;
  int posz;

  while (x < 12)
    {
      y = 0;
      while (y < 12)
	{
	  if ((x != 0 && x != 11) && (y != 0 && y != 11))
	    {
	      std::vector<irr::scene::IMeshSceneNode*> *curr = map->tray->at(x);
	      irr::scene::IMeshSceneNode *node = curr->at(y);
	      posx = node->getPosition().X;
	      posz = node->getPosition().Z;
	      this->map->getPos(&posx, &posz);
	    }
	  ++y;
	}
      ++x;
    }
}

void	MapEditorScene::saveMap()
{
  int	x = 11;
  int	y;
  std::ofstream	file;
  std::wstring ws(this->filename->getText());
  std::string name(ws.begin(), ws.end());

  name += ".map";
  file.open(name.c_str());
  if (!file.is_open())
    this->quit();
  while (--x >= 1)
    {
      y = -1;
      while (++y < 12)
	{
	  if ((x != 0 && x != 11) && (y != 0 && y != 11))
	    file << this->map->map_tab[y][x];
	}
      file << std::endl;
    }
  file.close();
}

void	MapEditorScene::run()
{
  int	x;
  int	z;

  this->listenMessages();
  for (auto &e: this->objs)
    e->update(*this->getEvents());
  if (this->getEvents()->isPressed(irr::KEY_ESCAPE))
    this->quit();
  this->player1->update(*this->getEvents());
  if (this->getEvents()->isPressed(irr::KEY_SPACE) && !finish)
    {
      irr::scene::IMeshSceneNode *block = this->map->getBlockPlayer
	(this->player1->node->getPosition().X, this->player1->node->getPosition().Z);
      block->setVisible(true);
      block->setMaterialTexture(0, this->getDriver()->getTexture(TEXT_BREAK));
      x = this->player1->node->getPosition().X;
      z = this->player1->node->getPosition().Z;
      this->map->getPos(&x, &z);
      this->map->map_tab[x][z] = 2;
    }
  if (this->getEvents()->isPressed(irr::KEY_KEY_C) && !finish)
    {
      irr::scene::IMeshSceneNode *block = this->map->getBlockPlayer
	(this->player1->node->getPosition().X, this->player1->node->getPosition().Z);
      block->setVisible(true);
      block->setMaterialTexture(0, this->getDriver()->getTexture(TEXT_UNBREAK));
      x = this->player1->node->getPosition().X;
      z = this->player1->node->getPosition().Z;
      this->map->getPos(&x, &z);
      this->map->map_tab[x][z] = 3;
    }
  if (this->getEvents()->isPressed(irr::KEY_KEY_R) && !finish)
    {
      irr::scene::IMeshSceneNode *block = this->map->getBlockPlayer
	(this->player1->node->getPosition().X, this->player1->node->getPosition().Z);
      block->setVisible(false);
      x = this->player1->node->getPosition().X;
      z = this->player1->node->getPosition().Z;
      this->map->getPos(&x, &z);
      this->map->map_tab[x][z] = 0;
    }
  if (this->getEvents()->isPressed(irr::KEY_KEY_V) && !finish)
    {
      irr::gui::IGUIEnvironment* guienv = this->getDevice()->getGUIEnvironment();
      irr::gui::IGUIStaticText *text2 = guienv->addStaticText
	(L"Map name :",
	 irr::core::rect<irr::s32>(10, 70, 10 + 110, 70 + 10));
      text2->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
      this->filename = guienv->addEditBox
	(L"map_custom", irr::core::rect<irr::s32>(10, 85, 10 + 110, 90 + 10));
      finish = true;
    }
  if (this->getEvents()->isPressed(irr::KEY_RETURN) && finish)
    {
      this->saveMap();
      this->quit();
    }
}

void					MapEditorScene::listenMessages()
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

void	MapEditorScene::unload()
{
  std::cout << "Unload " << std::endl;
  if (this->getSmgr()->getActiveCamera())
    this->getSmgr()->getActiveCamera()->remove();
  for (auto &e: this->objs)
    {
      e->unload();
  std::cout << "Unload " << std::endl;
    }
  this->objs.clear();
}

/**
 * PRIVATE METHODS
 */

void	MapEditorScene::blockCollision(Map *map)
{
  int	x = 0;
  int	y;

  while (x < 12)
    {
      y = 0;
      while (y < 12)
	{
	  if ((x == 0 || x == 11) || (y == 0 || y == 11))
	    {
	      std::vector<irr::scene::IMeshSceneNode*> *curr = map->tray->at(x);
	      irr::scene::IMeshSceneNode *node = curr->at(y);
	      this->addSelector(node, node->getMesh());
	    }
	  ++y;
	}
      ++x;
    }
}

void			MapEditorScene::setupPlayers()
{
  irr::core::vector3df	pos1;
  irr::gui::IGUIEnvironment* guienv = this->getDevice()->getGUIEnvironment();
  irr::gui::IGUIStaticText *text;

  pos1 = irr::core::vector3df(0, -5, 0);
  this->map = static_cast<Map*>(this->createObj("Map", pos1));
  if (!(this->player1 = static_cast<Player*>(this->createObj("Player", pos1))))
    throw new RuntimeError("Could not initialize a player");
  this->player1->setKey("up", irr::KEY_KEY_Z);
  this->player1->setKey("down", irr::KEY_KEY_S);
  this->player1->setKey("left", irr::KEY_KEY_Q);
  this->player1->setKey("right", irr::KEY_KEY_D);
  this->addSelector(this->map->getNode(), this->map->getMesh());
  this->blockCollision(this->map);
  this->collide(this->player1->node, true, irr::core::vector3df(0.5, 0.5, 0.5));
  text = guienv->addStaticText
    (L"ZQSD : Move\nSPACE : Place wooden block\nC : Place solid block\nR : Remove block\nV : Save map",
     irr::core::rect<irr::s32>(10, 10, 10 + 110, 10 + 50), true);
  text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
}

void		MapEditorScene::addSelector(irr::scene::ISceneNode *node,
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

void					MapEditorScene::collide(irr::scene::IMeshSceneNode *node,
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

void					MapEditorScene::collide(irr::scene::IAnimatedMeshSceneNode *node,
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

void		MapEditorScene::setNames(Message const *msg)
{
  this->player1->setName(msg->getAction());
  std::cout << "P1: " << this->player1->getName() << std::endl;
}

void				MapEditorScene::removeObject(Message const *msg)
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

IObj*	MapEditorScene::createObj(std::string const &name,
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

IObj*		MapEditorScene::createPlayer(irr::core::vector3df pos) const
{
  return (new Player(pos, this->getDevice(), this->getMessager()));
}

IObj*		MapEditorScene::createMap(irr::core::vector3df pos) const
{
  return (new Map(pos, this->getDevice(), this->getMessager(),
		  "./media/map/empty_map.map"));
}
