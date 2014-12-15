#pragma once

#include <fstream>
#include "commandLineInterface.h"
using namespace std;
class map
{
	int m_width, m_height;
	char ** m_map;
public:
	map():m_map(0),m_width(0),m_height(0){}

	static char ** new2Dmap(int const & h, int const & w){
		char ** newMap = new char * [h];
		for(int row = 0; row < h; ++row)
			newMap[row] = new char[w];
		return newMap;
	}

	static void delete2Dmap(char ** & a_map, int const & h){
		if(a_map){
			for(int row = 0; row < h; ++row)
				delete[] a_map[row];
			delete a_map;
			a_map = 0;
		}
	}

	bool load(char* a_file);
	int getWidth();
	int getHeight();
	char getAt(int x, int y);
	int getCharXPos(char a_c);
	int getCharYPos(char a_c);
	void setAt(int x, int y, char c);
	map(map const & a_original);
	void release();
	~map();
	void draw(int const & a_x, int const & a_y)const;
	void drawFlippedH(int const & a_x, int const & a_y)const;
	void drawFlippedV(int const & a_x, int const & a_y)const;
	void drawFlippedXY(int const & a_x, int const & a_y)const;
	void drawFlippedCW(int const & a_x, int const & a_y)const;
	void drawFlippedCCW(int const & a_x, int const & a_y)const;
	void flipH();
	void flipV();
	void flipXY();
	void flipCW();
	void flipCCW();
};