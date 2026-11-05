#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "player.h"

class cFlare : public CBasePlayerWeapon
{
	void Spawn() override;
	bool GetItemInfo(ItemInfo* p) override;
	void Precache() override;

	void PrimaryAttack() override;
	void SecondaryAttack() override;
	void WeaponIdle() override;
	bool Deploy() override;

	bool UseDecrement() override
	{
	#if defined(CLIENT_WEAPONS)
			return true;
	#else
			return false;
	#endif
	}

	bool m_fRegisteredSound;
};

LINK_ENTITY_TO_CLASS(weapon_flare, cFlare);

void cFlare::Spawn() {
	Precache();
	m_iId = WEAPON_FLARE;
	SET_MODEL(ENT(pev), "models/w_grenade.mdl");

#ifndef CLIENT_DLL
	pev->dmg = gSkillData.plrDmgHandGrenade;
#endif

	m_iDefaultAmmo = FLARE_DEFAULT_GIVE;

	FallInit();
}

bool cFlare::GetItemInfo(ItemInfo* p) {
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "Flare";
	p->iMaxAmmo1 = FLARE_MAX_CARRY;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iId = m_iId = WEAPON_FLARE;
	p->iSlot = 4;
	p->iPosition = 4;
	p->iWeight = FLARE_WEIGHT;
	p->iFlags = ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;

	return true;
}

// Copied from handgrenade.cpp

void cFlare::PrimaryAttack()
{
	ALERT(at_console, "Primary attack pressed \n");
	if (0 == m_flStartThrow && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0)
	{
		m_flStartThrow = gpGlobals->time;
		m_flReleaseThrow = 0;

		SendWeaponAnim(HANDGRENADE_PINPULL);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
	}
}

void cFlare::SecondaryAttack()
{
	ALERT(at_console, "Secondary attack pressed \n");
}

void cFlare::Precache()
{
	PRECACHE_MODEL("models/w_grenade.mdl");
	PRECACHE_MODEL("models/v_grenade.mdl");
	PRECACHE_MODEL("models/p_grenade.mdl");
}

bool cFlare::Deploy()
{
	m_flReleaseThrow = -1;
	return DefaultDeploy("models/v_grenade.mdl", "models/p_grenade.mdl", HANDGRENADE_DRAW, "crowbar");
}

void cFlare::WeaponIdle()
{
	if (m_flReleaseThrow == 0 && 0 != m_flStartThrow)
		m_flReleaseThrow = gpGlobals->time;

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (0 != m_flStartThrow)
	{
		Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;

		if (angThrow.x < 0)
			angThrow.x = -10 + angThrow.x * ((90 - 10) / 90.0);
		else
			angThrow.x = -10 + angThrow.x * ((90 + 10) / 90.0);

		static float flMultiplier = 6.5f;
		float flVel = (90 - angThrow.x) * flMultiplier;
		if (flVel > 1000)
			flVel = 1000;

		UTIL_MakeVectors(angThrow);

		Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 16;

		Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;

		// alway explode 3 seconds after the pin was pulled
		float time = m_flStartThrow - gpGlobals->time + 3.0;
		if (time < 0)
			time = 0;

		CGrenade::ShootFlare(m_pPlayer->pev, vecSrc, vecThrow, time);
		//CGrenade::ShootTimed(m_pPlayer->pev, vecSrc, vecThrow, time);

		if (flVel < 500)
		{
			SendWeaponAnim(HANDGRENADE_THROW1);
		}
		else if (flVel < 1000)
		{
			SendWeaponAnim(HANDGRENADE_THROW2);
		}
		else
		{
			SendWeaponAnim(HANDGRENADE_THROW3);
		}

		// player "shoot" animation
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);

		// m_flReleaseThrow = 0;
		m_flStartThrow = 0;
		m_flNextPrimaryAttack = GetNextAttackDelay(0.5);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;

		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;

		if (0 == m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			// just threw last grenade
			// set attack times in the future, and weapon idle in the future so we can see the whole throw
			// animation, weapon idle will automatically retire the weapon for us.
			m_flTimeWeaponIdle = m_flNextSecondaryAttack = m_flNextPrimaryAttack = GetNextAttackDelay(0.5); // ensure that the animation can finish playing
		}
		return;
	}
	else if (m_flReleaseThrow > 0)
	{
		// we've finished the throw, restart.
		m_flStartThrow = 0;

		if (0 != m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			SendWeaponAnim(HANDGRENADE_DRAW);
		}
		else
		{
			RetireWeapon();
			return;
		}

		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15);
		m_flReleaseThrow = -1;
		return;
	}

	if (0 != m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		int iAnim;
		float flRand = UTIL_SharedRandomFloat(m_pPlayer->random_seed, 0, 1);
		if (flRand <= 0.75)
		{
			iAnim = HANDGRENADE_IDLE;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat(m_pPlayer->random_seed, 10, 15); // how long till we do this again.
		}
		else
		{
			iAnim = HANDGRENADE_FIDGET;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 75.0 / 30.0;
		}

		SendWeaponAnim(iAnim);
	}
}