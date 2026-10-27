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
	void Explosion();
};

LINK_ENTITY_TO_CLASS(env_fx_effects, fxEffects);

void fxEffects::Spawn() {

}

void fxEffects::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	Explosion();
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
