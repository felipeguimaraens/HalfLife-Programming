#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CCameraFollow : public CBaseEntity {
	void Spawn() override;
	void Think() override;
};

LINK_ENTITY_TO_CLASS(func_camera_follow, CCameraFollow);

void CCameraFollow::Spawn() {
	SET_MODEL(edict(), STRING(pev->model));
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;
	pev->avelocity.y = 15.0f;	

	pev->nextthink = gpGlobals->time + 10.f;
};

void CCameraFollow::Think() {
	CBaseEntity* player = UTIL_PlayerByIndex(1);

	TraceResult tracer;
	UTIL_TraceLine(pev->origin, player->pev->origin, dont_ignore_monsters, edict(), &tracer);

	if (tracer.pHit == player->edict()) {
		Vector toPlayer = (player->pev->origin - pev->origin).Normalize();
		pev->angles.y = UTIL_VecToYaw(toPlayer);
	}

	pev->nextthink = pev->ltime + 0.01f;
};