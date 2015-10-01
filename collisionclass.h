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

	int getClosestId();
	int getCurrentSelectedId();
	int getCurrentHoverId();
	int getCurrentMinDistance();
	int getLastSelectedId();
	int getLastHoverId();
	

	void setClosestId(int);
	void setCurrentSelectedId(int);
	void setCurrentHoverId(int);
	void setCurrentMinDistance(double);
	void setLastSelectedId(int);
	void setLastHoverId(int);
	void setClicked(bool);
	bool getClicked();

	
private:

	int m_ClosestId, m_SelectedId, m_LastSelectedId, m_HoverId, m_LastHoverId;
	
	bool wasClicked;
	double m_tMinDistance;
};

#endif