#include "collisionclass.h"


CollisionClass::CollisionClass()
{
	m_Id = -1;
	m_lastId = -1;
	m_tMinDistance = INFINITY;

}


CollisionClass::~CollisionClass()
{
}


int CollisionClass::getCurrentId()
{
	return m_Id;
}

int CollisionClass::getCurrentMinDistance()
{
	return m_tMinDistance;
}

void CollisionClass::setCurrentId(int id)
{
	m_Id = id;

}

void CollisionClass::setCurrentMinDistance(double mindistance)
{
	m_tMinDistance = mindistance;

}

int CollisionClass::getLastId()
{
	return m_lastId;
}

void CollisionClass::setLastId(int id)
{
	m_lastId = id;

}
