#include "CustomScientist.h"

LINK_ENTITY_TO_CLASS(monster_custom_scientist, CustomScientist);

void CustomScientist::Spawn() {
	CScientist::Spawn();
}

void CustomScientist::TraceAttack(entvars_t* pevAttacker, float flDamage, Vector vecDir, TraceResult* ptr, int bitsDamageType)
{
	if (ptr->iHitgroup != 0)
	{
		switch (ptr->iHitgroup)
		{
		case HITGROUP_HEAD: ALERT(at_console, "Hit detected on head!"); break;
		case HITGROUP_CHEST: ALERT(at_console, "Hit detected on chest!"); break;
		case HITGROUP_STOMACH: ALERT(at_console, "Hit detected on stomach!"); break;
		case HITGROUP_LEFTARM: ALERT(at_console, "Hit detected on left arm!"); break;
		case HITGROUP_RIGHTARM: ALERT(at_console, "Hit detected on right arm!"); break;
		case HITGROUP_LEFTLEG: ALERT(at_console, "Hit detected on left leg!"); break;
		case HITGROUP_RIGHTLEG: ALERT(at_console, "Hit detected on right leg!"); break;
		}
	}
}