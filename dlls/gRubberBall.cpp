#include "gRubberBall.h"



void CRubberBall::Spawn()
{
	ALERT(at_console, "Spawned rubber ball! \n");
	Precache();
	//CGrenade::Spawn(); test's sake

	pev->movetype = MOVETYPE_BOUNCE;
	pev->classname = MAKE_STRING("rubberball");

	pev->solid = SOLID_BBOX;

	SET_MODEL(ENT(pev), "models/big_rock.mdl");
	UTIL_SetSize(pev, Vector(0, 0, 0), Vector(0, 0, 0));

	pev->dmg = 100;
	m_fRegisteredSound = false;
}

LINK_ENTITY_TO_CLASS(rubberball, CRubberBall);

void CRubberBall::Precache() {
	PRECACHE_MODEL("models/big_rock.mdl");
}