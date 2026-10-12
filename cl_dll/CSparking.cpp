#pragma once
#include "extdll.h"
#include "util.h"
#include "cbase.h"
class CSparking : public CBaseEntity
{
private:
	bool canSpark = false;

public:
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
	void Think() override;
};

LINK_ENTITY_TO_CLASS(env_spaInrking, CSparking);

void CSparking::Spawn()
{
}

void CSparking::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	canSpark = !canSpark;
	pev->nextthink = gpGlobals->time;
}

void CSparking::Think()
{
	if (canSpark) {
		UTIL_Sparks(pev->origin);
	}

	pev->nextthink = gpGlobals->time + pev->speed;
}
