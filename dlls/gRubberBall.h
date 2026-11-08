#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"

class CRubberBall : public CGrenade
{
public:
	void Spawn() override;
};