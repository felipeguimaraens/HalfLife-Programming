#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CMagicCrystal: public CBaseEntity
{
public:	
	void Spawn() override;
	void Think() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
private:
	bool isActive = false;
};

LINK_ENTITY_TO_CLASS(c_magic_crystal, CMagicCrystal);

void CMagicCrystal::Spawn() {
	pev->solid = SOLID_BBOX;
	SET_MODEL(edict(), STRING(pev->model));

	// Attributes only valid when active
	pev->renderamt = 100;
	pev->rendercolor.x = 255;
	pev->rendercolor.y = 128;
	pev->rendercolor.z = 128;

	pev->nextthink = gpGlobals->time;
}

void CMagicCrystal::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	isActive = !isActive;

	if (isActive) {
		pev->rendermode = kRenderTransColor;
	}
	else {
		pev->rendermode = kRenderNormal;
	}
}

void CMagicCrystal::Think() {
	pev->nextthink = gpGlobals->time + 1.f;
}