#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CScreenFade : public CBaseEntity {
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};

LINK_ENTITY_TO_CLASS(env_screen_fade, CScreenFade);

void CScreenFade::Spawn() {
	pev->rendercolor = Vector(0.0f, 0.0f, 0.0f);
}

void CScreenFade::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	ALERT(at_console, "Screen fader started \n");
	UTIL_ScreenFadeAll(pev->rendercolor, 3.0f, 2.0f, 255, 0);	
}