/*
** IntroScene.h for IntroScene in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sun Jun 18 22:13:22 2017 ju
** Last update Sun Jun 18 23:32:49 2017 Eddy Chouikha
*/

#ifndef INTROSCENE_H_
# define INTROSCENE_H_

# include "Scene.h"

class			IntroScene: public Scene
{
  irr::gui::IGUIImage	*background;
  irr::u32		startedAt;
  unsigned int		duration;

public:

  IntroScene();
  ~IntroScene();

  // PUBLIC METHODS
  virtual void		load();
  virtual void		run();
  virtual void		unload();

  // PRIVATE METHODS
private:
};

#endif /* !INTROSCENE_H_ */
