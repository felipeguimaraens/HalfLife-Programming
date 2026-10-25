#include <extdll.h>
#include <util.h>
#include <cbase.h>

class CScreenFade : public CBaseEntity {
	void Spawn() override;
	void Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) override;
};

LINK_ENTITY_TO_CLASS(env_screen_fade, CScreenFade);

void CScreenFade::Spawn() {}

void CScreenFade::Use(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value) {
	ALERT(at_console, "Screen fader started. Duration:%.2f, FadeHold:%.2f \n", pev->speed, pev->armorvalue);
	UTIL_ScreenFadeAll(pev->rendercolor, pev->speed, pev->armorvalue, 255, 0);
}