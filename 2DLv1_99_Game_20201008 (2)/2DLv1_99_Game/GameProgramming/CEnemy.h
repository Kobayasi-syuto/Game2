#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy : public CRectangle {
public:
	int mFx; //X²•ûŒü‚ÌˆÚ“® -1:¶ 0:ˆÚ“®‚µ‚È‚¢ 1:‰E‚ÖˆÚ“®
	int mFy; //Y²•ûŒü‚ÌˆÚ“® -1:‰º 0:ˆÚ“®‚µ‚È‚¢ 1:ã‚ÖˆÚ“®

	int mFireCount;

	CEnemy();

	void Update();
	bool Collision(const CRectangle &r);
	void Render();

	void Collision(CRectangle *i, CRectangle *y);
};

#endif
