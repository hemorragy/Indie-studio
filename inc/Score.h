/*
** Score.h for Score in /home/adrienalliel/cpp_indie_studio/inc
** 
** Made by Adrien Alliel
** Login   <adrienalliel@ubuntu>
** 
** Started on  Sat Jun 17 14:48:07 2017 Adrien Alliel
** Last update Sat Jun 17 14:48:09 2017 Adrien Alliel
*/

#ifndef SCORE_H_
# define SCORE_H_

#include <list>
#include <vector>
#include "CreditsScene.h"

class   Score
{
private:
    std::list<int> listScore;
public:
    Score() {};
    ~Score() {};
    void    add(irr::IrrlichtDevice *fileSystem, std::string playerName, int score);
    std::vector<std::string> split(std::string str, std::string sep);
    std::list<int> fillScore(std::string data, std::list<int> listScore);
    std::list<int> stockScore();
    int            addScore(std::string playerName, int score);
    void            printScore(irr::IrrlichtDevice *);
};
#endif /* !SCORE_H_ */
