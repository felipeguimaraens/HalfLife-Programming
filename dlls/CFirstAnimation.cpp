#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CFirstAnim : public CBaseAnimating
{
public:
	void Spawn() override;
	void Precache() override;
	void Think() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
private:
	int mAnimSequence = 0;
};

LINK_ENTITY_TO_CLASS(env_first_anim, CFirstAnim);

void CFirstAnim::Spawn() {
	Precache();
	SET_MODEL(edict(), "models/barney.mdl");
	pev->angles.y = 270.0f;

	pev->sequence = LookupSequence("run");
	ResetSequenceInfo();
	pev->nextthink = gpGlobals->time;
}

void CFirstAnim::Precache() {
	PRECACHE_MODEL("models/barney.mdl");
}

void CFirstAnim::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	if (mAnimSequence <= 3)
		mAnimSequence++;
	else
		mAnimSequence = 0;

	switch (mAnimSequence)
	{
	case 0: pev->sequence = LookupSequence("idle"); break;
	case 1: pev->sequence = LookupSequence("run"); break;
	case 2: pev->sequence = LookupSequence("dieviolent"); break;
	case 3: pev->sequence = LookupSequence("stuffed_in_vent"); break;
	}
}

void CFirstAnim::Think() {
	
	StudioFrameAdvance();
	pev->nextthink = gpGlobals->time + 0.01f;
}