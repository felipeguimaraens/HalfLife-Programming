#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CTrampoline : public CBaseEntity {
public:
	void Spawn() override;
	void Touch(CBaseEntity* pOther) override;
};

LINK_ENTITY_TO_CLASS(func_trampoline, CTrampoline);

void CTrampoline::Spawn() {
	pev->solid = SOLID_TRIGGER;
	pev->movetype = MOVETYPE_PUSH;
	SET_MODEL(edict(), STRING(pev->model));
};

void CTrampoline::Touch(CBaseEntity* pOther) {
	pOther->pev->velocity.z += 400;
};