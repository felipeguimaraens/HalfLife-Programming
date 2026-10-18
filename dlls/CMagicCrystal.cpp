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
	bool doRotate = true;
	float rotationSpeed = 90.0f;
	float nextChangeColor = 0.0f;
	float colorRed = 255.;
	float colorGreen = 255.;
	float colorBlue = 255.;
};

LINK_ENTITY_TO_CLASS(c_magic_crystal, CMagicCrystal);

void CMagicCrystal::Spawn() {
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSH;
	SET_MODEL(edict(), STRING(pev->model));
	pev->renderamt = 156;
	pev->rendermode = kRenderNormal;
	if (doRotate)
		pev->avelocity.z = rotationSpeed;

	if (isActive)
		pev->nextthink = gpGlobals->time;
}

void CMagicCrystal::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	isActive = !isActive;

	if (isActive)
		pev->nextthink = gpGlobals->time;
	else {
		pev->rendermode = kRenderNormal;
		pev->nextthink = 0;
	}
}

void CMagicCrystal::Think() {
	if (pev->rendermode == kRenderNormal)
		pev->rendermode = kRenderTransColor;

	colorRed = RANDOM_FLOAT(0.0, 255.0);
	colorGreen = RANDOM_FLOAT(0.0, 255.0);
	colorBlue = RANDOM_FLOAT(0.0, 255.0);

	pev->rendercolor = Vector(colorRed, colorGreen, colorBlue);

	pev->nextthink = pev->ltime + 1.0f;
}
