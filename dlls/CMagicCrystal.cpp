#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CMagicCrystal: public CBaseEntity
{
public:	
	void Spawn() override;
	void Think() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
	void ChangeColor();
	void Rotate();
private:
	bool isActive = false;
	bool doRotate = true;
	bool doChangeColor = true;
	float rotationSpeed = 25.0f;
	float nextChangeColor = 0.0f;
	float colorRed = 255.;
	float colorGreen = 255.;
	float colorBlue = 255.;
};

LINK_ENTITY_TO_CLASS(c_magic_crystal, CMagicCrystal);

void CMagicCrystal::Spawn() {
	pev->solid = SOLID_BBOX;
	SET_MODEL(edict(), STRING(pev->model));
	pev->renderamt = 156;
	pev->rendermode = kRenderNormal;
	pev->avelocity.z = rotationSpeed * M_PI / 180;

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
	if (doRotate) Rotate();
	if (doChangeColor && gpGlobals->time > nextChangeColor)
		ChangeColor();

	pev->nextthink = gpGlobals->time;	
}

void CMagicCrystal::Rotate() {
	pev->angles = pev->angles + pev->avelocity;
}

void CMagicCrystal::ChangeColor() {
	nextChangeColor = gpGlobals->time + 1.0f;
	if (pev->rendermode == kRenderNormal) pev->rendermode = kRenderTransColor;

	colorRed = RANDOM_FLOAT(0.0, 255.0);
	colorGreen = RANDOM_FLOAT(0.0, 255.0);
	colorBlue = RANDOM_FLOAT(0.0, 255.0);

	pev->rendercolor = Vector(colorRed, colorGreen, colorBlue);
}