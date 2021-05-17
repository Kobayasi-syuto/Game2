#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	int mFx, mFy;
	int FireCount;
	CPlayer();
	void Update();
	void Render();

	void Collision(CRectangle *i, CRectangle *y);

	static CPlayer*spInstance;
};

#endif
