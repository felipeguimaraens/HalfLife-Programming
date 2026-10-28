#include <extdll.h>
#include <util.h>
#include <cbase.h>
#include <effects.h>

class CLaserCustom : public CBeam
{
	void Spawn() override;
	CBeam* m_pBeam;
};

LINK_ENTITY_TO_CLASS(env_custom_laser, CLaserCustom);

void CLaserCustom::Spawn()
{
	TraceResult tr;
	Vector endvec = pev->origin + Vector(0.0,1.0,0.0) * 2048;
	UTIL_TraceLine(pev->origin, endvec, dont_ignore_monsters, edict(), &tr);

	m_pBeam = CBeam::BeamCreate("sprites/laserbeam.spr", 5);
	m_pBeam->PointsInit(pev->origin, endvec);
	m_pBeam->SetColor(255, 0, 0);
	m_pBeam->SetScrollRate(200);
	m_pBeam->SetBrightness(50);
}

