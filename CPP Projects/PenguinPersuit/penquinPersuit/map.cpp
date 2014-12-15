#include "map.h"
static char ** new2DMap(int const & h, int const & w)
{
	char ** newMap = new char * [h];
	for(int row = 0; row < h; row++)
		newMap[row] = new char[w];
	return newMap;
}

static void delete2DMap(char** & a_map, int const & h)
{
	if(a_map)
	{
		for(int row = 0; row < h; row++)
			delete a_map[row];
		delete a_map;
	}
}

//Copy constructor
map::map(map const & original)
{
	m_width = original.m_width;
	m_height = original.m_height;
	m_map = new2DMap(m_height, m_width);
	for(int row = 0; row < m_height; row++){
		for(int col = 0; col < m_width; col++){
			m_map[row][col] = original.m_map[row][col];
		}
	}
}
void map::release()
{
	delete2DMap(m_map,m_height);
	m_height = 0;
	m_width = 0;
}
map::~map()
{
	release();
}
bool map::load(char * a_file)
{
	ifstream in(a_file);
	if(!in.good())	return false;
	// puts the first 2 tokens from the file into m_width/m_height
	in >> m_width >> m_height;
	m_map = new2Dmap(m_height, m_width);
	int x = 0, y = 0;
	char data;
	bool finished = false;
	while(in.good() && !finished) {
		data = in.get();
		if(data == '\n' || data == '\r')
			continue;
		m_map[y][x] = data;
		++x;
		if(x >= m_width) {
			x = 0;
			++y;
			if(y >= m_height)
				finished = true;
		}
	}
	in.close();
	return true;
}

int map::getWidth()
{
	return m_width;
}

int map::getHeight()
{
	return m_height;
}

char map::getAt(int a_x, int a_y)
{
	return m_map[a_y][a_x];
}

void map::setAt(int a_x, int a_y, char a_c)
{
	m_map[a_y][a_x] = a_c;
}

void map::flipH()
{	
		for(int row = 0; row < m_height; ++row){
			for(int col = 0; col < m_width/2; ++col){
				char temp = m_map[row][col];
				m_map[row][col] = m_map[row][m_width-1-col];
				m_map[row][m_width-1-col] = temp;
			}
		}
}
void map::flipV()
{	
		for(int row = 0; row < m_height/2; ++row){
			for(int col = 0; col < m_width; ++col){
				char temp = m_map[row][col];
				m_map[row][col] = m_map[m_height-1-row][col];
				m_map[m_height-1-row][col] = temp;
			}
		}
}
int map::getCharXPos(char a_c)
{
	for(int row = 0; row < m_height; ++row){
		for(int col = 0; col < m_width; ++col){
			if(m_map[row][col] == a_c)
				return col;
		}
	}
	return -1;
}
int map::getCharYPos(char a_c)
{
	for(int row = 0; row < m_height; ++row){
		for(int col = 0; col < m_width; ++col){
			if(m_map[row][col] == a_c)
				return row;
		}
	}
	return -1;
}
void map::flipXY()
{		
		char ** newMap = new2DMap(m_width, m_height);
		for(int row = 0; row < m_height; ++row){
			for(int col = 0; col < m_width; ++col){
				newMap[col][row] = m_map[row][col];
			}
		}
		delete2DMap(m_map, m_height);
		m_map = newMap;

		int temp = m_width;
		m_width = m_height;
		m_height = temp;
}
void map::flipCW()
{		
	flipXY();
	flipH();
}
void map::flipCCW()
{		
	flipXY();
	flipV();
}
void map::draw(int const & a_x, int const & a_y) const
{

	for(int row = 0; row < m_width; row++){
		gotoxy(a_x, a_y + row);
		for(int col = 0; col < m_height; col++)
		{
			char c = m_map[row][col];
			if(c == '#')
				setcolor(COLOR_BLUE, COLOR_BLUE);
			else if(c == '.')
				setcolor(COLOR_WHITE, COLOR_WHITE);
			printf("%c", c);
		}
			printf("\n");
	}


}
void map::drawFlippedH(int const & a_x, int const & a_y)const
{
	for(int row = 0; row < m_height; row++){
		gotoxy(a_x, a_y + row);
		for(int col = 0; col < m_width; col++){
			putchar(m_map[row][m_width - 1 - col]);
		}
	}
}
void map::drawFlippedV(int const & a_x, int const & a_y)const
{
	for(int row = 0; row < m_height; row++){
		gotoxy(a_x, a_y + row);
		for(int col = 0; col < m_width; col++){
			putchar(m_map[m_height - 1 - row][col]);
		}
	}
}
void map::drawFlippedXY(int const & a_x, int const & a_y)const
{
	for(int row = 0; row < m_width; row++){
		gotoxy(a_x, a_y + row);
		for(int col = 0; col < m_height; col++){
			putchar(m_map[col][row]);
		}
	}
}
void map::drawFlippedCW(int const & a_x, int const & a_y)const
{
	for(int row = 0; row < m_width; row++){
		gotoxy(a_x, a_y + row);
		for(int col = 0; col < m_height; col++){
			putchar(m_map[col][m_width - 1 - row]);
		}
	}
}
void map::drawFlippedCCW(int const & a_x, int const & a_y) const
{
	for(int row = 0; row < m_width; row++){
		gotoxy(a_x, a_y + row);
		for(int col = 0; col < m_height; col++){
			putchar(m_map[m_height - 1 - col][row]);
		}
	}
}