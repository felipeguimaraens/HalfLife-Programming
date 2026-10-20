#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CCameraFollow : public CBaseEntity {
	void Spawn() override;
	void Think() override;
	CBaseEntity* ScanSphere();
	bool isVisible(CBaseEntity* target);
};

LINK_ENTITY_TO_CLASS(func_camera_follow, CCameraFollow);

void CCameraFollow::Spawn() {
	SET_MODEL(edict(), STRING(pev->model));
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;
	pev->avelocity.y = 15.0f;	

	pev->nextthink = gpGlobals->time;
};

void CCameraFollow::Think() {
	CBaseEntity* player = ScanSphere();

	if (player) {
		Vector toPlayer = (player->pev->origin - pev->origin).Normalize();
		pev->angles.y = UTIL_VecToYaw(toPlayer);
	}

	pev->nextthink = pev->ltime + 0.01f;
};

CBaseEntity* CCameraFollow::ScanSphere()
{
	CBaseEntity* target_in_area = nullptr;
	while (target_in_area = UTIL_FindEntityInSphere(target_in_area, pev->origin, 256.0f)){
		
		if (!target_in_area->IsPlayer())
			continue;

		if (isVisible(target_in_area))
			return target_in_area;
	}

	return nullptr;
};

bool CCameraFollow::isVisible(CBaseEntity* target) {
	TraceResult tracer;
	UTIL_TraceLine(pev->origin, target->pev->origin, dont_ignore_monsters, edict(), &tracer);

	if (tracer.pHit == target->edict())
		return true;
	else
		false;
};