/*
** MapEditorScene.h for MapEditorScene in /home/bittan_c/rendu/cpp_indie_studio
** 
** Made by Chai Bittan
** Login   <bittan_c@epitech.net>
** 
** Started on  Sun Jun 18 21:12:50 2017 Chai Bittan
** Last update Mon Jun 19 00:25:08 2017 Chai Bittan
*/

#ifndef MAPEDITOR_H_
# define MAPEDITOR_H_

# include <vector>
# include <list>
# include "Scene.h"
# include "Player.h"
# include "Bomb.h"
# include "Map.h"
# include "Message.h"

class					MapEditorScene: public Scene
{
  Player				*player1;
  irr::gui::IGUIStaticText		*text;
  Map					*map;
  irr::scene::IMetaTriangleSelector	*metaCollisionSelector;
  std::vector<irr::scene::ISceneNode *>	collisionList;
  std::list<IObj*>			objs;
  bool					finish;
  irr::gui::IGUIEditBox			*filename;

  typedef IObj* (MapEditorScene::*creator)(irr::core::vector3df) const;
  std::map<std::string, creator>	creators;

  typedef void (MapEditorScene::*event)(Message const*);
  std::map<std::string, event>		receivers;

public:
  MapEditorScene();
  ~MapEditorScene();

  // PUBLIC METHODS
  virtual void				load();
  virtual void				run();
  virtual void				unload();

  // PRIVATE METHODS
private:
  void					listenMessages();
  void					setupPlayers();
  void					addSelector(irr::scene::ISceneNode *node,
						    irr::scene::IMesh *mesh);
  void					collide(irr::scene::IMeshSceneNode *node, bool gravity, irr::core::vector3df hitbox);
  void					collide(irr::scene::IAnimatedMeshSceneNode *node, bool gravity, irr::core::vector3df hitbox);
  void					setNames(Message const*);
  void					removeObject(Message const*);
  IObj*					createObj(std::string const&,
						  irr::core::vector3df);
  IObj*					createPlayer(irr::core::vector3df) const;
  IObj*					createMap(irr::core::vector3df) const;
  void					blockCollision(Map *map);
  void					generateMap();
  void					saveMap();
};

#endif /* !MAPEDITOR_H_ */
