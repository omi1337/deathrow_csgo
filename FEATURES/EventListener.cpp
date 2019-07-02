#include "../includes.h"

#include "../UTILS/interfaces.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/IEngine.h"
#include "../SDK/CBaseWeapon.h"
#include "../SDK/CBaseEntity.h"
#include "../SDK/CGlobalVars.h"
#include "../SDK/ConVar.h"
#include "../SDK/ISurface.h"
#include "../UTILS/render.h"
#include "../FEATURES/Backtracking.h"
#include "../FEATURES/Visuals.h"
#include "../FEATURES/Aimbot.h"
#include "../sounds.h"
#include "EventListener.h"
#include <playsoundapi.h>
#pragma comment(lib, "Winmm.lib")

CGameEvents::ItemPurchaseListener item_purchase_listener;
CGameEvents::PlayerHurtListener player_hurt_listener;
CGameEvents::BulletImpactListener bullet_impact_listener;
CGameEvents::PlayerDeathListener player_death_listener;
CGameEvents::WeaponFiredListener weapon_fired_listener;

void CGameEvents::InitializeEventListeners()
{
	INTERFACES::GameEventManager->AddListener(&item_purchase_listener, "item_purchase", false);
	INTERFACES::GameEventManager->AddListener(&player_hurt_listener, "player_hurt", false);
	INTERFACES::GameEventManager->AddListener(&bullet_impact_listener, "bullet_impact", false);
	INTERFACES::GameEventManager->AddListener(&player_death_listener, "player_death", false);
	INTERFACES::GameEventManager->AddListener(&weapon_fired_listener, "weapon_fire", false);
}

char* HitgroupToName(int hitgroup)
{
	switch (hitgroup)
	{
	case HITGROUP_HEAD:
		return "head";
	case HITGROUP_LEFTLEG:
		return "left leg";
	case HITGROUP_RIGHTLEG:
		return "right leg";
	case HITGROUP_STOMACH:
		return "stomach";
	default:
		return "body";
	}
}

float randnum(int Min, int Max)
{
	return ((rand() % (Max - Min)) + Min);
}

void CGameEvents::WeaponFiredListener::FireGameEvent(SDK::IGameEvent* game_event)
{
	if (!game_event)
		return;

	if (!(INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame()))
		return;

	int iUser = INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid"));

	auto engine_local_player = INTERFACES::Engine->GetLocalPlayer();

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!engine_local_player || !local_player || !iUser)
		return;

	auto event_weapon = game_event->GetString("weapon");

	if (!event_weapon)
		return;

	if (event_weapon == "weapon_unknown")
		return;

	auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex()));

	if (!weapon)
		return;

	if (engine_local_player == iUser)
	{
		shots_fired[target]++;

		if (SETTINGS::settings.info_bool)
		{
			if (didMiss && GoodestWeapon(event_weapon))
			{
				if (weapon->GetItemDefenitionIndex() == SDK::ItemDefinitionIndex::WEAPON_KNIFE
					|| weapon->GetItemDefenitionIndex() == SDK::ItemDefinitionIndex::WEAPON_KNIFE_T
					|| weapon->GetItemDefenitionIndex() == SDK::ItemDefinitionIndex::WEAPON_HEGRENADE
					|| weapon->GetItemDefenitionIndex() == SDK::ItemDefinitionIndex::WEAPON_INC
					|| weapon->GetItemDefenitionIndex() == SDK::ItemDefinitionIndex::WEAPON_SMOKEGRENADE)
					return;	

				static auto nospread = INTERFACES::cvar->FindVar("weapon_accuracy_nospread")->GetBool();
				Vector local_position = local_player->GetVecOrigin() + local_player->GetViewOffset();

				if (!nospread)
				{
					if (rand() % 100 < 50)
					{
						INTERFACES::cvar->ConsoleColorPrintf(CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "[deathrow - miss log] ");
						GLOBAL::Msg("missed shot due to spread.    \n");
					}
					else
					{
						INTERFACES::cvar->ConsoleColorPrintf(CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "[deathrow - miss log] ");
						GLOBAL::Msg("missed shot due to bad resolve.    \n");
					}
				}
			}

			didMiss = true;
		}
	}
}

void CGameEvents::PlayerHurtListener::FireGameEvent(SDK::IGameEvent* game_event)
{
	if (!game_event)
		return;

	if (!(INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame()))
		return;

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player)
		return;

	auto victim = INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid"));
	auto entity = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid")));
	if (!entity)
		return;

	auto entity_attacker = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("attacker")));
	if (!entity_attacker)
		return;

	if (entity->GetTeam() == local_player->GetTeam())
		return;

	SDK::player_info_t player_info;
	if (!INTERFACES::Engine->GetPlayerInfo(entity->GetIndex(), &player_info))
		return;

	if (INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("attacker")) == INTERFACES::Engine->GetLocalPlayer() && INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid")) != INTERFACES::Engine->GetLocalPlayer())
	{
		if (SETTINGS::settings.lag_comp_hitbox)
			visuals->lag_comp_hitbox(entity, INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid")));
	}

	SDK::CBaseEntity* hurt = (SDK::CBaseEntity*) INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid")));
	if (SETTINGS::settings.dmg_bool)
	{
		if (strcmp(game_event->GetName(), "player_hurt") == 0) {

			if (hurt != local_player && entity_attacker == local_player) {
				CVisuals::damage_indicator_t DmgIndicator;
				DmgIndicator.dmg = game_event->GetInt("dmg_health");
				DmgIndicator.player = hurt;
				DmgIndicator.earse_time = local_player->GetTickBase() * INTERFACES::Globals->interval_per_tick + 3.f;
				DmgIndicator.initializes = false;

				visuals->dmg_indicator.push_back(DmgIndicator);
			}
		}
	}


	if (entity_attacker == local_player)
	{
		didMiss = false;

		visuals->set_hitmarker_time(INTERFACES::Globals->curtime);
		switch (SETTINGS::settings.hit_sound)
		{
		case 0: break;
		case 1: INTERFACES::Surface->IPlaySound("buttons\\arena_switch_press_02.wav"); break;
		case 2: PlaySoundA(hitsound_wav, NULL, SND_ASYNC | SND_MEMORY); break;	
		case 3: PlaySoundA(argent_fingers_wav, NULL, SND_ASYNC | SND_MEMORY); break;
		case 4: PlaySoundA(bame_wav, NULL, SND_ASYNC | SND_MEMORY); break;
		case 5: PlaySoundA(bubble_wav, NULL, SND_ASYNC | SND_MEMORY); break;
		case 6: PlaySoundA(miau__online_audio_converter_com__wav, NULL, SND_ASYNC | SND_MEMORY); break;
		case 7: PlaySoundA(cod, NULL, SND_ASYNC | SND_MEMORY); break;
		case 8: PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break;
		case 9: PlaySoundA(keyboard, NULL, SND_ASYNC | SND_MEMORY); break;
		case 10: PlaySoundA(fatality, NULL, SND_ASYNC | SND_MEMORY); break;
		case 11: PlaySoundA(pew, NULL, SND_ASYNC | SND_MEMORY); break;
		}

		if (SETTINGS::settings.info_bool)
		{
			auto pVictim = reinterpret_cast<SDK::CBaseEntity*>(INTERFACES::ClientEntityList->GetClientEntity(victim));

			SDK::player_info_t pinfo;
			INTERFACES::Engine->GetPlayerInfo(pVictim->GetIndex(), &pinfo);

			auto hitbox = game_event->GetInt("hitgroup");
			if (!hitbox)
				return;

			auto damage = game_event->GetInt("dmg_health");
			if (!damage)
				return;

			auto health = game_event->GetInt("health");
			if (!health && health != 0)
				return;

			auto hitgroup = HitgroupToName(hitbox);

			INTERFACES::cvar->ConsoleColorPrintf(CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "[deathrow - damage log] ");

			GLOBAL::Msg("hurt %s in the %s for %d damage.    \n", pinfo.name, hitgroup, damage, pinfo.name, health);
		}
		shots_hit[entity->GetIndex()]++;
	}
}

void CGameEvents::BulletImpactListener::FireGameEvent(SDK::IGameEvent* game_event)
{
	if (!game_event)
		return;

	if (!(INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame()))
		return;

	int iUser = INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid"));

	auto entity = reinterpret_cast<SDK::CBaseEntity*>(INTERFACES::ClientEntityList->GetClientEntity(iUser));

	if (!entity)
		return;

	if (entity->GetIsDormant())
		return;

	float x, y, z;
	x = game_event->GetFloat("x");
	y = game_event->GetFloat("y");
	z = game_event->GetFloat("z");

	UTILS::BulletImpact_t impact(entity, Vector(x, y, z), INTERFACES::Globals->curtime, iUser == INTERFACES::Engine->GetLocalPlayer() ? GREEN : RED);

	visuals->Impacts.push_back(impact);
}

void CGameEvents::ItemPurchaseListener::FireGameEvent(SDK::IGameEvent* game_event)
{
	if (!game_event)
		return;

	if (!(INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame()))
		return;

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player)
		return;

	auto entity = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid")));
	if (!entity)
		return;

	if (entity->GetTeam() == local_player->GetTeam())
		return;

	SDK::player_info_t player_info;
	if (!INTERFACES::Engine->GetPlayerInfo(entity->GetIndex(), &player_info))
		return;

	auto event_weapon = game_event->GetString("weapon");

	if (event_weapon == "weapon_unknown")
		return;

	if (!event_weapon)
		return;

	if (SETTINGS::settings.info_bool)
	{
		INTERFACES::cvar->ConsoleColorPrintf(CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "[deathrow - player purchase] ");
		GLOBAL::Msg("%s bought %s    \n", player_info.name, event_weapon);
	}
};


bool CGameEvents::GoodWeapon(const char* weapon)
{
	if (weapon == "taser")
		return false;

	if (weapon == "molotov")
		return false;

	if (weapon == "decoy")
		return false;

	if (weapon == "flashbang")
		return false;

	if (weapon == "hegrenade")
		return false;

	if (weapon == "smokegrenade")
		return false;

	if (weapon == "incgrenade")
		return false;

	if (weapon == "knife")
		return false;

	if (weapon == "unknown")
		return false;

	return true;
}

void CGameEvents::PlayerDeathListener::FireGameEvent(SDK::IGameEvent* game_event)
{
	if (!game_event)
		return;

	if (!(INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame()))
		return;

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player)
		return;

	auto entity = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid")));
	if (!entity)
		return;

	auto attacker = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("attacker")));
	if (!attacker)
		return;

	SDK::player_info_t player_info;
	if (!INTERFACES::Engine->GetPlayerInfo(entity->GetIndex(), &player_info))
		return;

	auto event_weapon = game_event->GetString("weapon");

	if (!event_weapon)
		return;

	if (event_weapon == "weapon_unknown")
		return;

	auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex()));

	if (!weapon)
		return;

	auto health = game_event->GetInt("health");
	if (!health && health != 0) return;

	shots_hit[attacker->GetIndex()]++;
	//MISC::in_game_logger.AddLog(log);
	if (SETTINGS::settings.achievement_earned) {
		if (health <= 0) {

			int negay = rand() % 6;

			switch (negay) {
			case 0:
				INTERFACES::Engine->ClientCmd_Unrestricted("say 1");
				break;

			case 1:
				INTERFACES::Engine->ClientCmd_Unrestricted("say 1?");
				break;
			case 2:
				INTERFACES::Engine->ClientCmd_Unrestricted("say 1");
			case 3:
				INTERFACES::Engine->ClientCmd_Unrestricted("say 1");
			case 4:
				INTERFACES::Engine->ClientCmd_Unrestricted("say 1");
			case 5:
				INTERFACES::Engine->ClientCmd_Unrestricted("say 1");
			case 6:
				INTERFACES::Engine->ClientCmd_Unrestricted("say 1 ");
			}
		}
	}
}

void CGameEvents::RoundStartListener::FireGameEvent(SDK::IGameEvent* game_event)
{
	if (!game_event)
		return;

	if (!(INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame()))
		return;

	auto entity_attacker = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("attacker")));
	if (!entity_attacker)
		return;
	SDK::CBaseEntity* hurt = (SDK::CBaseEntity*) INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetPlayerForUserID(game_event->GetInt("userid")));

	SDK::CBaseEntity* local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player)
		return;
	GLOBAL::NewRound = true;
	if (strcmp(game_event->GetName(), "player_hurt") == 0) {

		if (hurt != local_player && entity_attacker == local_player) {
			//CVisuals::damage_indicator_t DmgIndicator;
			//DmgIndicator.dmg = game_event->GetInt("dmg_health");
			//DmgIndicator.player = hurt;
			//DmgIndicator.earse_time = local_player->GetTickBase() * INTERFACES::Globals->interval_per_tick + 3.f;
			//DmgIndicator.initializes = false;

			//visuals->dmg_indicator.push_back(DmgIndicator);
		}
	}

	GLOBAL::NewRound = true;

	if (!SETTINGS::settings.buybot_enabled)
		return;

	switch (SETTINGS::settings.buybot_rifle)
	{
	case 1:
		INTERFACES::Engine->ClientCmd("buy scar20;buy g3sg1");
		break;
	case 2:
		INTERFACES::Engine->ClientCmd("buy ssg08");
		break;
	case 3:
		INTERFACES::Engine->ClientCmd("buy awp");
		break;
	default:
		break;
	}

	switch (SETTINGS::settings.buybot_pistol)
	{
	case 1:
		INTERFACES::Engine->ClientCmd("buy deagle");
		break;
	case 2:
		INTERFACES::Engine->ClientCmd("buy elite");
		break;
	case 3:
		INTERFACES::Engine->ClientCmd("buy p250");
		break;
	default:
		break;
	}

	switch (SETTINGS::settings.buybot_armor)
	{
	case 1:
		INTERFACES::Engine->ClientCmd("buy vest");
		break;
	case 2:
		INTERFACES::Engine->ClientCmd("buy vesthelm");
		break;
	default:
		break;
	}

	if (SETTINGS::settings.buybot_grenade)
		INTERFACES::Engine->ClientCmd("buy hegrenade; buy molotov; buy incgrenade; buy smokegrenade;");



	if (SETTINGS::settings.buybot_zeus)
		INTERFACES::Engine->ClientCmd("buy taser 34");
}
bool CGameEvents::GoodestWeapon(const char* weapon)
{
	if (weapon == "weapon_taser")
		return false;

	if (weapon == "weapon_molotov")
		return false;

	if (weapon == "weapon_decoy")
		return false;

	if (weapon == "weapon_flashbang")
		return false;

	if (weapon == "weapon_hegrenade")
		return false;

	if (weapon == "weapon_smokegrenade")
		return false;

	if (weapon == "weapon_incgrenade")
		return false;

	if (weapon == "weapon_knife")
		return false;

	if (weapon == "weapon_unknown")
		return false;

	return true;
}