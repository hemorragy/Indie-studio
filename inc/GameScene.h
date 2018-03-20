/*
** GameScene.h for GameScene in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 16:39:21 2017 ju
** Last update Sun Jun 18 23:14:02 2017 ju
*/

#ifndef GAMESCENE_H_
# define GAMESCENE_H_

# include <vector>
# include <list>
# include "Scene.h"
# include "Player.h"
# include "Bomb.h"
# include "Map.h"
# include "Message.h"

class					GameScene: public Scene
{
  Player				*player1;
  Player				*player2;
  irr::gui::IGUIStaticText		*text;
  Map					*map;
  irr::scene::IMetaTriangleSelector	*metaCollisionSelector;
  std::vector<irr::scene::ISceneNode *>	collisionList;
  std::list<IObj*>			objs;

  typedef IObj* (GameScene::*creator)(irr::core::vector3df) const;
  std::map<std::string, creator>	creators;

  typedef void (GameScene::*event)(Message const*);
  std::map<std::string, event>		receivers;

public:
  GameScene();
  ~GameScene();

  // PUBLIC METHODS
  virtual void				load();
  virtual void				run();
  virtual void				unload();

  // PRIVATE METHODS
private:
  bool					isPlayerDead(Bomb*, Player*);
  void					listenMessages();
  void					addBomb(irr::core::vector3df);
  void					setupPlayers();
  void					addSelector(irr::scene::ISceneNode *node,
						    irr::scene::IMesh *mesh);
  void					collide(irr::scene::IMeshSceneNode *node, bool gravity, irr::core::vector3df hitbox);
  void					collide(irr::scene::IAnimatedMeshSceneNode *node, bool gravity, irr::core::vector3df hitbox);
  void					end(Message const*);
  void					setNames(Message const*);
  void					addBomb(Message const*);
  void					explodeBomb(Message const*);
  void					removeObject(Message const*);
  IObj*					createObj(std::string const&,
						  irr::core::vector3df);
  IObj*					createBomb(irr::core::vector3df) const;
  IObj*					createPlayer(irr::core::vector3df) const;
  IObj*					createMap(irr::core::vector3df) const;
  void					blockCollision(Map *map);
};

#endif /* !GAMESCENE_H_ */
