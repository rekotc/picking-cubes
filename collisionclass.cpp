#include "collisionclass.h"


CollisionClass::CollisionClass()
{
	m_ClosestId = -1;
	m_SelectedId = -1;
	m_LastSelectedId = -1;
	m_HoverId = -1;
	m_LastHoverId = -1;
	m_tMinDistance = 999999999;
	wasClicked = false;
}


CollisionClass::~CollisionClass()
{
}

void CollisionClass::setClosestId(int id)
{
	m_ClosestId = id;
}

int CollisionClass::getClosestId()
{
	return m_ClosestId;
}

int CollisionClass::getCurrentSelectedId()
{
	return m_SelectedId;
}

void CollisionClass::setCurrentSelectedId(int id)
{
	m_SelectedId = id;

}

int CollisionClass::getCurrentHoverId()
{
	return m_HoverId;
}

void CollisionClass::setCurrentHoverId(int id)
{
	m_HoverId = id;

}


void CollisionClass::setCurrentMinDistance(double mindistance)
{
	m_tMinDistance = mindistance;

}

int CollisionClass::getLastSelectedId()
{
	return m_LastSelectedId;
}

void CollisionClass::setLastSelectedId(int id)
{
	m_LastSelectedId = id;

}

int CollisionClass::getLastHoverId()
{
	return m_LastHoverId;
}

void CollisionClass::setLastHoverId(int id)
{
	m_LastHoverId = id;

}


void CollisionClass::setClicked(bool c)
{
	wasClicked = c;

}

bool CollisionClass::getClicked(){
	return wasClicked;
}

int CollisionClass::getCurrentMinDistance()
{
	return m_tMinDistance;
}

