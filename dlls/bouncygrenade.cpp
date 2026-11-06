#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "weapons.h"

class bouncygrenade : public CGrenade
{
public:
	void Spawn() override;
};

void bouncygrenade::Spawn() {
	pev->movetype = MOVETYPE_BOUNCE;
	pev->classname = MAKE_STRING("bouncygrenade");

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/can.mdl");
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pev->dmg = 100;
	m_fRegisteredSound = false;
}
