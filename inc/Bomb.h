/*
** Player.h for Player in /home/ju/tek/cpp/cpp_indie_studio
**
** Made by ju
** Login   <ju@ju-virtual>
**
** Started on  Sat Jun 17 04:32:14 2017 ju
** Last update Sun Jun 18 21:37:36 2017 ju
*/

#ifndef BOMB_H_
# define BOMB_H_

# include <iostream>
# include "Obj.h"
# include "Player.h"
# include "RuntimeError.h"

class					Bomb: public Obj
{
  irr::core::vector3df			_playerPosition;
  int					_range;
  int					_duration;
  irr::u32				_startedAt;
  Player				*_player;
  irr::scene::IAnimatedMeshSceneNode	*node;

public:

  Bomb(irr::core::vector3df, irr::IrrlichtDevice*, MessagesHandler*);
  virtual ~Bomb();
  // PUBLIC METHODS
  virtual void				load();
  virtual void				update(EventReceiver const&);
  virtual void				unload();
  virtual irr::scene::ISceneNode	*getNode();
  virtual irr::scene::IMesh		*getMesh();
  Player*				getPlayer() const;
  void					setPlayer(Player*);
  unsigned int				getRange() const;
  void					explode();
};

#endif /* !BOMB_H_ */
