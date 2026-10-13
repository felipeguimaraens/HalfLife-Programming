#pragma once
#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CFader : public CBaseEntity
{
private:
	bool fade = true;
public:
	void Spawn() override;
	void Think() override;
};

LINK_ENTITY_TO_CLASS(func_fader, CFader);

void CFader::Spawn() {
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSHSTEP;
	SET_MODEL(edict(), STRING(pev->model));
	pev->renderamt = 128;
	pev->rendermode = kRenderTransTexture;

	pev->nextthink = gpGlobals->time;
};

void CFader::Think() {

	if (pev->renderamt <= 0 || pev->renderamt >= 255) {
		fade = !fade;
	}

	if (fade) {
		pev->renderamt += 1.0f;
	}
	else {
		pev->renderamt -= 1.0f;
	}

	pev->nextthink = gpGlobals->time + 0.01f;
};

