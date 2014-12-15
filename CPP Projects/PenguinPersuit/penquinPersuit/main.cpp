#include "map.h"
#include <iostream>
using namespace std;

void main()
{
	map m_map;
	m_map.load("helloWorld.txt");
	m_map.draw(0,0);
	char anyKey;
	cin>>anyKey;
	
}
