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
	float colorRed = 255.;
	float colorGreen = 255.;
	float colorBlue = 255.;
};

LINK_ENTITY_TO_CLASS(c_magic_crystal, CMagicCrystal);

void CMagicCrystal::Spawn() {
	pev->solid = SOLID_BBOX;
	SET_MODEL(edict(), STRING(pev->model));
	pev->renderamt = 100;
}

void CMagicCrystal::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	isActive = !isActive;

	if (isActive) {
		pev->rendermode = kRenderTransColor;
		pev->nextthink = gpGlobals->time;
	}
	else {
		pev->rendermode = kRenderNormal;
	}
}

void CMagicCrystal::Think() {
	if (isActive) {
		colorRed = RANDOM_FLOAT(0.0, 255.0);
		colorGreen = RANDOM_FLOAT(0.0, 255.0);
		colorBlue = RANDOM_FLOAT(0.0, 255.0);

		pev->rendercolor = Vector(colorRed, colorGreen, colorBlue);

		pev->nextthink = gpGlobals->time + 1.f;
	}
	else {
		pev->nextthink = 0.0;
	}
}