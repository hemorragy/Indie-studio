/*
** Score.cpp for Score in /home/adrienalliel/cpp_indie_studio/src
** 
** Made by Adrien Alliel
** Login   <adrienalliel@ubuntu>
** 
** Started on  Sat Jun 17 15:24:08 2017 Adrien Alliel
** Last update Sun Jun 18 22:59:11 2017 Chai Bittan
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <irrlicht.h>
#include "../inc/CreditsScene.h"
#include "../inc/Player.h"
#include "../inc/Score.h"

std::vector<std::string> Score::split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

std::list<int> Score::fillScore(std::string data, std::list<int> listScore)
{
    std::string sub;
    std::vector<std::string> stock;
    int                      temp;

    stock = this->split(data, " ");
    temp = std::stoi(stock[1]);
    listScore.push_back(temp);
    return (listScore);
}

std::list<int> Score::stockScore()
{
    std::ifstream    scoreFile("score.txt", std::ifstream::in);
    std::list<int>   listScore;
    std::string        content;

    while (getline(scoreFile, content))
        listScore = this->fillScore(content, listScore);
      for (std::list<int>::iterator it=listScore.begin(); it != listScore.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << '\n';
    return (listScore);
}

int     Score::addScore(std::string playerName, int score)
{
    std::ofstream file;
    file.open("score.txt", std::ios_base::app); 
    file << playerName << " " << score << std::endl;
    file.close();

    return (0);
}

void    Score::printScore(irr::IrrlichtDevice *device)
{
    std::ifstream    scoreFile("score.txt", std::ifstream::in);
    std::string      content;
    std::wstring widestr;
    const wchar_t *test;
    int x = 30;
    int y = 20;
    
    //IGUIEnvironment* env = device->getGUIEnvironment();
    /*IGUIWindow* wnd = env->addWindow(core::rect<s32>(100,20,800,480), false, L"Toolset", 0, 2);
    IGUITabControl* tab = env->addTabControl(core::rect<s32>(2,20,800-602,480-7), wnd, true, true);
    IGUITab* t1 = tab->addTab(L"Config");*/
    //IGUIScrollBar* scrollbar = env->addScrollBar(true,
      //  core::rect<s32>(10,225,150,240), t1, 1);

    //file.open("score.txt");

    /*IGUIEnvironment* guienv = device->getGUIEnvironment();
    IGUIScrollBar* scrollbar1 = guienv->addScrollBar(true, rect<s32>(position2di(50,75),dimension2di(200,20)), wnd, 102);
    scrollbar1->setMax(255);
    scrollbar1->setPos(guienv->getSkin()->getColor(EGDC_WINDOW).getAlpha());*/
    int z = 100;
    int w = 200;
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    //guienv->addStaticText(L"Transparent Control:", rect<s32>(position2di(300,50),dimension2di(200,20)), true, false, wnd);
    while (getline(scoreFile, content))
    {
        widestr = std::wstring(content.begin(), content.end());
        test = widestr.c_str();
        guienv->addStaticText(test, irr::core::rect<irr::s32>(z,y,w,x), true, true, 0, -1, true);
        //env->addStaticText(test, rect<s32>(100,y,400,x), true, false, wnd);
        y += 10;
        if (y == 500)
        {
            w += 100;
            y = 20;
            z += 100;
        }
        x+= 30;
    }
}

void    Score::add(irr::IrrlichtDevice *fileSystem, std::string playerName, int score)
{
    std::list<int> listScore;    
    
    fileSystem->setWindowCaption(L"Bomberman - Score");
    addScore(playerName, score);
    //listScore = this->stockScore();
}

