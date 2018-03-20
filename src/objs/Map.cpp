/*
** Player.cpp for Player in /home/ju/tek/cpp/cpp_indie_studio
**
** Made by ju
** Login   <ju@ju-virtual>
**
** Started on  Sat Jun 17 04:32:01 2017 ju
** Last update Mon Jun 19 01:22:51 2017 Chai Bittan
*/

#include <fstream>
#include <iostream>
#include "Map.h"

Map::Map(irr::core::vector3df pos,
	 irr::IrrlichtDevice *device,
	 MessagesHandler *messager,
	 const std::string &map): Obj(device, messager),
			   initialPos(pos),
			   file_map(map)
{
}

Map::~Map()
{
}

/**
 * PUBLIC METHODS
 */

void	Map::load()
{
  setupMap();
  setupTray();
  setupBlock();
  getMap();
}

void	Map::update(EventReceiver const &events)
{
  (void)events;
}

void	Map::unload()
{
  std::cout << "remove map" << std::endl;
  int		x = 0;
  int		y;

  while (x < MAP_SIZE)
    {
      y = 0;
      while (y < MAP_SIZE)
	{
	  std::vector<irr::scene::IMeshSceneNode*> *curr = this->tray->at(x);
	  irr::scene::IMeshSceneNode *node = curr->at(y);
	  node->remove();
	  ++y;
	}
      ++x;
    }
  this->map->remove();
  delete this;
}

irr::scene::ISceneNode	*Map::getNode()
{
  return (this->map);
}

irr::scene::IMesh	*Map::getMesh()
{
  return (this->map->getMesh());
}

void	Map::getPos(int *x, int *y)
{
  int	a = 0;
  int	b = 0;

  while (*x >= -9.1)
    {
      ++a;
      *x = *x - 2;
    }
  while (*y >= -8)
    {
      ++b;
      *y = *y - 2;
    }
  *x = a;
  *y = b;
}

irr::scene::IMeshSceneNode	*Map::getBlockPlayer(int x, int y)
{
  getPos(&x, &y);
  if (x < 0 || y < 0)
    throw RuntimeError("Map", "Out of range");
  std::vector<irr::scene::IMeshSceneNode*>	*curr = this->tray->at(x);
  irr::scene::IMeshSceneNode			*node = curr->at(y);
  return (node);
}

bool	Map::isPlayerDead(int expX, int expY, Player *p)
{
  int	x;
  int	y;

  x = p->getNode()->getPosition().X;
  y = p->getNode()->getPosition().Z;
  getPos(&x, &y);
  return (x == expX && y == expY);
}

int	Map::getExplode(int x, int y, int range, int direction, Player *p[2])
{
  int	count = 1;

  while (range)
    {
      x = (direction == 0) ? x - 1 : x;
      y = (direction == 1) ? y + 1 : y;
      x = (direction == 2) ? x + 1 : x;
      y = (direction == 3) ? y - 1 : y;
      if (this->isPlayerDead(x, y, p[0]))
	 this->getMessager()->send(new Message("GameDie", "", p[0]));
      if (this->isPlayerDead(x, y, p[1]))
	this->getMessager()->send(new Message("GameDie", "", p[1]));
      if (this->map_tab[x][y] == 2)
	{
	  std::vector<irr::scene::IMeshSceneNode*>	*curr = this->tray->at(x);
	  irr::scene::IMeshSceneNode			*node = curr->at(y);
	  node->setPosition(irr::core::vector3df(node->getPosition().X, -20, node->getPosition().Z));
	  this->map_tab[x][y] = 0;
	  return (count);
	}
      ++count;
      --range;
    }
  return (-1);
}

int	*Map::deleteBlock(int x, int y, int range, Player *p[2])
{
  int	*explode = new int[4];

  if (!explode)
    throw RuntimeError("Alloc", "Memory allocation failure");
  getPos(&x, &y);
  if (x < 0 || y < 0)
    throw RuntimeError("Map", "Out of range");
  if (this->isPlayerDead(x, y, p[0]))
    this->getMessager()->send(new Message("GameDie", "", p[0]));
  if (this->isPlayerDead(x, y, p[1]))
    this->getMessager()->send(new Message("GameDie", "", p[1]));
  explode[0] = getExplode(x, y, range, 0, p);
  explode[1] = getExplode(x, y, range, 1, p);
  explode[2] = getExplode(x, y, range, 2, p);
  explode[3] = getExplode(x, y, range, 3, p);
  return (explode);
}

void						Map::putBlock(int x, int y, char type)
{
  std::vector<irr::scene::IMeshSceneNode*>	*curr = this->tray->at(x);
  irr::scene::IMeshSceneNode			*node = curr->at(y);
  irr::video::IVideoDriver			*driver = this->getDriver();

  if (type == '2')
    node->setMaterialTexture(0, driver->getTexture(TEXT_BREAK));
  if (type == '3')
    node->setMaterialTexture(0, driver->getTexture(TEXT_UNBREAK));
  node->setVisible(true);
  this->map_tab[x][y] = type - '0';
}

void		Map::getMap()
{
  std::ifstream	file(this->file_map.c_str());
  std::string	str;
  int		x = 0;
  int		y;

  if (!file)
    throw RuntimeError("Map", "Couldn't load map file");
  while (std::getline(file, str))
    {
      if (str.size() != MAP_SIZE - 2)
	throw RuntimeError("Map", "Map format isn't good");
      y = 0;
      while (y < MAP_SIZE - 2)
	{
	  if (str[y] != '0' && str[y] != '2' && str[y] != '3')
	    throw RuntimeError("Map", "Map format isn't good");
	  if (str[y] == '2' || str[y] == '3')
	    putBlock(x + 1, (MAP_SIZE - 1) - (y + 1), str[y]);
	  ++y;
	}
      ++x;
    }
  if (x < MAP_SIZE - 2)
    throw RuntimeError("Map", "Map format isn't good");
}

void				Map::setupBlock()
{
  irr::video::IVideoDriver	*driver = this->getDriver();
  irr::scene::ISceneManager	*smgr = this->getSmgr();
  int				a = 0;
  int				b;

  while (a < MAP_SIZE)
    {
      b = 0;
      while (b < MAP_SIZE)
	{
	  std::vector<irr::scene::IMeshSceneNode*> *curr = this->tray->at(a);
	  curr->push_back(smgr->addCubeSceneNode(2));
	  irr::scene::IMeshSceneNode *node = curr->at(b);
	  node->setPosition(irr::core::vector3df(-11.1 + (2 * a),
						 -5.2, -10 + (2 * b)));
	  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	  node->setMaterialTexture(0, driver->getTexture(TEXT_WALL));
	  node->setVisible(((a == 0 || a == MAP_SIZE - 1) || (b == 0 || b == MAP_SIZE - 1))
			   ? true : false);
	  this->map_tab[a][b] = ((a == 0 || a == MAP_SIZE - 1) || (b == 0 || b == MAP_SIZE - 1))
	    ? 1 : 0;
	  ++b;
	}
      ++a;
    }
}

void								Map::setupTray()
{
  std::vector<std::vector<irr::scene::IMeshSceneNode*>*>	*arr =
    new std::vector<std::vector<irr::scene::IMeshSceneNode*>*>;
  int								i = 0;

  if (!arr)
    throw RuntimeError("Alloc", "Memory allocation failure");
  this->map_tab = new int*[12];
  while (i < MAP_SIZE)
    {
      arr->push_back(new std::vector<irr::scene::IMeshSceneNode*>);
      std::vector<irr::scene::IMeshSceneNode*>	*curr = arr->at(i);
      if (!curr)
	throw RuntimeError("Alloc", "Memory allocation failure");
      this->map_tab[i] = new int[12];
      ++i;
    }
  this->tray = arr;
}

void				Map::setupMap()
{
  irr::video::IVideoDriver	*driver = this->getDriver();
  irr::scene::ISceneManager	*smgr = this->getSmgr();
  irr::scene::IMesh		*map_mesh;
  irr::scene::IMeshSceneNode	*map;

  (void)driver;
  map_mesh = smgr->getMesh(OBJ_GROUND);
  map = smgr->addMeshSceneNode(map_mesh);
  map->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  map->setPosition(irr::core::vector3df(0, -8, 0));
  map->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
  map->setRotation(irr::core::vector3df(0, 0, 0));
  this->map = map;
  map->setMaterialTexture(0, driver->getTexture(TEXT_GROUND));
}

/**
 * PRIVATE METHODS
 */
