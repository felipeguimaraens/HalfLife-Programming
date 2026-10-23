#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CFirstAnim : public CBaseAnimating
{
	void Spawn() override;
	void Precache() override;
	void Think() override;
};

LINK_ENTITY_TO_CLASS(env_first_anim, CFirstAnim);

void CFirstAnim::Spawn() {
	Precache();
	SET_MODEL(edict(), "models/barney.mdl");

	pev->sequence = LookupSequence("run");
	pev->nextthink = gpGlobals->time;
}

void CFirstAnim::Precache() {
	PRECACHE_MODEL("models/barney.mdl");
}

void CFirstAnim::Think() {
	pev->frame += 1.0f;
	if (pev->frame >= 255)
		pev->frame = 0.0;

	pev->nextthink = gpGlobals->time + 0.01f;
}