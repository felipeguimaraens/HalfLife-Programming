#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CScientistAnim : public CBaseAnimating {
public:
	void Spawn() override;
	void Precache() override;
	void Think() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;

private:
	int mHeadType = 0;
};

LINK_ENTITY_TO_CLASS(env_scientist_test, CScientistAnim);

void CScientistAnim::Spawn()
{
	Precache();
	SET_MODEL(edict(), "models/scientist.mdl");
	pev->angles.y = 180.0f;

	pev->sequence = LookupSequence("beatdoor");
	ResetSequenceInfo();
	m_fSequenceLoops = true;
	pev->nextthink = gpGlobals->time;
}

void CScientistAnim::Precache()
{
	PRECACHE_MODEL("models/scientist.mdl");
}

void CScientistAnim::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	mHeadType++;

	if (mHeadType > 3) 
		mHeadType = 0;

	SetBodygroup(1, mHeadType);
}

void CScientistAnim::Think() {
	StudioFrameAdvance();
	pev->nextthink = gpGlobals->time + 0.01f;
}