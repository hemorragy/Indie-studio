/*
** MainMenuScene.h for MainMenuScene in /home/ju/tek/cpp/bomber
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Thu May 18 17:25:15 2017 ju
** Last update Sun Jun 18 23:47:07 2017 Eddy Chouikha
*/

#ifndef MAINMENUSCENE_H_
# define MAINMENUSCENE_H_

# include "Scene.h"

class				MainMenuScene: public Scene
{
  irr::gui::IGUIImage		*background;
public:

  MainMenuScene();
  ~MainMenuScene();

  // PUBLIC METHODS
  virtual void			load();
  virtual void			run();
  virtual void			unload();

  // PRIVATE METHODS
};

#endif /* !MAINMENUSCENE_H_ */
