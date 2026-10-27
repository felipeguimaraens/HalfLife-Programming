#include <extdll.h>
#include <util.h>
#include <cbase.h>
// Most of effects are pre-cached within weapons.h and effects.h
#include "weapons.h"
#include "effects.h"

class fxEffects: public CBaseEntity
{
public:
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
private:
	// Function for each fx effects
	void Explosion();
	void BeamPoints();
	void Gunshot();
	short fx_type = 0;
	short m_BeamSprite;
};

LINK_ENTITY_TO_CLASS(env_fx_effects, fxEffects);

void fxEffects::Spawn() {
	// Using health to pass paramater from map builder
	fx_type = pev->health;
	// Not mentioned in video series but some messages must have sprite precached apart
	m_BeamSprite = PRECACHE_MODEL("sprites/lgtning.spr");
}

void fxEffects::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	//Returns player and func_button. Pure curiosity... Also without explicity cast to STRING it breakes the game
	//ALERT(at_console, "pActivator.targetname:%s; pCaller.targetname:%s; \n", STRING(pActivator->pev->classname), STRING(pCaller->pev->classname));
	
	// Hack to use one env_fx_effects with multiple buttons
	if (pCaller->pev->armorvalue > 0) {
		fx_type = pCaller->pev->armorvalue;
		ALERT(at_console, "ArmorValue: %.2f and %i \n", pCaller->pev->armorvalue, fx_type);
	}
	
	switch (fx_type)
	{
		case 1: Explosion(); break;
		case 2: BeamPoints(); break;
		case 3: Gunshot(); break;
	}

	
}

void fxEffects::Explosion() {
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
	WRITE_BYTE(TE_EXPLOSION);
	WRITE_COORD(pev->origin.x);
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z);
	WRITE_SHORT(g_sModelIndexFireball);
	WRITE_BYTE(20);
	WRITE_BYTE(15);
	WRITE_BYTE(TE_EXPLFLAG_NONE);
	MESSAGE_END();
}

void fxEffects::BeamPoints() {
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
	WRITE_BYTE(TE_BEAMPOINTS);
	WRITE_COORD(pev->origin.x);
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z - 64.0f);
	WRITE_COORD(pev->origin.x);
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z + 64.0f);
	WRITE_SHORT(m_BeamSprite);
	WRITE_BYTE(0);
	WRITE_BYTE(100);
	WRITE_BYTE(60);
	WRITE_BYTE(50);
	WRITE_BYTE(20);
	WRITE_BYTE(255);
	WRITE_BYTE(160);
	WRITE_BYTE(0);
	WRITE_BYTE(255);
	WRITE_BYTE(50);
	MESSAGE_END();
}

void fxEffects::Gunshot() {
	MESSAGE_BEGIN(MSG_PVS, SVC_TEMPENTITY, pev->origin);
	WRITE_BYTE(TE_GUNSHOT);
	WRITE_COORD(pev->origin.x);
	WRITE_COORD(pev->origin.y);
	WRITE_COORD(pev->origin.z);
	MESSAGE_END();
}
