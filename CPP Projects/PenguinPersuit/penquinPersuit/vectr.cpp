#include "vectr.h"
Vectr::Vectr()
{
	m_list = 0;
	m_size = 0;
	m_allocated = 0;
}

Vectr::~Vectr()
{
	delete m_list;
	m_size = 0;
	m_allocated = 0;
}

void Vectr::add(void * a_item)
{
	if(m_size >= m_allocated)
	{
		int newSize = (!m_allocated)?1:m_allocated*2;
		void ** newList = new void * [newSize];
		for(int i = 0; i < m_size; ++i)
		{
			newList[i] = m_list[i];
		}
		if(m_list)
		{
			delete m_list;
		}
		m_list = newList;
		m_allocated = newSize;
	}
	m_list[m_size++] = a_item;
}

void * Vectr::get(int a_index)
{
	return m_list[a_index];
}

int Vectr::getSize()
{
	return m_size;
}
