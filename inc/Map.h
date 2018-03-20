/*
** Map.h for Map in /home/ju/tek/cpp/cpp_indie_studio
**
** Made by ju
** Login   <ju@ju-virtual>
**
** Started on  Sun Jun 18 03:00:27 2017 ju
** Last update Mon Jun 19 01:06:45 2017 Chai Bittan
*/

#ifndef MAP_H_
# define MAP_H_

# include <map>
# include <string>
# include <vector>
# include "Obj.h"
# include "RuntimeError.h"
# include "Player.h"

# define MAP_SIZE 12
# define TEXT_WALL "./media/map/Textures/Tile.png"
# define TEXT_BREAK "./media/map/Textures/Box2.png"
# define TEXT_GROUND "./media/map/blocks.png"
# define TEXT_UNBREAK "./media/map/Textures/Cement.png"
# define OBJ_GROUND "./media/map/Arena.obj"

class					Map: public Obj
{
  irr::core::vector3df			initialPos;
  std::string				file_map;
  irr::scene::IMeshSceneNode					*map;

public:
  std::vector<std::vector<irr::scene::IMeshSceneNode*>*>	*tray;
  int								**map_tab;

  Map(irr::core::vector3df, irr::IrrlichtDevice*, MessagesHandler*, const std::string &);
  virtual ~Map();
  // PUBLIC METHODS
  virtual void				load();
  virtual void				update(EventReceiver const&);
  virtual void				unload();
  virtual irr::scene::ISceneNode	*getNode();
  virtual irr::scene::IMesh		*getMesh();
  int					*deleteBlock(int, int, int, Player *p[2]);
  irr::scene::IMeshSceneNode		*getBlockPlayer(int, int);
  void					getPos(int *, int *);
private:
  int					getExplode(int, int, int, int, Player *p[2]);
  void					setupMap();
  void					setupTray();
  void					setupBlock();
  void					getMap();
  void					putBlock(int, int, char);
  bool					isPlayerDead(int, int, Player *);
  // PRIVATE METHODS
};

#endif /* !MAP_H_ */
