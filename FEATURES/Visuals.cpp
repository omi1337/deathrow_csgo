#include "../includes.h"
#include "../UTILS/interfaces.h"
#include "../SDK/IEngine.h"
#include "../SDK/CUserCmd.h"
#include "../SDK/ConVar.h"
#include "../SDK/CGlobalVars.h"
#include "../SDK/IViewRenderBeams.h"
#include "../FEATURES/Backtracking.h"
#include "../SDK/CBaseEntity.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/CBaseWeapon.h"
#include "../FEATURES/AutoWall.h"
#include "../SDK/CTrace.h"	
#include "../SDK/CGlobalVars.h"
#include "../FEATURES/Aimbot.h"
#include "../FEATURES/Visuals.h"
#include "../UTILS/render.h"
#include "../SDK/IVDebugOverlay.h"
#include <string.h>


/*
………………….._,,-~’’’¯¯¯’’~-,,
………………..,-‘’ ; ; ;_,,---,,_ ; ;’’-,…………………………….._,,,---,,_
……………….,’ ; ; ;,-‘ , , , , , ‘-, ; ;’-,,,,---~~’’’’’’~--,,,_…..,,-~’’ ; ; ; ;__;’-,
……………….| ; ; ;,’ , , , _,,-~’’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ¯’’~’-,,_ ,,-~’’ , , ‘, ;’,
……………….’, ; ; ‘-, ,-~’’ ; ; ; ; ; ; ; ; ; ; ; ; ; omi ; ; ; ; ; ; ; ; ;’’-, , , , , ,’ ; |
…………………’, ; ;,’’ ; ; ; ; ; ; ; ; ; ; ; ; ; 07.02.2019  ; ; ; ; ; ; ; ; ;’-, , ,-‘ ;,-‘
………………….,’-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;  rip  ; ; ; ; ; ; ; ; ; ; ; ;’’-‘ ;,,-‘
………………..,’ ; ; ; ; ; ; ; ; ; ; ; ;__ ; ; ; ; ;  deathrow ; ; ; ; ; ; ; ; ; ; ‘-,’
………………,-‘ ; ; ; ; ; ; ; ; ; ;,-‘’¯: : ’’-, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; _ ; ; ; ; ;’,
……………..,’ ; ; ; ; ; ; ; ; ; ; ;| : : : : : ; ; ; ; ; ; ; ; ; ; ; ; ,-‘’¯: ¯’’-, ; ; ;’,
…………….,’ ; ; ; ; ; ; ; ; ; ; ; ‘-,_: : _,-‘ ; ; ; ; ; ; ; ; ; ; ; ; | : : : : : ; ; ; |
……………,’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ¯¯ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;’-,,_ : :,-‘ ; ; ; ;|
…………..,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,,-~’’ , , , , ,,,-~~-, , , , _ ; ; ;¯¯ ; ; ; ; ;|
..…………,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’ , , , , , , ,( : : : : , , , ,’’-, ; ; ; ; ; ; ; ;|
……….,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;’, , , , , , , , ,’~---~’’ , , , , , ,’ ; ; ; ; ; ; ; ;’,
…….,-‘’ ; _, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ‘’~-,,,,--~~’’’¯’’’~-,,_ , ,_,-‘ ; ; ; ; ; ; ; ; ; ‘,
….,-‘’-~’’,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; | ; ; | . . . . . . ,’; ,’’¯ ; ; ; ; ; ; ; ; ; ,_ ; ‘-,
……….,’ ; ;,-, ; ;, ; ; ;, ; ; ; ; ; ; ; ; ; ; ‘, ; ;’, . . . . .,’ ;,’ ; ; ; ;, ; ; ;,’-, ; ;,’ ‘’~--‘’’
………,’-~’ ,-‘-~’’ ‘, ,-‘ ‘, ,,- ; ; ; ; ; ; ; ; ‘, ; ; ‘~-,,,-‘’ ; ,’ ; ; ; ; ‘, ;,-‘’ ; ‘, ,-‘,
……….,-‘’ ; ; ; ; ; ‘’ ; ; ;’’ ; ; ; ; ; ; ; ; ; ; ‘’-,,_ ; ; ; _,-‘ ; ; ; ; ; ;’-‘’ ; ; ; ‘’ ; ;’-,
……..,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;¯¯’’¯ ; ; ; ; ; ; ; ; , ; ; ; ; ; ; ; ; ;’’-,
……,-‘ ; ; ; ; ; ; ; ,, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; |, ; ; ; ; ; ; ; ; ; ; ‘-,
…..,’ ; ; ; ; ; ; ; ;,’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;|..’-,_ ; ; ; , ; ; ; ; ; ‘,
….,’ ; ; ; ; ; ; ; ; | ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’…….’’’,-~’ ; ; ; ; ; ,’
…,’ ; ; ; ; ; ; ; ; ;’~-,,,,,--~~’’’’’’~-,, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’…..,-~’’ ; ; ; ; ; ; ,-
…| ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ‘, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’…,-‘ ; ; ; ; ; ; ; ;,-‘
…’, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,’….’, ; ; ; ; _,,-‘’
….’, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,-‘’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’…….’’~~’’¯
…..’’-, ; ; ; ; ; ; ; ; ; ; ; ; ; ;_,,-‘’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,-‘
………’’~-,,_ ; ; ; ; _,,,-~’’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,-‘
………..| ; ; ;¯¯’’’’¯ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,,-‘
………..’, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,-‘
…………| ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;|
…………’, ; ; ; ; ; ; ; ; ; ~-,,___ ; ; ; ; ; ; ; ; ; ; ; ; ; ;’,
………….’, ; ; ; ; ; ; ; ; ; ; ;,-‘….’’-, ; ; ; ; ; ; ; ; ; ; ; ; ‘,
………..,’ ‘- ; ; ; ; ; ; ; ; ;,-‘’……….’-, ; ; ; ; ; ; ; ; ; ; ; ‘,
……….,’ ; ;’ ; ; ; ; ; ; ,,-‘…………….’, ; ; ; ; ; ; ; ; ; ; ;’,
………,’ ; ; ; ; ; ; ; ;,-‘’…………………’’-, ; ; ; ; ; ; ; ; ; |
……..,’ ; ; ; ; ; ; ;,,-‘………………………’’, ; ; ; ; ; ; ; ; |
……..| ; ; ; ; ; ; ;,’…………………………,’ ; ; ; ; ; ; ; ;,’
……..| ; ; ; ; ; ; ,’………………………..,-‘ ; ; ; ; ; ; ; ,’’
……..| ; ; ; ; ; ;,’……………………….,-‘ ; ; ; ; ; ; ; ,-‘
……..’,_ , ; , ;,’……………………….,’ ; ; ; ; ; ; ; ,-‘
………’,,’,¯,’,’’|……………………….| ; ; ; ; ; ; ; ; ‘--,,
………….¯…’’………………………..’-, ; ; ; ; ; ; ; ; ; ;’’~,,
……………………………………………’’-,, ; ; ; ; ; ; ; ; ; ;’’~-,,
………………………………………………..’’-, ; ; ; ; ; ,,_ ; ;’-,’’-,
…………………………………………………..’, ; ; ; ; ; ; ‘-,__,--.
……………………………………………………’-, ; ; ;,,-~’’’ , ,|, |
………………………………………………………’’~-‘’_ , , ,,’,_/--‘
thats supposed to be a pedobear

*/


#define XorStr( s ) ( s )


//--- Misc Variable Initalization ---//
float flPlayerAlpha[255];
CColor breaking;
CColor backtrack;
static bool bPerformed = false, bLastSetting;
float fade_alpha[65];
float dormant_time[65];
CColor main_color;
CColor ammo;
SDK::CBaseEntity *BombCarrier;

void CVisuals::set_hitmarker_time(float time)
{
	GLOBAL::flHurtTime = time;
}
#define clamp(val, min, max) (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)))
void CVisuals::Draw()
{
	if (!INTERFACES::Engine->IsInGame()) {
		GLOBAL::flHurtTime = 0.f;
		return;
	}
	DrawCrosshair();
	for (int i = 1; i <= 65; i++)
	{
		auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
		if (!entity) continue;
		if (!local_player) continue;

		bool is_local_player = entity == local_player;
		bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

		if (is_local_player) continue;
		if (entity->GetHealth() <= 0) continue;
		if (entity->GetVecOrigin() == Vector(0, 0, 0)) continue;

		//--- Colors ---//
		if (entity->GetIsDormant() && flPlayerAlpha[i] > 0) flPlayerAlpha[i] -= .3;
		else if (!entity->GetIsDormant() && flPlayerAlpha[i] < 255) flPlayerAlpha[i] = 255;

		float playerAlpha = flPlayerAlpha[i];
		int enemy_hp = entity->GetHealth();
		int hp_red = 255 - (enemy_hp * 2.55);
		int hp_green = enemy_hp * 2.55;
		CColor health_color = CColor(hp_red, hp_green, 1, playerAlpha);
		CColor dormant_color = CColor(100, 100, 100, playerAlpha);
		CColor box_color, still_health, alt_color, zoom_color, name_color, weapon_color, distance_color, arrow_col;

		static auto alpha = 0.f; static auto plus_or_minus = false;
		if (alpha <= 0.f || alpha >= 255.f) plus_or_minus = !plus_or_minus;
		alpha += plus_or_minus ? (255.f / 7 * 0.015) : -(255.f / 7 * 0.015); alpha = clamp(alpha, 0.f, 255.f);
		float arrow_colour[3] = { SETTINGS::settings.fov_col.RGBA[0], SETTINGS::settings.fov_col.RGBA[1], SETTINGS::settings.fov_col.RGBA[2] };
		float arrowteam_colour[3] = { SETTINGS::settings.arrowteam_col.RGBA[0], SETTINGS::settings.arrowteam_col.RGBA[1], SETTINGS::settings.arrowteam_col.RGBA[2] };

		if (entity->GetIsDormant())
		{
			main_color = dormant_color;
			still_health = health_color;
			alt_color = CColor(20, 20, 20, playerAlpha);
			zoom_color = dormant_color;
			breaking = dormant_color;
			backtrack = dormant_color;
			box_color = dormant_color;
			ammo = dormant_color;
			name_color = dormant_color;
			weapon_color = dormant_color;
			distance_color = dormant_color;
			arrow_col = dormant_color;
		}
		else if (!entity->GetIsDormant())
		{
			main_color = CColor(255, 255, 255, playerAlpha);
			still_health = health_color;
			alt_color = CColor(0, 0, 0, 165);
			zoom_color = CColor(150, 150, 220, 165);
			breaking = CColor(220, 150, 150, 165);
			backtrack = CColor(155, 220, 150, 165);
			box_color = SETTINGS::settings.box_col;
			ammo = CColor(61, 135, 255, 165);
			name_color = SETTINGS::settings.name_col;
			weapon_color = SETTINGS::settings.weapon_col;
			distance_color = SETTINGS::settings.distance_col;
			arrow_col = SETTINGS::settings.fov_col;
		}
		Vector min, max, pos, pos3D, top, top3D; entity->GetRenderBounds(min, max);
		pos3D = entity->GetAbsOrigin() - Vector(0, 0, 10); top3D = pos3D + Vector(0, 0, max.z + 10);

		SDK::ClientClass* cClass = (SDK::ClientClass*)entity->GetClientClass();

		if (RENDER::WorldToScreen(pos3D, pos) && RENDER::WorldToScreen(top3D, top))
		{
			if (SETTINGS::settings.zeusrange) DrawZeusRange(entity);

			if (!is_teammate)
			{
				if (SETTINGS::settings.box_bool) DrawBox(entity, box_color, pos, top);
				if (SETTINGS::settings.name_bool) DrawName(entity, name_color, i, pos, top);
				if (SETTINGS::settings.weap_bool) DrawWeapon(entity, weapon_color, i);
				if (SETTINGS::settings.health_bool) DrawHealth(entity, still_health, alt_color, pos, top);
				if (SETTINGS::settings.ammo_bool) ammo_bar(entity, ammo, alt_color, pos, top);
				if (SETTINGS::settings.radar) radar(entity);
				DrawDistance(entity, main_color, pos, top);

			}
			DrawInfo(entity, main_color, zoom_color, pos, top);
		
		}
		if (!is_teammate)
		{
			//if (SETTINGS::settings.fov_bool) fov_arrows(entity, CColor(arrow_colour[0], arrow_colour[1], arrow_colour[2], alpha));
		}
	}
}

void CVisuals::DrawZeusRange(SDK::CBaseEntity* entity) {
	if (!INTERFACES::Engine->IsConnected() || !INTERFACES::Engine->IsInGame())
		return;
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	auto c_baseweapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(entity->GetActiveWeaponIndex()));
	if (!c_baseweapon) return;

	auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex()));
	if (!weapon)
		return;

	//	if (c_baseweapon->GetItemDefenitionIndex() == SDK::ItemDefinitionIndex::WEAPON_TASER)
		//	return;
	if (weapon->GetItemDefenitionIndex() == SDK::ItemDefinitionIndex::WEAPON_TASER)
	{
		if (!in_tp) return;
		float step = M_PI * 2.0 / 1023;
		float rad = SETTINGS::settings.zeus_range;
		//float rad = 178.f; //ûûû
		//Vector origin = Vector(Globals::eyePos.x, Globals::eyePos.y - 25, Globals::eyePos.z);
		Vector origin = local_player->GetEyePosition();

		static double rainbow;

		Vector screenPos;
		static Vector prevScreenPos;

		for (float rotation = 0; rotation < (M_PI * 2.0); rotation += step)
		{
			Vector pos(rad * cos(rotation) + origin.x, rad * sin(rotation) + origin.y, origin.z);

			SDK::Ray_t ray;
			SDK::trace_t trace;
			SDK::CTraceFilter filter;

			filter.pSkip1 = local_player;
			ray.Init(origin, pos);

			INTERFACES::Trace->TraceRay(ray, MASK_SHOT_BRUSHONLY, &filter, &trace);

			if (INTERFACES::DebugOverlay->ScreenPosition(trace.end, screenPos))
				continue;

			if (!prevScreenPos.IsZero() && !screenPos.IsZero() && screenPos.DistTo(Vector(-107374176, -107374176, -107374176)) > 3.f && prevScreenPos.DistTo(Vector(-107374176, -107374176, -107374176)) > 3.f) {
				rainbow += 0.00001;
				if (rainbow > 1.f)
					rainbow = 0;

				CColor color = CColor::FromHSB(rainbow, 1.f, 1.f);


				RENDER::DrawLine(prevScreenPos.x, prevScreenPos.y, screenPos.x, screenPos.y, color);
				RENDER::DrawLine(prevScreenPos.x, prevScreenPos.y + 1, screenPos.x, screenPos.y + 1, color);
				//Draw::Line(Vector2D(prevScreenPos.x, prevScreenPos.y - 1), Vector2D(screenPos.x, screenPos.y - 1), color);
			}
			prevScreenPos = screenPos;
		}
	}
}

void CVisuals::ClientDraw()
{

	if (SETTINGS::settings.scope_bool) DrawBorderLines();

	DrawIndicator();
	DrawSnaplines();
	DrawHitmarker();
}


void CVisuals::viewmodelxyz()
{
	INTERFACES::cvar->get_convar("viewmodel_offset_x")->SetValue(SETTINGS::settings.viewmodel_x);
	INTERFACES::cvar->get_convar("viewmodel_offset_y")->SetValue(SETTINGS::settings.viewmodel_y);
	INTERFACES::cvar->get_convar("viewmodel_offset_z")->SetValue(SETTINGS::settings.viewmodel_z - 10);
}

std::string str_to_upper(std::string strToConvert)
{
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

	return strToConvert;
}


void CVisuals::DrawBox(SDK::CBaseEntity* entity, CColor color, Vector pos, Vector top)
{

	float alpha = flPlayerAlpha[entity->GetIndex()];
	int height = (pos.y - top.y), width = height / 2;

	RENDER::DrawEmptyRect(pos.x - width / 2, top.y, (pos.x - width / 2) + width, top.y + height, color);
	RENDER::DrawEmptyRect((pos.x - width / 2) + 1, top.y + 1, (pos.x - width / 2) + width - 1, top.y + height - 1, CColor(20, 20, 20, alpha));
	RENDER::DrawEmptyRect((pos.x - width / 2) - 1, top.y - 1, (pos.x - width / 2) + width + 1, top.y + height + 1, CColor(20, 20, 20, alpha));
}

void CVisuals::lag_comp_hitbox(SDK::CBaseEntity* entity, int index)
{
	float duration = 2.0f;

	if (index < 0)
		return;

	if (!entity)
		return;

	SDK::studiohdr_t* pStudioModel = INTERFACES::ModelInfo->GetStudioModel(entity->GetModel());

	if (!pStudioModel)
		return;

	SDK::mstudiohitboxset_t* pHitboxSet = pStudioModel->pHitboxSet(0);

	if (!pHitboxSet)
		return;

	for (int i = 0; i < pHitboxSet->numhitboxes; i++)
	{
		SDK::mstudiobbox_t* pHitbox = pHitboxSet->GetHitbox(i);

		if (!pHitbox)
			continue;

		auto bone_matrix = entity->GetBoneMatrix(pHitbox->bone);

		Vector vMin, vMax;

		MATH::VectorTransform(pHitbox->bbmin, bone_matrix, vMin);
		MATH::VectorTransform(pHitbox->bbmax, bone_matrix, vMax);

		if (pHitbox->radius > -1)
		{
			INTERFACES::DebugOverlay->AddCapsuleOverlay(vMin, vMax, pHitbox->radius, 255, 255, 255, 100, duration); // color green 
		}
	}
}

void CVisuals::DrawSnaplines()
{
	if (!SETTINGS::settings.snaplines)
		return;

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player)
		return;

	int width, height;
	INTERFACES::Engine->GetScreenSize(width, height);

}

void CVisuals::ammo_bar(SDK::CBaseEntity* entity, CColor color, CColor dormant, Vector pos, Vector top)
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	auto c_baseweapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(entity->GetActiveWeaponIndex()));
	if (!c_baseweapon) return;

	int height = (pos.y - top.y);

	float offset = (height / 4.f) + 5;
	UINT hp = height - (UINT)((height * 3) / 100);

	auto animLayer = entity->GetAnimOverlay(1);
	if (!animLayer.m_pOwner)
		return;


	int iClip = entity->GetArmor();
	if (!iClip)
		return; 

	float box_w = (float)fabs(height / 2);
	float width;

		width = (((box_w * iClip) / 100));

	RENDER::DrawFilledRect((pos.x - box_w / 2), top.y + height + 3, (pos.x - box_w / 2) + box_w + 2, top.y + height + 7, dormant); //outline
	RENDER::DrawFilledRect((pos.x - box_w / 2) + 1, top.y + height + 4, (pos.x - box_w / 2) + width + 1, top.y + height + 6, color); //ammo
}

void CVisuals::DrawName(SDK::CBaseEntity* entity, CColor color, int index, Vector pos, Vector top)
{
	SDK::player_info_t ent_info; INTERFACES::Engine->GetPlayerInfo(index, &ent_info);

	int height = (pos.y - top.y), width = height / 2;
	RENDER::DrawF(pos.x, top.y - 7, FONTS::visuals_esp_font, true, true, color, ent_info.name);
}

float CVisuals::resolve_distance(Vector src, Vector dest)
{
	Vector delta = src - dest;
	float fl_dist = ::sqrtf((delta.Length()));
	if (fl_dist < 1.0f) return 1.0f;
	return fl_dist;
}

std::string fix_item_name(std::string name)
{
	std::string cname = name;

	if (cname[0] == 'C')
		cname.erase(cname.begin());

	auto startOfWeap = cname.find("Weapon");
	if (startOfWeap != std::string::npos)
		cname.erase(cname.begin() + startOfWeap, cname.begin() + startOfWeap + 6);

	return cname;
}

void CVisuals::DrawDistance(SDK::CBaseEntity* entity, CColor color, Vector pos, Vector top)
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	auto c_baseweapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(entity->GetActiveWeaponIndex()));

	if (!c_baseweapon)
		return;


	SDK::player_info_t ent_info;
	Vector vecOrigin = entity->GetVecOrigin(), vecOriginLocal = local_player->GetVecOrigin();

	char dist_to[32]; int height = (pos.y - top.y), width = height / 12;

	sprintf_s(dist_to, "%.0f ft", resolve_distance(vecOriginLocal, vecOrigin));
	RENDER::DrawF(pos.x, SETTINGS::settings.DrawDistance ? pos.y + 20 : pos.y + 20, FONTS::visuals_esp_font, true, true, color, dist_to);
}


void CVisuals::DrawWeapon(SDK::CBaseEntity* entity, CColor color, int index)
{
	SDK::player_info_t ent_info;
	Vector min, max;
	entity->GetRenderBounds(min, max);
	Vector pos, pos3D, top, top3D;
	pos3D = entity->GetAbsOrigin() - Vector(0, 0, 10);
	top3D = pos3D + Vector(0, 0, max.z + 10);
	INTERFACES::Engine->GetPlayerInfo(index, &ent_info);

	auto weapon = INTERFACES::ClientEntityList->GetClientEntity(entity->GetActiveWeaponIndex());
	auto c_baseweapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(entity->GetActiveWeaponIndex()));

	if (!c_baseweapon)
		return;


	if (!weapon)
		return;

	if (SETTINGS::settings.weap_bool) {

		if (RENDER::WorldToScreen(pos3D, pos) && RENDER::WorldToScreen(top3D, top)) {
			int height = (pos.y - top.y);
			int width = height / 3;

			if (SETTINGS::settings.ammo_bool)
				RENDER::DrawF(pos.x, pos.y + 11, FONTS::visuals_esp_font, true, true, color, fix_item_name(weapon->get_weapon_names()));
			else
				RENDER::DrawF(pos.x, pos.y + 11, FONTS::visuals_esp_font, true, true, color, fix_item_name(weapon->get_weapon_names()));

		}
	}
}

void CVisuals::radar(SDK::CBaseEntity* entity)
{
	DWORD m_bSpotted = OFFSETS::m_bSpotted;
	*(char*)((DWORD)(entity)+m_bSpotted) = 1;
}

void CVisuals::fov_arrows(SDK::CBaseEntity* entity, CColor color)
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;
	if (entity->GetIsDormant()) return;

	Vector screenPos, client_viewangles;
	int screen_width = 0, screen_height = 0;
	float radius = 300.f;

	if (UTILS::IsOnScreen(aimbot->get_hitbox_pos(entity, SDK::HitboxList::HITBOX_HEAD), screenPos)) return;

	INTERFACES::Engine->GetViewAngles(client_viewangles);
	INTERFACES::Engine->GetScreenSize(screen_width, screen_height);

	const auto screen_center = Vector(screen_width / 2.f, screen_height / 2.f, 0);
	const auto rot = DEG2RAD(client_viewangles.y - UTILS::CalcAngle(local_player->GetEyePosition(), aimbot->get_hitbox_pos(entity, SDK::HitboxList::HITBOX_HEAD)).y - 90);

	std::vector<SDK::Vertex_t> vertices;

	vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot) * radius, screen_center.y + sinf(rot) * radius)));
	vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot + DEG2RAD(2)) * (radius - 26), screen_center.y + sinf(rot + DEG2RAD(2)) * (radius - 26))));
	vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot - DEG2RAD(2)) * (radius - 26), screen_center.y + sinf(rot - DEG2RAD(2)) * (radius - 26))));
	vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot - DEG2RAD(2)) * (radius - 46), screen_center.y + sinf(rot - DEG2RAD(2)) * (radius - 46))));
	vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot - DEG2RAD(2)) * (radius - 46), screen_center.y + sinf(rot - DEG2RAD(2)) * (radius - 46))));
	RENDER::TexturedPolygon(3, vertices, CColor(int(SETTINGS::settings.arrows_col[0] * 255.f), int(SETTINGS::settings.arrows_col[1] * 255.f), int(SETTINGS::settings.arrows_col[2] * 255.f)));
}

void CVisuals::static_crosshair()
{
	static SDK::ConVar* weapon_debug_spread_show = INTERFACES::cvar->FindVar("weapon_debug_spread_show");
	weapon_debug_spread_show->nFlags &= ~FCVAR_CHEAT;

	if (SETTINGS::settings.static_crosshair)
		INTERFACES::Engine->ClientCmd_Unrestricted("weapon_debug_spread_show 3");
	else
		INTERFACES::Engine->ClientCmd_Unrestricted("weapon_debug_spread_show 0");
}

void CVisuals::DrawHealth(SDK::CBaseEntity* entity, CColor color, CColor dormant, Vector pos, Vector top)
{
	int enemy_hp = entity->GetHealth(),
		hp_red = 255 - (enemy_hp * 2.55),
		hp_green = enemy_hp * 2.55,
		height = (pos.y - top.y),
		width = height / 2;

	float offset = (height / 4.f) + 5;
	UINT hp = height - (UINT)((height * enemy_hp) / 100);

	RENDER::DrawEmptyRect((pos.x - width / 2) - 6, top.y, (pos.x - width / 2) - 3, top.y + height, dormant);
	RENDER::DrawLine((pos.x - width / 2) - 4, top.y + hp, (pos.x - width / 2) - 4, top.y + height, color);
	RENDER::DrawLine((pos.x - width / 2) - 5, top.y + hp, (pos.x - width / 2) - 5, top.y + height, color);

	if (entity->GetHealth() < 100)
		RENDER::DrawF((pos.x - width / 2) - 4, top.y + hp, FONTS::visuals_esp_font, true, true, main_color, std::to_string(enemy_hp));
}

void CVisuals::DrawInfo(SDK::CBaseEntity* entity, CColor color, CColor alt, Vector pos, Vector top)
{
	std::vector<std::pair<std::string, CColor>> stored_info;

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	bool is_local_player = entity == local_player;
	bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

	if (SETTINGS::settings.info_bool && !is_teammate)
	{
		if (entity->GetArmor() > 0)
			stored_info.push_back(std::pair<std::string, CColor>(entity->GetArmorName(), color));

		if (entity->GetIsScoped())
			stored_info.push_back(std::pair<std::string, CColor>("zoom", color));

		if (!using_fake_angles)
			stored_info.push_back(std::pair<std::string, CColor>("fake", color));

	}

	int height = (pos.y - top.y), width = height / 2, i = 0;
	for (auto Text : stored_info)
	{
		RENDER::DrawF((pos.x + width / 2) + 5, top.y + i, FONTS::visuals_esp_font, false, false, Text.second, Text.first);
		i += 8;
	}
}



void CVisuals::DrawDamageIndicator() {
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;

	if (!local_player->GetHealth() > 0)
		return;

	CColor dmg_color = SETTINGS::settings.dmg_color;

	float CurrentTime = local_player->GetTickBase() * INTERFACES::Globals->interval_per_tick;

	for (int i = 0; i < dmg_indicator.size(); i++) {
		if (dmg_indicator[i].earse_time < CurrentTime) {
			dmg_indicator.erase(dmg_indicator.begin() + i);
			continue;
		}

		if (!dmg_indicator[i].initializes) {
			dmg_indicator[i].Position = dmg_indicator[i].player->GetBonePosition(6);
			dmg_indicator[i].initializes = true;
		}

		if (CurrentTime - dmg_indicator[i].last_update > 0.0001f) {
			dmg_indicator[i].Position.z -= (0.7f * (CurrentTime - dmg_indicator[i].earse_time));
			dmg_indicator[i].last_update = CurrentTime;

			Vector ScreenPosition;

			if (RENDER::WorldToScreen(dmg_indicator[i].Position, ScreenPosition)) {
				RENDER::DrawF(ScreenPosition.x, ScreenPosition.y, FONTS::font_dmg_indicator, true, true, dmg_color, std::to_string(dmg_indicator[i].dmg).c_str());
			}
		}
	}
}

void CVisuals::BombPlanted(SDK::CBaseEntity * entity)
{
	BombCarrier = nullptr;

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;

	Vector vOrig; Vector vScreen;
	vOrig = entity->GetVecOrigin();
	SDK::CCSBomb* Bomb = (SDK::CCSBomb*)entity;

	float flBlow = Bomb->GetC4BlowTime();
	float TimeRemaining = flBlow;
	char buffer[64];//df
	sprintf_s(buffer, "C4 - %.1fs", TimeRemaining);
	RENDER::DrawF(10, 10, FONTS::visuals_lby_font, false, false, CColor(124, 195, 13, 255), buffer);
}

void CVisuals::DrawBulletBeams()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	if (!INTERFACES::Engine->IsInGame() || !local_player) { Impacts.clear(); return; }
	if (Impacts.size() > 30) Impacts.pop_back();

	for (int i = 0; i < Impacts.size(); i++)
	{
		auto current = Impacts.at(i);
		if (!current.pPlayer) continue;
		if (current.pPlayer->GetIsDormant()) continue;

		bool is_local_player = current.pPlayer == local_player;
		bool is_teammate = local_player->GetTeam() == current.pPlayer->GetTeam() && !is_local_player;

		if (current.pPlayer == local_player)
			current.color = CColor(SETTINGS::settings.bulletlocal_col[0] * 255, SETTINGS::settings.bulletlocal_col[1] * 255, SETTINGS::settings.bulletlocal_col[2] * 255, SETTINGS::settings.bulletlocal_col[3] * 255);
		else if (current.pPlayer != local_player && !is_teammate)
			current.color = CColor(SETTINGS::settings.bulletenemy_col[0] * 255, SETTINGS::settings.bulletenemy_col[1] * 255, SETTINGS::settings.bulletenemy_col[2] * 255, SETTINGS::settings.bulletenemy_col[3] * 255);
		else if (current.pPlayer != local_player && is_teammate)
			current.color = CColor(SETTINGS::settings.bulletteam_col[0] * 255, SETTINGS::settings.bulletteam_col[1] * 255, SETTINGS::settings.bulletteam_col[2] * 255, SETTINGS::settings.bulletteam_col[3] * 255);

		SDK::BeamInfo_t beamInfo;
		beamInfo.m_nType = SDK::TE_BEAMPOINTS;
		beamInfo.m_pszModelName = "sprites/purplelaser1.vmt";
		beamInfo.m_nModelIndex = -1;
		beamInfo.m_flHaloScale = 0.0f;
		beamInfo.m_flLife = SETTINGS::settings.bulletlife;
		beamInfo.m_flWidth = SETTINGS::settings.bulletsize;
		beamInfo.m_flEndWidth = 2.0f;
		beamInfo.m_flFadeLength = 0.0f;
		beamInfo.m_flAmplitude = 2.0f;
		beamInfo.m_flBrightness = 255.f;
		beamInfo.m_flSpeed = 0.2f;
		beamInfo.m_nStartFrame = 0;
		beamInfo.m_flFrameRate = 0.f;
		beamInfo.m_flRed = current.color.RGBA[0];
		beamInfo.m_flGreen = current.color.RGBA[1];
		beamInfo.m_flBlue = current.color.RGBA[2];
		beamInfo.m_nSegments = 2;
		beamInfo.m_bRenderable = true;
		beamInfo.m_nFlags = SDK::FBEAM_ONLYNOISEONCE | SDK::FBEAM_NOTILE | SDK::FBEAM_HALOBEAM;

		beamInfo.m_vecStart = current.pPlayer->GetVecOrigin() + current.pPlayer->GetViewOffset();
		beamInfo.m_vecEnd = current.vecImpactPos;

		auto beam = INTERFACES::ViewRenderBeams->CreateBeamPoints(beamInfo);
		if (beam) INTERFACES::ViewRenderBeams->DrawBeam(beam);

		Impacts.erase(Impacts.begin() + i);
	}
}

CColor world_color;
CColor prop_color;
CColor skybox_color;
float prop_alpha = 1.f;

void CVisuals::ModulateWorld()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;
	{
		static SDK::ConVar* r_DrawSpecificStaticProp = INTERFACES::cvar->FindVar("r_DrawSpecificStaticProp");
		r_DrawSpecificStaticProp->nFlags &= ~FCVAR_CHEAT;
		r_DrawSpecificStaticProp->SetValue(0);

		static SDK::ConVar* sv_skyname = INTERFACES::cvar->FindVar("sv_skyname");
		sv_skyname->nFlags &= ~FCVAR_CHEAT;
		if (SETTINGS::settings.asus_props_value != prop_alpha || disconnect)
		{
			for (SDK::MaterialHandle_t i = INTERFACES::MaterialSystem->FirstMaterial(); i != INTERFACES::MaterialSystem->InvalidMaterial(); i = INTERFACES::MaterialSystem->NextMaterial(i))
			{
				SDK::IMaterial* pMaterial = INTERFACES::MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				if (strstr(pMaterial->GetTextureGroupName(), "StaticProp textures"))
				{
					pMaterial->AlphaModulate(prop_alpha);
				}
			}
			prop_alpha = (1 - (SETTINGS::settings.asus_props_value / 100));
		}

		for (SDK::MaterialHandle_t i = INTERFACES::MaterialSystem->FirstMaterial(); i != INTERFACES::MaterialSystem->InvalidMaterial(); i = INTERFACES::MaterialSystem->NextMaterial(i))
		{
			SDK::IMaterial* pMaterial = INTERFACES::MaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			float night_val = (100 - SETTINGS::settings.daytimevalue);
			auto finalnightval = night_val / 100.f;

			if (strstr(pMaterial->GetTextureGroupName(), "World"))
			{
				if (SETTINGS::settings.sky_changer)
				{
					switch (SETTINGS::settings.sky_type)
					{
					case 0: sv_skyname->SetValue("sky_l4d_rural02_ldr"); break;
					case 1: sv_skyname->SetValue("cs_baggage_skybox_"); break;
					case 2: sv_skyname->SetValue("cs_tibet"); break;
					case 3: sv_skyname->SetValue("embassy"); break;
					case 4: sv_skyname->SetValue("italy"); break;
					case 5: sv_skyname->SetValue("jungle"); break;
					case 6: sv_skyname->SetValue("office"); break;
					case 7: sv_skyname->SetValue("sky_cs15_daylight01_hdr"); break;
					case 8: sv_skyname->SetValue("sky_cs15_daylight02_hdr"); break;
					case 9: sv_skyname->SetValue("sky_day02_05"); break;
					case 10: sv_skyname->SetValue("nukeblank"); break;
					case 11: sv_skyname->SetValue("sky_venice"); break;
					case 12: sv_skyname->SetValue("sky_cs15_daylight03_hdr"); break;
					case 13: sv_skyname->SetValue("sky_cs15_daylight04_hdr"); break;
					case 14: sv_skyname->SetValue("sky_csgo_cloudy01"); break;
					case 15: sv_skyname->SetValue("sky_csgo_night02"); break;
					case 16: sv_skyname->SetValue("sky_csgo_night02b"); break;
					case 17: sv_skyname->SetValue("vertigo"); break;
					case 18: sv_skyname->SetValue("vertigoblue_hdr"); break;
					case 19: sv_skyname->SetValue("sky_dust"); break;
					case 20: sv_skyname->SetValue("vietnam"); break;
					case 21: sv_skyname->SetValue("sky2mh_"); break;
					case 22: sv_skyname->SetValue("clear_night_sky"); break;
					}
				}
			}
			else if (strstr(pMaterial->GetTextureGroupName(), "SkyBox"))
			{
				if (SETTINGS::settings.skycolor_bool)
				{
					pMaterial->ColorModulate(SETTINGS::settings.sky_color);
				}
				else
				{
					pMaterial->ColorModulate(1.00, 1.00, 1.00);
				}
			}
			else if (strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
			{
				if (SETTINGS::settings.night_bool)
					pMaterial->ColorModulate(0.28, 0.28, 0.28);
				else
					pMaterial->ColorModulate(1, 1, 1);
			}
		}
	}
}

void CVisuals::DrawCrosshair()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	auto crosshair = INTERFACES::cvar->FindVar("crosshair");
	if (SETTINGS::settings.xhair_type == 0)
	{
		crosshair->SetValue("1");
		return;
	}
	else
		crosshair->SetValue("0");

	int W, H, cW, cH;
	INTERFACES::Engine->GetScreenSize(W, H);

	cW = W / 2; cH = H / 2;

	int dX = W / 120.f, dY = H / 120.f;
	int drX, drY;

	if (SETTINGS::settings.xhair_type == 2)
	{
		drX = cW - (int)(dX * (((local_player->GetPunchAngles().y * 2.f) * 0.45f) + local_player->GetPunchAngles().y));
		drY = cH + (int)(dY * (((local_player->GetPunchAngles().x * 2.f) * 0.45f) + local_player->GetPunchAngles().x));
	}
	else
	{
		drX = cW;
		drY = cH;
	}

	INTERFACES::Surface->DrawSetColor(BLACK);
	INTERFACES::Surface->DrawFilledRect(drX - 4, drY - 2, drX - 4 + 8, drY - 2 + 4);
	INTERFACES::Surface->DrawFilledRect(drX - 2, drY - 4, drX - 2 + 4, drY - 4 + 8);

	INTERFACES::Surface->DrawSetColor(WHITE);
	INTERFACES::Surface->DrawFilledRect(drX - 3, drY - 1, drX - 3 + 6, drY - 1 + 2);
	INTERFACES::Surface->DrawFilledRect(drX - 1, drY - 3, drX - 1 + 2, drY - 3 + 6);
}


void CVisuals::DrawInaccuracy1()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex()));
	if (!weapon) return;

	int spread_Col[3] = { SETTINGS::settings.spreadcirclecol[0], SETTINGS::settings.spreadcirclecol[1], SETTINGS::settings.spreadcirclecol[2] };


	int W, H, cW, cH;
	INTERFACES::Engine->GetScreenSize(W, H);
	cW = W / 2; cH = H / 2;

	if (local_player->IsAlive())
	{
		auto accuracy = (weapon->GetInaccuracy() + weapon->GetSpreadCone()) * 500.f;

		float r;
		float alpha, newAlpha;

		for (r = accuracy; r>0; r--)
		{
			if (!weapon->is_grenade() && !weapon->is_knife())


				alpha = r / accuracy;
			newAlpha = pow(alpha, 5);

			RENDER::DrawCircle(cW, cH, r, 60, CColor(spread_Col[0], spread_Col[1], spread_Col[2], newAlpha * 130));
		}
	}
}

void CVisuals::DrawIndicator()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;
	if (local_player->GetHealth() <= 0) return;

	float breaking_lby_fraction = fabs(MATH::NormalizeYaw(GLOBAL::real_angles.y - local_player->GetLowerBodyYaw())) / 180.f;
	float lby_delta = abs(MATH::NormalizeYaw(GLOBAL::real_angles.y - local_player->GetLowerBodyYaw()));

	int screen_width, screen_height;
	INTERFACES::Engine->GetScreenSize(screen_width, screen_height);

	int center_width = screen_width / 2;
	int center_height = screen_height / 2;

	float dmg;
	if (AutoWall->CanWallbang(dmg)) {
		RENDER::DrawLine(center_width, center_height + 2, center_width, center_height - 2, CColor(0, 255, 0, 255));
		RENDER::DrawLine(center_width + 2, center_height, center_width - 2, center_height, CColor(0, 255, 0, 255));
	}
	else {
		RENDER::DrawLine(center_width, center_height + 2, center_width, center_height - 2, CColor(255, 0, 0, 255));
		RENDER::DrawLine(center_width + 2, center_height, center_width - 2, center_height, CColor(255, 0, 0, 255));


		int iY = 88;

		if (!(local_player->GetFlags() & FL_ONGROUND) && local_player->GetHealth() > 0)
		{
			static Vector pos = local_player->GetVecOrigin();
			iY += 11;
			if (pos.LengthSqr() > 4096.f) {
				int screen_width, screen_height;
				INTERFACES::Engine->GetScreenSize(screen_width, screen_height);
				RENDER::DrawF(10, screen_height / 2, FONTS::visuals_lby_font, false, false, CColor(0, 160, 29), "LC");
				//int(SETTINGS::settings.arrows_col[0] * 255.f), int(SETTINGS::settings.arrows_col[1] * 255.f), int(SETTINGS::settings.arrows_col[2] * 255.f)
			}

			pos = local_player->GetVecOrigin();
		}
	}

	if (SETTINGS::settings.desyncindicator)
{
	float fake_strength = local_player->GetPoseParamaters()[11] * 58;

	if (fake_strength >= 30.f)
		RENDER::DrawF(10, screen_height / 2 + 49, FONTS::visuals_lby_font, false, false, CColor(0, 188, 44), "FAKE");
	else if (fake_strength >= 20.f)
		RENDER::DrawF(10, screen_height / 2 + 49, FONTS::visuals_lby_font, false, false, CColor(201, 204, 0), "FAKE");
	else if (fake_strength >= 10.f)
		RENDER::DrawF(10, screen_height / 2 + 49, FONTS::visuals_lby_font, false, false, CColor(204, 75, 0), "FAKE");
	else
		RENDER::DrawF(10, screen_height / 2 + 49, FONTS::visuals_lby_font, false, false, CColor(204, 0, 0), "FAKE");


}

	if (SETTINGS::settings.rifk_arrow)
	{
		if (!in_tp)
		{
			auto client_viewangles = Vector();
			INTERFACES::Engine->GetViewAngles(client_viewangles);
			const auto screen_center = Vector2D(screen_width / 2.f, screen_height / 2.f);
			//float aa_arrow_width = SETTINGS::settings.aa_arrows_width;
			//float aa_arrow_height = SETTINGS::settings.aa_arrows_height;

			constexpr auto radius = 80.f;
			auto draw_arrow = [&](float rot, CColor color) -> void
			{
				std::vector<SDK::Vertex_t> vertices;
				vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot) * radius, screen_center.y + sinf(rot) * radius)));
				//vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot + DEG2RAD(aa_arrow_width)) * (radius - aa_arrow_height), screen_center.y + sinf(rot + DEG2RAD(aa_arrow_width)) * (radius - aa_arrow_height))));
				//vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot - DEG2RAD(aa_arrow_width)) * (radius - aa_arrow_height), screen_center.y + sinf(rot - DEG2RAD(aa_arrow_width)) * (radius - aa_arrow_height))));
				RENDER::TexturedPolygon(3, vertices, color);
			};

			static auto alpha = 0.f; static auto plus_or_minus = false;
			if (alpha <= 0.f || alpha >= 255.f) plus_or_minus = !plus_or_minus;
			alpha += plus_or_minus ? (255.f / 7 * 0.30) : -(255.f / 7 * 0.30); alpha = clamp(alpha, 0.f, 255.f);

			auto lby_color = CColor(0, 0, 255, alpha);
			const auto lby_rot = DEG2RAD(client_viewangles.y - local_player->GetLowerBodyYaw() - 90);
			draw_arrow(lby_rot, lby_color);

			auto fake_color = CColor(255, 0, 0, alpha);
			const auto fake_rot = DEG2RAD(client_viewangles.y - GLOBAL::fake_angles.y - 90);
			draw_arrow(fake_rot, fake_color);


			auto real_color = CColor(0, 255, 0, alpha);
			const auto real_rot = DEG2RAD(client_viewangles.y - GLOBAL::real_angles.y - 90);
			draw_arrow(real_rot, real_color);
		}
		else
		{
			Vector src3D, dst3D, forward, src, dst;
			SDK::trace_t tr;
			SDK::Ray_t ray;
			SDK::CTraceFilter filter;

			filter.pSkip1 = local_player;

			MATH::AngleVectors(Vector(0, local_player->GetLowerBodyYaw(), 0), &forward);
			src3D = local_player->GetVecOrigin();
			dst3D = src3D + (forward * 42.f); //replace 50 with the length you want the line to have 

			ray.Init(src3D, dst3D);

			INTERFACES::Trace->TraceRay(ray, 0, &filter, &tr);

			if (!RENDER::WorldToScreen(src3D, src) || !RENDER::WorldToScreen(tr.end, dst))
				return;

			RENDER::DrawLine(src.x, src.y, dst.x, dst.y, CColor(0, 0, 255, 255));

			MATH::AngleVectors(Vector(0, GLOBAL::fake_angles.y, 0), &forward);
			dst3D = src3D + (forward * 42.f); //replace 50 with the length you want the line to have 

			ray.Init(src3D, dst3D);

			INTERFACES::Trace->TraceRay(ray, 0, &filter, &tr);

			if (!RENDER::WorldToScreen(src3D, src) || !RENDER::WorldToScreen(tr.end, dst))
				return;

			RENDER::DrawLine(src.x, src.y, dst.x, dst.y, CColor(255, 0, 0, 255));

			MATH::AngleVectors(Vector(0, GLOBAL::real_angles.y, 0), &forward);
			src3D = local_player->GetVecOrigin();
			dst3D = src3D + (forward * 42.f); //replace 50 with the length you want the line to have 

			ray.Init(src3D, dst3D);

			INTERFACES::Trace->TraceRay(ray, 0, &filter, &tr);

			if (!RENDER::WorldToScreen(src3D, src) || !RENDER::WorldToScreen(tr.end, dst))
				return;

			RENDER::DrawLine(src.x, src.y, dst.x, dst.y, CColor(0, 255, 0, 255));
		}
	}
}


void CVisuals::LogEvents()
{
	static bool convar_performed = false, convar_lastsetting;

	if (convar_lastsetting != SETTINGS::settings.info_bool)
	{
		convar_lastsetting = SETTINGS::settings.info_bool;
		convar_performed = false;
	}

	if (!convar_performed)
	{
		//--- Log Events ---//
		static auto developer = INTERFACES::cvar->FindVar("developer");
		developer->SetValue(1);
		static auto con_filter_text_out = INTERFACES::cvar->FindVar("con_filter_text_out");
		static auto con_filter_enable = INTERFACES::cvar->FindVar("con_filter_enable");
		static auto con_filter_text = INTERFACES::cvar->FindVar("con_filter_text");

		con_filter_text->SetValue("    ");
		con_filter_text_out->SetValue("");
		con_filter_enable->SetValue(2);
		convar_performed = true;
	}
}

void CVisuals::DrawHitmarker()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;

	if (local_player->GetHealth() <= 0)
		return;

	static int lineSize = 6;

	static float alpha = 0;
	float step = 255.f / 0.3f * INTERFACES::Globals->frametime;


	if (GLOBAL::flHurtTime + 0.4f >= INTERFACES::Globals->curtime)
		alpha = 255.f;
	else
		alpha -= step;

	if (alpha > 0) {
		int screenSizeX, screenCenterX;
		int screenSizeY, screenCenterY;
		INTERFACES::Engine->GetScreenSize(screenSizeX, screenSizeY);

		screenCenterX = screenSizeX / 2;
		screenCenterY = screenSizeY / 2;
		CColor col = CColor(255, 255, 255, alpha);
		RENDER::DrawLine(screenCenterX - lineSize * 2, screenCenterY - lineSize * 2, screenCenterX - (lineSize), screenCenterY - (lineSize), col);
		RENDER::DrawLine(screenCenterX - lineSize * 2, screenCenterY + lineSize * 2, screenCenterX - (lineSize), screenCenterY + (lineSize), col);
		RENDER::DrawLine(screenCenterX + lineSize * 2, screenCenterY + lineSize * 2, screenCenterX + (lineSize), screenCenterY + (lineSize), col);
		RENDER::DrawLine(screenCenterX + lineSize * 2, screenCenterY - lineSize * 2, screenCenterX + (lineSize), screenCenterY - (lineSize), col);
	}
}

//raimbow
void CVisuals::DrawBorderLines()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player) return;

	auto weapon = INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex());
	if (!weapon) return;

	int screen_x;
	int screen_y;
	int center_x;
	int center_y;
	INTERFACES::Engine->GetScreenSize(screen_x, screen_y);
	INTERFACES::Engine->GetScreenSize(center_x, center_y);
	center_x /= 2; center_y /= 2;

	if (local_player->GetIsScoped())
	{
		RENDER::DrawLine(0, center_y, screen_x, center_y, CColor(0, 0, 0, 255));
		RENDER::DrawLine(center_x, 0, center_x, screen_y, CColor(0, 0, 0, 255));
	}
}

void CVisuals::clan_tag()
{
	auto apply = [](const char * name) -> void {
		using Fn = int(__fastcall *)(const char *, const char *);
		static auto fn = reinterpret_cast<Fn>(UTILS::FindSignature("engine.dll", "53 56 57 8B DA 8B F9 FF 15"));
		fn(name, name);
	};

	static float last_time;

	if (int(INTERFACES::Globals->curtime) != last_time)
	{
		std::string name = ("deathrow ");
		apply((char*)name.substr(0, int(INTERFACES::Globals->curtime) % name.length()).c_str());
		last_time = int(INTERFACES::Globals->curtime);
	}
}

void CVisuals::clan_tagrec()
{
	auto apply = [](const char* name) -> void {
		using Fn = int(__fastcall*)(const char*, const char*);
		static auto fn = reinterpret_cast<Fn>(UTILS::FindSignature("engine.dll", "53 56 57 8B DA 8B F9 FF 15"));
		fn(name, name);
	};

	static float last_time;

	if (int(INTERFACES::Globals->curtime) != last_time)
	{
		std::string name = ("deathrow recode");
		apply((char*)name.substr(0, int(INTERFACES::Globals->curtime) % name.length()).c_str());
		last_time = int(INTERFACES::Globals->curtime);
	}
}

std::vector<std::string> spam =
{

};

void CVisuals::chat_spam()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;

	static float nextTime = 0.f;
	float flServerTime = local_player->GetTickBase() * INTERFACES::Globals->interval_per_tick;

	if (nextTime > flServerTime)
		return;

	nextTime = flServerTime + 3.0f;
	if (SETTINGS::settings.misc_chat_spam)
		INTERFACES::Engine->ClientCmd(std::string(std::string("say ") + spam[rand() % 1]).c_str());
}

SDK::ConVar* r_DrawSpecificStaticProp;

void CVisuals::night_mode()
{
	static bool OldNightmode;

	if (OldNightmode != SETTINGS::settings.night_bool)
	{
		if (!r_DrawSpecificStaticProp)
			r_DrawSpecificStaticProp = INTERFACES::cvar->FindVar("r_DrawSpecificStaticProp");

		r_DrawSpecificStaticProp->SetValue(0);

		for (SDK::MaterialHandle_t i = INTERFACES::MaterialSystem->FirstMaterial(); i != INTERFACES::MaterialSystem->InvalidMaterial(); i = INTERFACES::MaterialSystem->NextMaterial(i))
		{
			SDK::IMaterial* pMaterial = INTERFACES::MaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "World") || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
			{
				if (SETTINGS::settings.night_bool)
				{
					if (strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
						pMaterial->ColorModulate(0.3f, 0.3f, 0.3f);
					else
						pMaterial->ColorModulate(0.05f, 0.05f, 0.05f);
				}
				else
					pMaterial->ColorModulate(1.0f, 1.0f, 1.0f);
			}
		}

		OldNightmode = SETTINGS::settings.night_bool;
	}
}



CVisuals* visuals = new CVisuals();