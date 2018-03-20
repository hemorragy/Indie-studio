/*
** CreditsScene.h for CreditsScene in /home/ju/tek/cpp/bomber
**
** Made by ju
** Login   <ju@ju-virtual>
**
** Started on  Wed May 17 03:01:17 2017 ju
** Last update Sun Jun 18 22:13:38 2017 ju
*/

#ifndef CREDITSSCENE_H_
# define CREDITSSCENE_H_

# include "Scene.h"

class					CreditsScene: public Scene
{
  irr::gui::IGUIStaticText		*text;

public:

  CreditsScene();
  ~CreditsScene();

  // PUBLIC METHODS
  virtual void				load();
  virtual void				run();
  virtual void				unload();
  void                callFunc(std::string, int);

  // PRIVATE METHODS
private:
};

#endif /* !CREDITSSCENE_H_ */
