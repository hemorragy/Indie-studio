/*
** OptionsScene.h for OptionsScene in /home/ju/tek/cpp/cpp_indie_studio
** 
** Made by ju
** Login   <ju@ju-virtual>
** 
** Started on  Sat Jun 17 21:24:42 2017 ju
** Last update Sun Jun 18 23:34:26 2017 Eddy Chouikha
*/

#ifndef OPTIONSSCENE_H_
# define OPTIONSSCENE_H_

# include "Scene.h"
# include <cwchar>

class					OptionsScene: public Scene
{
  irr::gui::IGUIImage			*background;
  irr::gui::IGUIImage			*logo;
  irr::gui::IGUIStaticText		*text;
  irr::video::IVideoDriver		*dedriver;
  irr::gui::IGUIEditBox*		box1;
  irr::gui::IGUIEditBox*		box2;
  const wchar_t				*player1;
  const wchar_t				*player2;

public:

  OptionsScene();
  ~OptionsScene();

  // PUBLIC METHODS
  virtual void				load();
  virtual void				run();
  virtual void				unload();

  // PRIVATE METHODS
private:
};

#endif /* !OPTIONSSCENE_H_ */
