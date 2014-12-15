#pragma once
class Vectr
{
private:
	void ** m_list;
	int m_size;
	int m_allocated;
public:
	Vectr();
	void add(void * a_item);
	void * get(int a_index);
	int getSize();
	~Vectr();
};
