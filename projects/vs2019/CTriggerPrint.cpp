#pragma once
#include "extdll.h"
#include "util.h"
#include "cbase.h"
class CTriggerPrint : public CBaseEntity
{
public:
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};

LINK_ENTITY_TO_CLASS(trigger_print, CTriggerPrint);

void CTriggerPrint::Spawn()
{
}

void CTriggerPrint::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value)
{
	ALERT(at_console, "%s\n", STRING( pev->message ));
}