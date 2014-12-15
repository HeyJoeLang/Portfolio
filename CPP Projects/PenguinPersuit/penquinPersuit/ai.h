#pragma once

#include <cmath>

class SearchCell
{
   public:
      int m_xcoord, m_ycoord, m_id;

      SearchCell *parent;

      float G;
      float H;

      SearchCell() : parent(0) { };
      SearchCell(int x, int y, int id, SearchCell *_parent) :
      m_xcoord(x),
      m_ycoord(y),
      parent(_parent),
      m_id( id),
      G(0.0f),
      H(0.0f)
      {  };

      float GetF() { return G + H; }
      float heuristic(SearchCell *NodeEnd) 
      {
           float x = (float)(fabs((float)this->m_xcoord - NodeEnd->m_xcoord));
         float y = (float)(fabs((float)this->m_ycoord - NodeEnd->m_ycoord));

          //Good 
         return x + y ;

         // Better
       // return sqrt(x*x+y*y);

        //Best
        // return std::max(x,y);

          //Allway The shortest path
         //return 0.0f;         
      }
};

#include <vector>
#include <windows.h>
#include "game.h"

class PathFinding
{
public:
   PathFinding();
   PathFinding(Game & g){pGame = &g; pMap = &(pGame->getMap());}
   ~PathFinding();
   // Sets Start and End//
   bool FindPath(COORD CurrentPos, COORD TargetPos );
   //Gets next Position//
   COORD NextPathPos();

   bool m_FoundGoal;

private:
	Game * pGame;
	Map * pMap;
   Grid *myGridptr;
   
   typedef std::shared_ptr<COORD> SPv;
   typedef std::shared_ptr<SearchCell> SPsc;

   void AddCell(int x, int y, float newCost, SearchCell *_parent);

   std::shared_ptr<SearchCell> GetNextCell();

   void SearchPath();

   SPsc m_StartCell;
   SPsc m_GoalCell;

   std::vector<SPsc > m_OpenList;
   std::vector<SPsc > m_ClosedList;
   std::vector<SPv > m_PathToGoal;   
};