#pragma once
#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CFader : public CBaseEntity
{
public:
	void Spawn() override;
	// Needs to use DLLEXPORT otherwise it won't find the func during running
	DLLEXPORT void ThinkTransparent();
	DLLEXPORT void ThinkOpaque();
};

LINK_ENTITY_TO_CLASS(func_fader, CFader);

void CFader::Spawn() {
	pev->solid = SOLID_BSP;
	pev->movetype = MOVETYPE_PUSHSTEP;
	SET_MODEL(edict(), STRING(pev->model));
	pev->renderamt = 128;
	pev->rendermode = kRenderTransTexture;

	SetThink(&CFader::ThinkTransparent);
	pev->nextthink = gpGlobals->time;
};

void CFader::ThinkTransparent()
{
	pev->renderamt -= 1.0f;

	if (pev->renderamt <= 0)
	{
		pev->renderamt = 0;
		SetThink(&CFader::ThinkOpaque);
	}

	pev->nextthink = gpGlobals->time + 0.01f;
};

void CFader::ThinkOpaque()
{
	pev->renderamt += 1.0f;

	if (pev->renderamt >= 255)
	{
		pev->renderamt = 255;
		SetThink(&CFader::ThinkTransparent);
	}

	pev->nextthink = gpGlobals->time + 0.01f;
};

