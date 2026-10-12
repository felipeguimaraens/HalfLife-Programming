#pragma once
#include "extdll.h"
#include "util.h"
#include "cbase.h"
class CTriggerHeal : public CBaseEntity
{
public:
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};

LINK_ENTITY_TO_CLASS(trigger_heal, CTriggerHeal);

void CTriggerHeal::Spawn()
{
}

void CTriggerHeal::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	ALERT(at_console, "User triggered heal\n");
	if (pActivator->IsPlayer())
	{
		pActivator->pev->health = 100;
	}
}