#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "explode.h"

class CCompExplosive : public CBaseEntity
{
private:
	bool isAlive = true;

public:
	void Spawn() override;
	bool TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType) override;
};

LINK_ENTITY_TO_CLASS(func_explosive_comp, CCompExplosive);

void CCompExplosive::Spawn() {
	pev->takedamage = true;
	pev->health = 50;
	
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSHSTEP;
	SET_MODEL(edict(), STRING( pev->model ));
}

bool CCompExplosive::TakeDamage(entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType)
{
	if (isAlive) {
		pev->health -= flDamage;
		if (pev->health <= 0) {
			isAlive = false;
			Vector comp_centerPoint = pev->origin + (pev->maxs + pev->mins) * 0.5f;
			ExplosionCreate(comp_centerPoint, pev->angles, edict(), 50, true);
		}

		return 1;
	} else {
		return 0;
	}
}

