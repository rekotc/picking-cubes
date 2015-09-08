// Filename: collisionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _COLLISIONCLASS_H_
#define _COLLISIONCLASS_H

#include <math.h>

class CollisionClass
{
public:
	CollisionClass();
	~CollisionClass();

	int getCurrentId();
	int getCurrentMinDistance();
	int getLastId();

	void setCurrentId(int);
	void setCurrentMinDistance(double);
	void setLastId(int);
	
private:

	int m_Id, m_lastId;
	double m_tMinDistance;
};

#endif