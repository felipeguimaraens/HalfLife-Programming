#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CTriggerRepeater : public CBaseEntity
{
private:
	float triggerDelay = 1.0f;
	CBaseEntity* target = nullptr;

public:
	void Spawn() override;
	void Think();
};

LINK_ENTITY_TO_CLASS(trigger_repeater, CTriggerRepeater);

void CTriggerRepeater::Spawn()
{
	pev->nextthink = gpGlobals->time + triggerDelay;
}

void CTriggerRepeater::Think()
{
	target = UTIL_FindEntityByTargetname(NULL, STRING(pev->target));
	if (target) 
	{
		//ALERT(at_console, "Target found\n");
		target->Use(this, this, USE_TOGGLE, 1);
	}

	pev->nextthink = gpGlobals->time + triggerDelay;
}
