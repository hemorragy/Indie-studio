/*
** Player.h for Player in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 04:32:14 2017 ju
** Last update Sun Jun 18 21:48:13 2017 ju
*/

#ifndef PLAYER_H_
# define PLAYER_H_

# include <map>
# include <string>
# include "Obj.h"
# include "RuntimeError.h"

class					Player: public Obj
{
  unsigned int				speed; // Units per seconds
  unsigned int				dropCooldown;
  irr::u32				droppedAt;
  std::string				name;
  irr::core::vector3df			initialPos;
  std::map<std::string, irr::EKEY_CODE>	keys;
  unsigned int				score;

public:
  irr::scene::IAnimatedMeshSceneNode	*node;
  Player(irr::core::vector3df, irr::IrrlichtDevice*, MessagesHandler*);
  virtual ~Player();
  // PUBLIC METHODS
  virtual void				load();
  virtual void				update(EventReceiver const&);
  virtual void				unload();
  virtual irr::scene::ISceneNode	*getNode();
  virtual irr::scene::IMesh		*getMesh();
  void					setKey(std::string const&, irr::EKEY_CODE);
  irr::core::vector3df			getPosition() const;
  std::string const&			getName() const;
  unsigned int				getScore() const;
  void					addScore(unsigned int);
  void					setName(std::string const&);
private:
  // PRIVATE METHODS
  void					dropBomb();
  void					moveUp(irr::f32);
  void					moveLeft(irr::f32);
  void					moveRight(irr::f32);
  void					moveDown(irr::f32);
  void					move(irr::core::vector3df);
};

#endif /* !PLAYER_H_ */
