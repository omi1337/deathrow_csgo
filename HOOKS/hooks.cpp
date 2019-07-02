#include "..\includes.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../ImGui/dx9/imgui_impl_dx9.h"
#include "hooks.h"
#include "../UTILS/interfaces.h"
#include "../UTILS/offsets.h"
#include "../UTILS/NetvarHookManager.h"
#include "../FEATURES/bt.h"
#include "../UTILS/render.h"
#include "../SDK/CInput.h"
#include "../SDK/IClient.h"
#include "../HOOKS/back_drop.h"
#include "../SDK/CPanel.h"
#include "../SDK/ConVar.h"
#include "../SDK/CGlowObjectManager.h"
#include "../SDK/IEngine.h"
#include "../SDK/CTrace.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/RecvData.h"
#include "../SDK/CBaseAnimState.h"
#include "../SDK/ModelInfo.h"
#include "../SDK/ModelRender.h"
#include "../SDK/RenderView.h"
#include "../SDK/CTrace.h"
#include "../FEATURES/config.h"
#include "../SDK/CViewSetup.h"
#include "../SDK/CGlobalVars.h"
#include "../SDK/CPrediction.h"
#include "../AWHitmarkers.h"
#include "../FEATURES/Movement.h"
#include "../FEATURES/Visuals.h"

#include "../FEATURES/AntiAim.h"
#include "../FEATURES/Aimbot.h"
#include "../FEATURES/override.h"
#include "../FEATURES/Backtracking.h"
#include "../FEATURES/FakeLag.h"
#include "../FEATURES/EnginePred.h"
#include "../FEATURES/EventListener.h"
#include "../FEATURES/GrenadePrediction.h"
#include "../FEATURES/Legitbot.h"
#include "../FEATURES/Flashlight.h"
#include "../FEATURES/GloveChanger.h"
#include "../FEATURES/SkinChanger.h"
#include "../xor.h"
#include "../shit.h"
#include <chrono>
#include <d3dx9.h>
#include <ShlObj_core.h>
#include <intrin.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


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


void animation_fix(SDK::CBaseEntity* entity)
{
	if (!entity)
		return;

	auto old_curtime = INTERFACES::Globals->curtime;
	auto old_frametime = INTERFACES::Globals->frametime;
	auto old_fraction = entity->GetAnimState()->m_flUnknownFraction = 0.f;

	INTERFACES::Globals->curtime = entity->GetSimTime();
	INTERFACES::Globals->frametime = INTERFACES::Globals->interval_per_tick;

	SDK::CAnimationLayer backup_layers[16];
	std::memcpy(backup_layers, entity->GetAnimOverlays(), (sizeof(SDK::CAnimationLayer) * 15));

	if (entity->GetAnimState())
		entity->GetAnimState()->m_iLastClientSideAnimationUpdateFramecount - INTERFACES::Globals->framecount - 1;

	entity->GetClientSideAnimation() = true;
	entity->UpdateClientSideAnimation();
	entity->GetClientSideAnimation() = false;

	std::memcpy(backup_layers, entity->GetAnimOverlays(), (sizeof(SDK::CAnimationLayer) * 15));

	INTERFACES::Globals->curtime = old_curtime;
	INTERFACES::Globals->frametime = old_frametime;

	entity->GetAnimState()->m_flUnknownFraction = old_fraction;

	entity->SetAngle2(Vector(0.f, entity->GetAnimState()->m_flGoalFeetYaw, 0.f));
}




static int tab1 = 1;
static int tab2 = 1;



std::vector<std::pair<int, const char*>> weapon_skins =
{
{ 0,   "default" },
{ 692, "night riot" },
{ 693 , "flame test" },
{ 697 , "black sand" },
{ 700 , "urban hazard (p2000)" },
{ 701 , "grip" },
{ 702 , "aloha" },
{ 645 , "oxide blaze" },
{ 694 , "moonrise" },
{ 698 , "lionfish" },
{ 699 , "wild six" },
{ 703 , "swag - 7" },
{ 704 , "arctic wolf" },
{ 690 , "stymphalian" },
{ 691 , "mortis" },
{ 705 , "cortex" },
{ 695 , "neo - noir" },
{ 696, "bloodsport (mp7)" },
{ 361, "abyss" },
{ 253, "acid fade" },
{ 598, "aerial" },
{ 154, "afterimage" },
{ 609, "airlock" },
{ 455, "akihabara accept" },
{ 523, "amber fade (revolver)" },
{ 246, "amber fade" },
{ 210, "anodized gunmetal" },
{ 197, "anodized navy" },
{ 28,  "anodized navy" },
{ 286, "antique (nova)" },
{ 306, "antique (pp bizon)" },
{ 460, "aqua terrace" },
{ 474, "aquamarine revenge" },
{ 6,   "arctic camo" },
{ 583, "aristocrat" },
{ 423, "armor core" },
{ 242, "army mesh" },
{ 245, "army recon" },
{ 298, "army sheen" },
{ 234, "ash wood" },
{ 279, "asiimov (awp)" },
{ 255, "asiimov (m4a4)" },
{ 551, "asiimov (p250)" },
{ 359, "asiimov (p90)" },
{ 442, "asterion" },
{ 553, "atlas" },
{ 301, "atomic alloy" },
{ 573, "autotronic (bayonet)" },
{ 574, "autotronic (flip)" },
{ 575, "autotronic (gut)" },
{ 576, "autotronic (karambit)" },
{ 577, "autotronic (m9 bayonet)" },
{ 520, "avalanche" },
{ 229, "azure zebra" },
{ 174, "boom" },
{ 459, "bamboo forest" },
{ 457, "bamboo print" },
{ 458, "bamboo shadow" },
{ 383, "basilisk" },
{ 9,   "bengal tiger" },
{ 503, "big iron" },
{ 549, "bioleak" },
{ 172, "black laminate (ak-47)" },
{ 563, "black laminate (bayonet)" },
{ 564, "black laminate (flip)" },
{ 565, "black laminate (gut)" },
{ 566, "black laminate (karambit)" },
{ 567, "black laminate (m9 bayonet)" },
{ 190, "black limba" },
{ 629, "black sand" },
{ 557, "black tie" },
{ 166, "blaze orange" },
{ 37,  "blaze" },
{ 228, "blind spot" },
{ 75,  "blizzard marbleized" },
{ 217, "blood tiger" },
{ 222, "blood in the water" },
{ 597, "bloodsport" },
{ 62,  "bloomstick" },
{ 278, "blue fissure" },
{ 226, "blue laminate" },
{ 96,  "blue spruce" },
{ 42,  "blue steel" },
{ 13,  "blue streak" },
{ 216, "blue titanium" },
{ 370, "bone machine" },
{ 27,  "bone mask" },
{ 193, "bone pile" },
{ 77,  "boreal forest" },
{ 159, "brass" },
{ 317, "bratatat" },
{ 330, "briar" },
{ 615, "briefing" },
{ 578, "bright water (knife)" },
{ 579, "bright water (knife)" },
{ 189, "bright water (m4a1-s)" },
{ 425, "bronze deco" },
{ 39,  "bulldozer" },
{ 155, "bullet rain" },
{ 479, "bunsen burner" },
{ 364, "business class" },
{ 632, "buzz kill" },
{ 299, "caged steel" },
{ 339, "caiman" },
{ 240, "calicamo" },
{ 3,   "candy apple" },
{ 93,  "caramel" },
{ 70,  "carbon fiber" },
{ 391, "cardiac" },
{ 589, "carnivore" },
{ 388, "cartel" },
{ 394, "cartel" },
{ 528, "cartel" },
{ 44,  "case hardened" },
{ 399, "catacombs" },
{ 379, "cerberus" },
{ 327, "chainmail" },
{ 325, "chalice" },
{ 280, "chameleon" },
{ 548, "chantico's fire" },
{ 398, "chatterbox" },
{ 376, "chemical green" },
{ 593, "chopper" },
{ 438, "chronos" },
{ 627, "cirrus" },
{ 346, "coach class" },
{ 499, "cobalt core" },
{ 231, "cobalt disruption" },
{ 267, "cobalt halftone" },
{ 249, "cobalt quartz" },
{ 67,  "cold blooded" },
{ 47,  "colony" },
{ 343, "commuter" },
{ 110, "condemned" },
{ 351, "conspiracy" },
{ 373, "contamination" },
{ 46,  "contractor" },
{ 22,  "contrast spray" },
{ 274, "copper galaxy" },
{ 41,  "copper" },
{ 10,  "copperhead" },
{ 509, "corinthian" },
{ 281, "corporal" },
{ 181, "corticera (awp)" },
{ 184, "corticera (p2000)" },
{ 462, "counter terrace" },
{ 466, "crimson kimono" },
{ 12,  "crimson web (deagle)" },
{ 232, "crimson web" },
{ 310, "curse" },
{ 92,  "cyanospatter" },
{ 360, "cyrex (m4a1-s)" },
{ 312, "cyrex (scar-20)" },
{ 487, "cyrex (sg 553)" },
{ 637, "cyrex (usp)" },
{ 444, "daedalus" },
{ 411, "damascus steel (knife)" },
{ 410, "damascus steel (knife)" },
{ 247, "damascus steel (sg 553)" },
{ 329, "dark age" },
{ 60,  "dark water" },
{ 386, "dart" },
{ 471, "daybreak" },
{ 610, "dazzle" },
{ 403, "deadly poison" },
{ 293, "death rattle" },
{ 156, "death by kitty" },
{ 392, "delusion" },
{ 195, "demeter" },
{ 153, "demolition" },
{ 8,   "desert storm" },
{ 311, "desert warfare" },
{ 336, "desert-strike" },
{ 355, "desert-strike" },
{ 588, "desolate space" },
{ 319, "detour" },
{ 603, "directive" },
{ 429, "djinn" },
{ 178, "doomkitty" },
{ 417, "doppler (black pearl)" },
{ 418, "doppler (phase 1)" },
{ 419, "doppler (phase 2)" },
{ 420, "doppler (phase 3)" },
{ 421, "doppler (phase 4)" },
{ 415, "doppler (ruby)" },
{ 416, "doppler (sapphire)" },
{ 400, "?? dragon king" },
{ 344, "dragon lore" },
{ 48,  "dragon tattoo" },
{ 624, "dragonfire" },
{ 199, "dry season" },
{ 491, "dualing dragons" },
{ 447, "duelist" },
{ 428, "eco" },
{ 227, "electric hive" },
{ 422, "elite build (ak-47)" },
{ 525, "elite build (awp)" },
{ 486, "elite build (p90)" },
{ 182, "emerald dragon" },
{ 300, "emerald pinstripe" },
{ 196, "emerald" },
{ 453, "emerald" },
{ 480, "evil daimyo" },
{ 590, "exo" },
{ 207, "facets" },
{ 522, "fade (revolver)" },
{ 38,  "fade" },
{ 176, "faded zebra" },
{ 169, "fallout warning" },
{ 378, "fallout warning" },
{ 389, "fire elemental" },
{ 180, "fire serpent" },
{ 546, "firefight" },
{ 385, "firestarter" },
{ 341, "first class" },
{ 345, "first class" },
{ 631, "flashback" },
{ 541, "fleet flock" },
{ 493, "flux" },
{ 5,   "forest ddpat" },
{ 25,  "forest leaves" },
{ 78,  "forest night" },
{ 352, "fowl play" },
{ 295, "franklin" },
{ 580, "freehand" },
{ 581, "freehand" },
{ 582, "freehand" },
{ 490, "frontside misty" },
{ 552, "fubar" },
{ 524, "fuel injector (ak-47)" },
{ 614, "fuel injector (tec-9)" },
{ 508, "fuel rod" },
{ 250, "full stop" },
{ 568, "gamma doppler (emerald marble)" },
{ 569, "gamma doppler (phase 1)" },
{ 570, "gamma doppler (phase 2)" },
{ 571, "gamma doppler (phase 3)" },
{ 572, "gamma doppler (phase 4)" },
{ 243, "gator mesh" },
{ 225, "ghost camo" },
{ 554, "ghost crusader" },
{ 634, "gila" },
{ 111, "glacier mesh" },
{ 497, "golden coil" },
{ 185, "golden koi" },
{ 436, "grand prix" },
{ 21,  "granite marbleized" },
{ 212, "graphite" },
{ 214, "graphite" },
{ 104, "grassland leaves" },
{ 95,  "grassland" },
{ 188, "graven" },
{ 294, "green apple" },
{ 502, "green marine" },
{ 366, "green plaid" },
{ 384, "griffin" },
{ 611, "grim" },
{ 381, "grinder" },
{ 406, "grotto" },
{ 2,   "groundwater" },
{ 209, "groundwater" },
{ 257, "guardian" },
{ 290, "guardian" },
{ 15,  "gunsmoke" },
{ 439, "hades" },
{ 328, "hand cannon" },
{ 485, "handgun" },
{ 594, "harvester" },
{ 198, "hazard" },
{ 284, "heat" },
{ 431, "heat" },
{ 291, "heaven guard" },
{ 314, "heaven guard" },
{ 273, "heirloom" },
{ 220, "hemoglobin" },
{ 218, "hexane" },
{ 390, "highwayman" },
{ 219, "hive" },
{ 33,  "hot rod" },
{ 445, "hot rod" },
{ 377, "hot shot" },
{ 309, "howl" },
{ 241, "hunting blind" },
{ 456, "hydroponic" },
{ 475, "hyper beast (awp)" },
{ 430, "hyper beast (m4a1-s)" },
{ 537, "hyper beast (nova)" },
{ 61,  "hypnotic" },
{ 440, "icarus fell" },
{ 599, "ice cap" },
{ 472, "impact drill" },
{ 591, "imperial dragon" },
{ 515, "imperial" },
{ 536, "impire" },
{ 602, "imprint" },
{ 333, "indigo" },
{ 592, "iron clad" },
{ 623, "ironwork" },
{ 171, "irradiated alert" },
{ 303, "isaac" },
{ 357, "ivory" },
{ 316, "jaguar" },
{ 539, "jambiya" },
{ 340, "jet set" },
{ 542, "judgement of anubis" },
{ 202, "jungle ddpat" },
{ 147, "jungle dashed" },
{ 122, "jungle spray" },
{ 16,  "jungle tiger" },
{ 151, "jungle" },
{ 205, "jungle" },
{ 265, "kami (five-seven)" },
{ 308, "kami (galil-ar)" },
{ 504, "kill confirmed" },
{ 326, "knight" },
{ 356, "koi" },
{ 527, "kumicho dragon" },
{ 362, "labyrinth" },
{ 534, "lapis gator" },
{ 540, "lead conduit" },
{ 342, "leather" },
{ 26,  "lichen dashed" },
{ 51,  "lightning strike" },
{ 596, "limelight" },
{ 558, "lore (bayonet)" },
{ 559, "lore (flip)" },
{ 560, "lore (gut)" },
{ 561, "lore (karambit)" },
{ 562, "lore (m9 bayonet)" },
{ 483, "loudmouth" },
{ 266, "magma" },
{ 402, "malachite" },
{ 395, "man-o'-war (awp)" },
{ 432, "man-o'-war (negev)" },
{ 413, "marble fade" },
{ 261, "marina" },
{ 321, "master piece" },
{ 200, "mayan dreams" },
{ 587, "mecha industries (m4a1-s)" },
{ 626, "mecha industries (famas)" },
{ 446, "medusa" },
{ 258, "mehndi" },
{ 177, "memento" },
{ 34,  "metallic ddpat" },
{ 296, "meteorite" },
{ 468, "midnight storm" },
{ 441, "minotaur's labyrinth" },
{ 467, "mint kimono" },
{ 164, "modern hunter" },
{ 335, "module" },
{ 427, "monkey business" },
{ 450, "moon in libra" },
{ 204, "mosaico" },
{ 90,  "mudder" },
{ 404, "muertos" },
{ 382, "murky" },
{ 397, "naga" },
{ 496, "nebula crusader" },
{ 538, "necropos" },
{ 481, "nemesis" },
{ 464, "neon kimono" },
{ 600, "neon revolution" },
{ 433, "neon rider" },
{ 477, "neural net" },
{ 236, "night ops" },
{ 40,  "night" },
{ 223, "nightshade" },
{ 254, "nitro" },
{ 322, "nitro" },
{ 372, "nuclear garden" },
{ 168, "nuclear threat" },
{ 179, "nuclear threat" },
{ 369, "nuclear waste" },
{ 211, "ocean foam" },
{ 213, "ocean foam" },
{ 550, "oceanic" },
{ 365, "olive plaid" },
{ 545, "orange crash" },
{ 83,  "orange ddpat" },
{ 465, "orange kimono" },
{ 141, "orange peel" },
{ 434, "origami" },
{ 313, "orion" },
{ 349, "osiris" },
{ 36,  "ossified" },
{ 518, "outbreak" },
{ 183, "overgrowth" },
{ 157, "palm" },
{ 201, "palm" },
{ 448, "pandora's box" },
{ 276, "panther" },
{ 454, "para green" },
{ 443, "pathfinder" },
{ 608, "petroglyph" },
{ 584, "phobos" },
{ 526, "photic zone" },
{ 347, "pilot" },
{ 84,  "pink ddpat" },
{ 251, "pit viper" },
{ 506, "point disarray" },
{ 315, "poison dart" },
{ 74,  "polar camo" },
{ 107, "polar mesh" },
{ 435, "pole position" },
{ 622, "polymer" },
{ 449, "poseidon" },
{ 514, "power loader" },
{ 612, "powercore" },
{ 535, "praetorian" },
{ 170, "predator" },
{ 556, "primal saber" },
{ 260, "pulse" },
{ 287, "pulse" },
{ 338, "pulse" },
{ 407, "quicksilver" },
{ 167, "radiation hazard" },
{ 375, "radiation hazard" },
{ 498, "rangeen" },
{ 484, "ranger" },
{ 555, "re-entry" },
{ 367, "reactor" },
{ 595, "reboot" },
{ 543, "red astor" },
{ 275, "red fragcam" },
{ 14,  "red laminate" },
{ 348, "red leather" },
{ 320, "red python" },
{ 248, "red quartz" },
{ 259, "redline" },
{ 282, "redline" },
{ 307, "retribution" },
{ 510, "retrobution" },
{ 507, "ricochet" },
{ 488, "riot" },
{ 263, "rising skull" },
{ 318, "road rash" },
{ 478, "rocket pop" },
{ 604, "roll cage" },
{ 262, "rose iron" },
{ 332, "royal blue" },
{ 625, "royal consorts" },
{ 532, "royal legion" },
{ 512, "royal paladin" },
{ 482, "ruby poison dart" },
{ 203, "rust coat" },
{ 323, "rust coat" },
{ 414, "rust coat" },
{ 72,  "safari mesh" },
{ 119, "sage spray" },
{ 148, "sand dashed" },
{ 208, "sand dune" },
{ 99,  "sand dune" },
{ 116, "sand mesh" },
{ 630, "sand scale" },
{ 124, "sand spray" },
{ 264, "sandstorm" },
{ 289, "sandstorm" },
{ 175, "scorched" },
{ 71,  "scorpion" },
{ 605, "scumbria (five-seven)" },
{ 505, "scumbria (xm1014)" },
{ 473, "seabird" },
{ 405, "serenity" },
{ 288, "sergeant" },
{ 221, "serum" },
{ 368, "setting sun" },
{ 636, "shallow grave" },
{ 516, "shapewood" },
{ 192, "shattered" },
{ 452, "shipping forecast" },
{ 252, "silver quartz" },
{ 32,  "silver" },
{ 11,  "skulls" },
{ 304, "slashed" },
{ 59,  "slaughter" },
{ 616, "slipstream" },
{ 30,  "snake camo" },
{ 633, "sonar" },
{ 500, "special delivery" },
{ 547, "spectre" },
{ 194, "spitfire" },
{ 165, "splash jam" },
{ 162, "splash" },
{ 43, "stained" },
{ 277, "stainless" },
{ 230, "steel disruption" },
{ 628, "stinger" },
{ 494, "stone cold" },
{ 100, "storm" },
{ 371, "styx" },
{ 451, "sun in leo" },
{ 469, "sunset storm ?" },
{ 470, "sunset storm ?" },
{ 358, "supernova" },
{ 492, "survivor z" },
{ 601, "syd mead" },
{ 401, "system lock" },
{ 337, "tatter" },
{ 244, "teardown" },
{ 521, "teclu burner" },
{ 191, "tempest" },
{ 463, "terrace" },
{ 285, "terrain" },
{ 533, "the battlestar" },
{ 511, "the executioner" },
{ 269, "the fuschia is now" },
{ 256, "the kraken" },
{ 519, "tiger moth" },
{ 409, "tiger tooth" },
{ 350, "tigris" },
{ 272, "titanium bit" },
{ 101, "tornado" },
{ 206, "tornado" },
{ 305, "torque" },
{ 489, "torque" },
{ 374, "toxic" },
{ 393, "tranquility" },
{ 363, "traveler" },
{ 268, "tread plate" },
{ 613, "triarch" },
{ 283, "trigon" },
{ 530, "triumvirate" },
{ 233, "tropical storm" },
{ 635, "turf" },
{ 297, "tuxedo" },
{ 437, "twilight galaxy" },
{ 334, "twist" },
{ 98,  "ultraviolet" },
{ 271, "undertow" },
{ 17,  "urban ddpat" },
{ 149, "urban dashed" },
{ 354, "urban hazard" },
{ 387, "urban hazard" },
{ 143, "urban masked" },
{ 135, "urban perforated" },
{ 237, "urban rubble" },
{ 396, "urban shock" },
{ 426, "valence" },
{ 529, "valence" },
{ 238, "varicamo blue" },
{ 235, "varicamo" },
{ 606, "ventilator" },
{ 544, "ventilators" },
{ 270, "victoria" },
{ 585, "violent daimyo" },
{ 20,  "virus" },
{ 302, "vulcan" },
{ 158, "walnut" },
{ 638, "wasteland princess" },
{ 380, "wasteland rebel (ak-47)" },
{ 586, "wasteland rebel (glock)" },
{ 353, "water elemental" },
{ 224, "water sigil" },
{ 186, "wave spray" },
{ 136, "waves perforated" },
{ 607, "weasel" },
{ 102, "whiteout" },
{ 73,  "wings" },
{ 501, "wingshot" },
{ 76,  "winter forest" },
{ 424, "worm god" },
{ 495, "wraiths" },
{ 215, "x-ray" },
{ 476, "yellow jacket" },
{ 517, "yorick" },
{ 187, "zirka" },
};

const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "desert eagle";
	case 2:
		return "dual barettas";
	case 3:
		return "five-seven";
	case 4:
		return "glock-17";
	case 7:
		return "ak-47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galil-ar";
	case 14:
		return "m249";
	case 60:
		return "m4a1-s";
	case 16:
		return "m4a4";
	case 17:
		return "mac-10";
	case 19:
		return "p90";
	case 24:
		return "ump-45";
	case 25:
		return "xm1014";
	case 26:
		return "pp-bizon";
	case 27:
		return "mag-7";
	case 28:
		return "negev";
	case 29:
		return "sawed-off";
	case 30:
		return "tec-9";
	case 32:
		return "p2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar-20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp-s";
	case 63:
		return "cz75-a";
	case 64:
		return "r8 revolver";
	case 508:
		return "m9 bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "flip knife";
	case 506:
		return "gut knife";
	case 507:
		return "karambit";
	case 509:
		return "hunstman knife";
	case 512:
		return "falchion";
	case 514:
		return "bowie knife";
	case 515:
		return "butterfly";
	case 516:
		return "shadow daggers";
	case 523:
		return "talon knife";
	case 520:
		return "navaja knife";
	case 522:
		return "stiletto knife";
	case 519:
		return "ursus knife";

	default:
		return "";
	}
}

std::vector<std::pair<int, const char*>> guns =
{
	{ SDK::ItemDefinitionIndex::WEAPON_AK47,			"ak-47" },
{ SDK::ItemDefinitionIndex::WEAPON_AUG,		  	    "aug" },
{ SDK::ItemDefinitionIndex::WEAPON_AWP,		     	"awp" },
{ SDK::ItemDefinitionIndex::WEAPON_CZ75A,		     	"cz75-a" },
{ SDK::ItemDefinitionIndex::WEAPON_DEAGLE,	    	"desert eagle" },
{ SDK::ItemDefinitionIndex::WEAPON_ELITE,			    "dual berettas" },
{ SDK::ItemDefinitionIndex::WEAPON_FAMAS,			    "famas" },
{ SDK::ItemDefinitionIndex::WEAPON_FIVESEVEN,     	"five-Seven" },
{ SDK::ItemDefinitionIndex::WEAPON_GALILAR,	    	"galil-ar" },
{ SDK::ItemDefinitionIndex::WEAPON_G3SG1,		    	"g3sg1" },
{ SDK::ItemDefinitionIndex::WEAPON_GLOCK,		    	"glock-18" },
{ SDK::ItemDefinitionIndex::WEAPON_M249,	    		"m249" },
{ SDK::ItemDefinitionIndex::WEAPON_M4A1_SILENCER,     "m4a1-s" },
{SDK::ItemDefinitionIndex::WEAPON_M4A1,	     		"m4a4" },
{ SDK::ItemDefinitionIndex::WEAPON_MAC10,		    	"mac-10" },
{ SDK::ItemDefinitionIndex::WEAPON_MAG7,		    	"mag-7" },
{ SDK::ItemDefinitionIndex::WEAPON_MP7,               "mp7" },
{ SDK::ItemDefinitionIndex::WEAPON_MP9,		    	"mp9" },
{ SDK::ItemDefinitionIndex::WEAPON_NEGEV,		    	"negev" },
{ SDK::ItemDefinitionIndex::WEAPON_NOVA,		    	"nova" },
{ SDK::ItemDefinitionIndex::WEAPON_HKP2000,	    	"p2000" },
{ SDK::ItemDefinitionIndex::WEAPON_P250,		    	"p250" },
{ SDK::ItemDefinitionIndex::WEAPON_P90,		    	"p90" },
{ SDK::ItemDefinitionIndex::WEAPON_BIZON,		    	"pp-bizon" },
{ SDK::ItemDefinitionIndex::WEAPON_REVOLVER,	    	"r8 revolver" },
{ SDK::ItemDefinitionIndex::WEAPON_SAWEDOFF,	    	"sawed-off" },
{ SDK::ItemDefinitionIndex::WEAPON_SCAR20,	    	"scar-20" },
{ SDK::ItemDefinitionIndex::WEAPON_SG556,		     	"sg-556" },
{ SDK::ItemDefinitionIndex::WEAPON_SSG08,		    	"scout" },
{ SDK::ItemDefinitionIndex::WEAPON_TEC9,		    	"tec-9" },
{ SDK::ItemDefinitionIndex::WEAPON_UMP45,		    	"ump-45" },
{ SDK::ItemDefinitionIndex::WEAPON_USP_SILENCER,   	"usp-s" },
{ SDK::ItemDefinitionIndex::WEAPON_XM1014,            "xm1014" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_BAYONET,  	"bayonet" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_FLIP,	    "flip knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_GUT,	    	"gut knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT,    "karambit" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET,	"m9 bayonet" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL,	"hunstman lnife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_FALCHION,	"falchion knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_BOWIE, "bowie knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY,	"butterfly knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_PUSH,        "shadow daggers" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_TALON,       "talon knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_NAVAJA,      "navaja knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_STILETTO,    "stiletto knife" },
{ SDK::ItemDefinitionIndex::WEAPON_KNIFE_URSUS,       "ursus knife" },
};

static int ground_tick;

IDirect3DStateBlock9* pixel_state = NULL; IDirect3DVertexDeclaration9* vertDec; IDirect3DVertexShader9* vertShader;
DWORD dwOld_D3DRS_COLORWRITEENABLE;

void SaveState(IDirect3DDevice9 * pDevice)
{
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->GetVertexDeclaration(&vertDec);
	pDevice->GetVertexShader(&vertShader);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);
}

void RestoreState(IDirect3DDevice9 * pDevice) // not restoring everything. Because its not needed.
{
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
	pDevice->SetVertexDeclaration(vertDec);
	pDevice->SetVertexShader(vertShader);
}

namespace INIT
{
	HMODULE Dll;
	HWND Window;
	WNDPROC OldWindow;
}
static bool menu_open = false;
static bool d3d_init = false;
bool PressedKeys[256] = {};
const char* merixids[] =
{
	"1","2","3","4","5","6", "7", "8", "9",
	"Q","W","E","R","T","Y","U","I","O","P",
	"A","S","D","F","G","H","J","K","L",
	"Z","X","C","V","B","N","M",".","\\","|", "/","}","{","[","]",
	"<",">","?","'"
};
static char ConfigNamexd[64] = { 0 };
namespace ImGui
{

	static auto vector_getterxd = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	IMGUI_API bool ComboBoxArrayxd(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getterxd,
			static_cast<void*>(&values), values.size());
	}
}
inline float FastSqrt1(float x)
{
	unsigned int i = *(unsigned int*)& x;
	i += 127 << 23;
	i >>= 1;
	return *(float*)& i;
}
#define square1( x ) ( x * x )
void SlowWalk2(SDK::CUserCmd* get_cmd, float get_speed)
{
	if (get_speed <= 0.f)
		return;

	float min_speed = (float)(FastSqrt1(square1(get_cmd->forwardmove) + square1(get_cmd->sidemove) + square1(get_cmd->upmove)));
	if (min_speed <= 0.f)
		return;

	if (get_cmd->buttons & IN_DUCK)
		get_speed *= 2.94117647f;

	if (min_speed <= get_speed)
		return;

	float speed = get_speed / min_speed;

	get_cmd->forwardmove *= speed;
	get_cmd->sidemove *= speed;
	get_cmd->upmove *= speed;
}
ImFont* bigmenu_font;
ImFont* menu_font;
ImFont* smallmenu_font;
//--- Other Globally Used Variables ---///
static bool tick = false;
Vector vecAimPunch, vecViewPunch;
Vector* pAimPunch = nullptr;
Vector* pViewPunch = nullptr;

//--- Declare Signatures and Patterns Here ---///
static auto CAM_THINK = UTILS::FindSignature("client_panorama.dll", "85 C0 75 30 38 86");
static auto linegoesthrusmoke = UTILS::FindSignature("client_panorama.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");

//--- Tick Counting ---//
void ground_ticks()
{
	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

	if (!local_player)
		return;

	if (local_player->GetFlags() & FL_ONGROUND)
		ground_tick++;
	else
		ground_tick = 0;
}
void slowwalkspeed(int speed)
{
	auto sidespeed = INTERFACES::cvar->FindVar("cl_sidespeed");
	auto forwardspeed = INTERFACES::cvar->FindVar("cl_forwardspeed");
	auto backspeed = INTERFACES::cvar->FindVar("cl_backspeed");
	if (sidespeed->GetInt() == 450 && speed == 450) return;
	sidespeed->SetValue(speed);
	forwardspeed->SetValue(speed);
	backspeed->SetValue(speed);
}

void SlowWalk(SDK::CUserCmd* userCMD)
{
	if (GetAsyncKeyState(SETTINGS::settings.Slowwalkkey))
	{
		GLOBAL::NormalSpeed = false;
		int finalspeed = 250 * SETTINGS::settings.Slowwalkspeed / 100;
		slowwalkspeed(finalspeed);
	}
	if (!GetAsyncKeyState(SETTINGS::settings.Slowwalkkey))
		GLOBAL::NormalSpeed = true;
	else
		GLOBAL::NormalSpeed = false;

	if (GLOBAL::NormalSpeed) slowwalkspeed(450);
}

void auto_revolver(SDK::CUserCmd* cmd)
{

	auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
	if (!local_player || local_player->GetHealth() <= 0)
		return;

	auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex()));
	if (!weapon || weapon->GetItemDefenitionIndex() != SDK::WEAPON_REVOLVER)
		return;

	static float delay = 0.f;
	if (delay < 0.15f)
	{
		delay += INTERFACES::Globals->interval_per_tick;
		cmd->buttons |= IN_ATTACK;
	}
	else
		delay = 0.f;

}

namespace HOOKS
{
	CreateMoveFn original_create_move;
	PaintTraverseFn original_paint_traverse;
	PaintFn original_paint;
	FrameStageNotifyFn original_frame_stage_notify;
	DrawModelExecuteFn original_draw_model_execute;
	SceneEndFn original_scene_end;
	TraceRayFn original_trace_ray;
	OverrideViewFn original_override_view;
	RenderViewFn original_render_view;
	SvCheatsGetBoolFn original_get_bool;
	GetViewmodelFOVFn original_viewmodel_fov;

	vfunc_hook fireevent;
	vfunc_hook directz;

	VMT::VMTHookManager iclient_hook_manager;
	VMT::VMTHookManager panel_hook_manager;
	VMT::VMTHookManager paint_hook_manager;
	VMT::VMTHookManager model_render_hook_manager;
	VMT::VMTHookManager scene_end_hook_manager;
	VMT::VMTHookManager render_view_hook_manager;
	VMT::VMTHookManager trace_hook_manager;
	VMT::VMTHookManager net_channel_hook_manager;
	VMT::VMTHookManager override_view_hook_manager;
	VMT::VMTHookManager input_table_manager;
	VMT::VMTHookManager get_bool_manager;
	std::string sPanel = ("FocusOverlayPanel");

	template<class T, class U>
	T fine(T in, U low, U high)
	{
		if (in <= low)
			return low;

		if (in >= high)
			return high;

		return in;
	}
	
	bool __stdcall HookedCreateMove(float sample_input_frametime, SDK::CUserCmd* cmd)
	{ 
		if (!cmd || cmd->command_number == 0)
			return false;

		uintptr_t* FPointer; __asm { MOV FPointer, EBP }
		byte* SendPacket = (byte*)(*FPointer - 0x1C);
		if (!SendPacket) return false;

		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
		if (!local_player) return false;
		GLOBAL::cmd = cmd;
		GLOBAL::should_send_packet = *SendPacket;
		GLOBAL::originalCMD = *cmd;
		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
			static SDK::ConVar* impacts = INTERFACES::cvar->FindVar("sv_showimpacts");
			GrenadePrediction::instance().Tick(cmd->buttons);

			auto_revolver(cmd);
			aimbot->autozeus(cmd);

			if (SETTINGS::settings.Slowwalkenable && GetAsyncKeyState(VK_SHIFT))
				SlowWalk2(cmd, SETTINGS::settings.Slowwalkspeed);

			if (SETTINGS::settings.remove_duck_cooldown)
				cmd->buttons |= IN_BULLRUSH;
			


			if (SETTINGS::settings.bullet_impact)
				impacts->SetValue(1);
			else
				impacts->SetValue(0);

			if (SETTINGS::settings.bhop_bool) movement->bunnyhop(cmd);
			if (SETTINGS::settings.duck_bool) movement->duckinair(cmd);
			if (SETTINGS::settings.autozeus) aimbot->autozeus(cmd);
			if (SETTINGS::settings.fakeduck) antiaim->fake_duck(cmd);
			if (SETTINGS::settings.Beta_AA) antiaim->BetaAA(cmd);
			if (SETTINGS::settings.misc_clantag) visuals->clan_tag();
			if (SETTINGS::settings.misc_clantagrecode) visuals->clan_tagrec();
			if (SETTINGS::settings.misc_chat_spam) visuals->chat_spam();

			prediction->run_prediction(cmd);
			{

				if (SETTINGS::settings.aim_bool)
				{
					aimbot->autozeus(cmd);
					if (SETTINGS::settings.fake_bool)
					{
						if (local_player->IsAlive())
						{
							for (int i = 1; i < INTERFACES::Globals->maxclients; i++)
							{
								auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
								if (!entity || entity == local_player || entity->GetClientClass()->m_ClassID != !entity->IsAlive()) continue;



								float simtime_delta = entity->GetSimTime() - *reinterpret_cast<float*>(uintptr_t(entity) + OFFSETS::m_flSimulationTime) + 0x4;

								int choked_ticks = HOOKS::fine(TIME_TO_TICKS(simtime_delta), 1, 15);
								Vector lastOrig;

								if (lastOrig.Length() != entity->GetVecOrigin().Length())
									lastOrig = entity->GetVecOrigin();

								float delta_distance = (entity->GetVecOrigin() - lastOrig).LengthSqr();
								if (delta_distance > 4096.f)
								{
									Vector velocity_per_tick = entity->GetVelocity() * INTERFACES::Globals->interval_per_tick;
									auto new_origin = entity->GetVecOrigin() + (velocity_per_tick * choked_ticks);
									entity->SetAbsOrigin(new_origin);
								}
							}
						}
					}
					aimbot->run_aimbot(cmd);
					backtracking->backtrack_player(cmd);
				}

				int accuracyboost = SETTINGS::settings.Accuracyboost;

				switch (accuracyboost)
				{
				case 0:
					break;
				case 1: {
					backtracking->backtrack_player(cmd);
					backtracking->run_legit(cmd);
				};
						break;
						/*	case 2: backtracking->run_legit(cmd);
								break;*/
				}

				if (SETTINGS::settings.extrapolation)
					aimbot->extrapolation();
				
				if (SETTINGS::settings.auto_knife) {
					//misc::knife_Run(cmd);
				}

				if (SETTINGS::settings.removesky)
				{
					auto skybox = INTERFACES::cvar->FindVar("sv_skyname");
					if (skybox) skybox->SetValue("sky_l4d_rural02_ldr");
				}
				else {
					static SDK::ConVar* sv_skyname = INTERFACES::cvar->FindVar("sv_skyname");
					sv_skyname->nFlags &= ~FCVAR_CHEAT;
					sv_skyname->SetValue("vertigoblue_hdr");
				}

				if (SETTINGS::settings.strafe_bool) movement->autostrafer(cmd);

				if (SETTINGS::settings.aim_type == 0 && SETTINGS::settings.aim_bool)
				{
					aimbot->run_aimbot(cmd);
				}	

				if (SETTINGS::settings.aa_bool)
				{
					antiaim->do_antiaim(cmd);
					antiaim->fix_movement(cmd);
				}
			}
			prediction->end_prediction(cmd);

		
				GLOBAL::real_angles = cmd->viewangles;
			

		}
		cmd = GLOBAL::cmd;
		*SendPacket = GLOBAL::should_send_packet;
		if (SETTINGS::settings.anti_untrusted)
			UTILS::ClampLemon(cmd->viewangles);
		return false;
	}


	void __stdcall HookedPaintTraverse(int VGUIPanel, bool ForceRepaint, bool AllowForce)
	{
		static DWORD* deathNotice;
		static void(__thiscall * ClearDeathNotices)(DWORD);
		std::string panel_name = INTERFACES::Panel->GetName(VGUIPanel);

		/*if (SETTINGS::settings.KillfeedBool)
		{
			static DWORD* deathNotice = FindHudElement<DWORD>("CCSGO_HudDeathNotice");
			static void(__thiscall * ClearDeathNotices)(DWORD) = (void(__thiscall*)(DWORD))UTILS::FindSignature("client_panorama.dll", "55 8B EC 83 EC 0C 53 56 8B 71 58");

			auto m_local = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
			//killfead 
			//ok 
			if (m_local) {
				if (!deathNotice) deathNotice = FindHudElement<DWORD>("CCSGO_HudDeathNotice");
				if (deathNotice) {
					float* localDeathNotice = (float*)((DWORD)deathNotice + 0x50);
					if (localDeathNotice)* localDeathNotice = SETTINGS::settings.PreserveKillfeed ? FLT_MAX : 1.5f;
					if (GLOBAL::NewRound) {
						deathNotice = FindHudElement<DWORD>("CCSGO_HudDeathNotice");
						if (deathNotice - 20)
						{
							ClearDeathNotices(((DWORD)deathNotice - 20));
						}
						GLOBAL::NewRound = false;
					}
				}
			}
		}*/


		if (panel_name == "HudZoom" && SETTINGS::settings.scope_bool) return;
		if (panel_name == "FocusOverlayPanel")
		{
			if (FONTS::ShouldReloadFonts())
				FONTS::InitFonts();

			int w, h;
			INTERFACES::Engine->GetScreenSize(w, h);
			RENDER::DrawFilledRect(w - 162, 4, 187 + w - 187, 20, CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)));
			RENDER::DrawF(w - 167 + 7, 5, FONTS::font_watermark, false, false, CColor(255, 255, 255, 255), "   deathrow beta");
			RENDER::DrawF(w - 187 + 92, 5, FONTS::font_watermark, false, false, CColor(255, 255, 255, 255), UTILS::currentDateTime());

			if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
			{
				int W, H, cW, cH;
				INTERFACES::Engine->GetScreenSize(W, H);
				cW = W / 2;
				cH = H / 2;

				int iY = 88;

				int screen_width, screen_height;
				INTERFACES::Engine->GetScreenSize(screen_width, screen_height);

				static bool left = false;
				static bool right = false;
				static bool back = false;
				static bool free = false;

				if (SETTINGS::settings.aa_real_type == 4)
				{

					if (GetAsyncKeyState(SETTINGS::settings.aa_left))
					{
						left = true;
						right = false;
						back = false;
						free = false;
					}
					else
					{
					}
					if (GetAsyncKeyState(SETTINGS::settings.aa_right))
					{
						left = false;
						right = true;
						back = false;
						free = false;
					}
					else
					{
					}
					if (GetAsyncKeyState(SETTINGS::settings.aa_back))
					{
						left = false;
						right = false;
						back = true;
						free = false;
					}
					else
					{
					}
					if (GetAsyncKeyState(SETTINGS::settings.aa_auto))
					{
						left = false;
						right = false;
						back = false;
						free = true;
					}
					else
					{
					}
					{
						if (left)
						{
						/*	RENDER::old_text(cW + 30, cH - 0, L"▸", FONTS::font_indicators, CColor(255, 255, 255, 200));
							RENDER::old_text(cW - 38, cH + 0, L"◂", FONTS::font_indicators, CColor(82, 0, 145));
							RENDER::old_text(cW - 3.5, cH + 30, L"▾", FONTS::font_indicators, CColor(255, 255, 255, 200));*/
							RENDER::DrawF(10, screen_height / 2 + 25, FONTS::visuals_lby_font, false, false, CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "LEFT");
						}
						else if (right)
						{
						/*	RENDER::old_text(cW + 30, cH - 0, L"▸", FONTS::font_indicators, CColor(82, 0, 145));
							RENDER::old_text(cW - 38, cH + 0, L"◂", FONTS::font_indicators, CColor(255, 255, 255, 200));
							RENDER::old_text(cW - 3.5, cH + 30, L"▾", FONTS::font_indicators, CColor(255, 255, 255, 200));*/
							RENDER::DrawF(10, screen_height / 2 + 25, FONTS::visuals_lby_font, false, false, CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "RIGHT");
						}
						else if (back)
						{
						/*	RENDER::old_text(cW + 30, cH - 0, L"▸", FONTS::font_indicators, CColor(255, 255, 255, 200));
							RENDER::old_text(cW - 38, cH + 0, L"◂", FONTS::font_indicators, CColor(255, 255, 255, 200));
							RENDER::old_text(cW - 3.5, cH + 30, L"▾", FONTS::font_indicators, CColor(82, 0, 145));*/
							RENDER::DrawF(10, screen_height / 2 + 25, FONTS::visuals_lby_font, false, false, CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "BACK");
						}
					}
				}

				GrenadePrediction::instance().Paint();
				pHitmarker->Paint();
				visuals->static_crosshair();

				if (SETTINGS::settings.aa_real_type == 5)
				{
					RENDER::DrawF(10, screen_height / 2 + 25, FONTS::visuals_lby_font, false, false, CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "SMART");

				}

				if (GetAsyncKeyState(SETTINGS::settings.Slowwalkkey))
				{
					RENDER::DrawF(10, screen_height / 2 + 72, FONTS::visuals_lby_font, false, false, CColor(int(SETTINGS::settings.invisible_col[0] * 255.f), int(SETTINGS::settings.invisible_col[1] * 255.f), int(SETTINGS::settings.invisible_col[2] * 255.f)), "SLOW WALK");
				}


				//daca nu merge circle-u ala, inseamna ca trebuie aici pus.

				if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
				{
					visuals->DrawDamageIndicator();
				}

				SDK::ConVar* mat_fullbright = INTERFACES::cvar->FindVar("mat_fullbright");

				if (SETTINGS::settings.full_bright)
					mat_fullbright->SetValue(true);
				else
					mat_fullbright->SetValue(false);

				if (SETTINGS::settings.esp_bool)
				{
					visuals->Draw();
					visuals->ClientDraw();
				}

				static SDK::ConVar* rag = INTERFACES::cvar->FindVar("phys_pushscale");
				rag->nFlags &= ~FCVAR_CHEAT;

				if (SETTINGS::settings.ragdol)
				{
					rag->SetValue(-900);
				}
				else
					rag->SetValue(100);


			}
			visuals->LogEvents();
			BackDrop::DrawBackDrop();
		}

		original_paint_traverse(INTERFACES::Panel, VGUIPanel, ForceRepaint, AllowForce);

		const char* pszPanelName = INTERFACES::Panel->GetName(VGUIPanel);

		if (!strstr(pszPanelName, sPanel.data()))
			return;


		INTERFACES::Panel->SetMouseInputEnabled(VGUIPanel, SETTINGS::settings.menu_open);
	}


	
	void __fastcall HookedFrameStageNotify(void* ecx, void* edx, int stage)
	{
		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
		if (!local_player) return;
		Vector vecAimPunch, vecViewPunch;
		Vector* pAimPunch = nullptr; Vector* pViewPunch = nullptr;
		GLOBAL::recoilframe = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer())->GetPunchAngles();

		visuals->night_mode();

		switch (stage)
		{
			case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
				if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
				{
					GloveChanger();
					xdSkinchanger();
					for (int i = 1; i <= 65; i++)
					{
						auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
						if (!entity) continue;

						bool is_local_player = entity == local_player;
						bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

						if (is_local_player) continue;
						if (is_teammate) continue;
						if (entity->GetHealth() <= 0) continue;
						if (entity->GetIsDormant()) continue;

						if (SETTINGS::settings.override)
							c_override->override_player(entity);

						if (SETTINGS::settings.resolve_bool)
						{
							int angle1[64];
							int angle2[64];
							int angle3[64];
							static float old_simtime[65];
							if (GLOBAL::should_send_packet)
								angle1[i] = entity->GetEyeAngles().y;
							else
								angle2[i] = entity->GetEyeAngles().y;

							if (angle1[i] != angle2[i])
								using_fake_angles[entity->GetIndex()] = true;
							else
								using_fake_angles[entity->GetIndex()] = false;

							if (using_fake_angles[entity->GetIndex()])
							{
								if (MATH::YawDistance(angle1[i], angle2[i]) < 59)
								{
									resolve_type[i] = 0;
									entity->GetEyeAnglesPtr()->y = entity->GetLowerBodyYaw() - MATH::YawDistance(angle1[i], angle2[i]);
								}
							}
						}
					
					}
				} break;
			case FRAME_NET_UPDATE_POSTDATAUPDATE_END:
				break;
			case FRAME_RENDER_START:

				if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
				{
					for (int i = 1; i <= 65; i++)
					{
						auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
						if (!entity) continue;

						bool is_local_player = entity == local_player;
						bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

						if (is_local_player) continue;
						if (is_teammate) continue;
						if (entity->GetHealth() <= 0) continue;
						if (entity->GetIsDormant()) continue;

						g_BacktrackHelper->UpdateBacktrackRecords(entity);

						if (SETTINGS::settings.force_ragdoll)
						{
							bool applied = false;
							if (!applied) {
								auto gamers = INTERFACES::cvar->FindVar("cl_ragdoll_gravity");
								gamers->SetValue(-1000);
								applied = true;
							}
						}
					}
					
					if (in_tp)
					{
						*reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(local_player) + 0x31D8) = GLOBAL::real_angles;
					}
					animation_fix(local_player);
					for (int i = 1; i <= 65; i++)
					{
						auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);
						if (!entity) continue;
						if (entity == local_player) continue;

						*(int*)((uintptr_t)entity + 0xA30) = INTERFACES::Globals->framecount;
						*(int*)((uintptr_t)entity + 0xA28) = 0;
					}
				} break;

			case FRAME_NET_UPDATE_START:
				if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
				{
					if (SETTINGS::settings.beam_bool)
						visuals->DrawBulletBeams();

				} break;
			case FRAME_NET_UPDATE_END:
				if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
				{
					for (int i = 1; i < 65; i++)
					{
						auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);

						if (!entity)
							continue;

						if (!local_player)
							continue;

						bool is_local_player = entity == local_player;
						bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

						if (is_local_player)
							continue;

						if (is_teammate)
							continue;

						if (entity->GetHealth() <= 0)
							continue;

							backtracking->DisableInterpolation(entity);
					}
				}
				break;
		}
		original_frame_stage_notify(ecx, stage);
	}

	void __fastcall HookedDrawModelExecute(void* ecx, void* edx, SDK::IMatRenderContext* context, const SDK::DrawModelState_t& state, const SDK::ModelRenderInfo_t& render_info, matrix3x4_t* matrix)
	{
		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
			//auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

			//if (!local_player)
				//return;

			auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
			std::string ModelName = INTERFACES::ModelInfo->GetModelName(render_info.pModel);

			if (SETTINGS::settings.wire_hand) { // strstr
				if (ModelName.find("arms") != std::string::npos) {
					SDK::IMaterial* mat = INTERFACES::MaterialSystem->CreateMaterialBasic2(true, false, true);
					mat->ColorModulate(SETTINGS::settings.wire_color_h[0], SETTINGS::settings.wire_color_h[1], SETTINGS::settings.wire_color_h[2]);
					mat->AlphaModulate(SETTINGS::settings.wire_color_h[3]);
					INTERFACES::ModelRender->ForcedMaterialOverride(mat);
				}
			}
			if (SETTINGS::settings.misc_no_sleeves)
			{
				if (ModelName.find("v_sleeve") != std::string::npos)
				{
					SDK::IMaterial* material = INTERFACES::MaterialSystem->FindMaterial(ModelName.c_str(), TEXTURE_GROUP_MODEL);
					if (!material) return;
					material->SetMaterialVarFlag(SDK::MATERIAL_VAR_NO_DRAW, true);
					INTERFACES::ModelRender->ForcedMaterialOverride(material);
				}
			}

			if (render_info.entity_index == INTERFACES::Engine->GetLocalPlayer() && local_player && in_tp && SETTINGS::settings.esp_bool && local_player->GetIsScoped())
				INTERFACES::RenderView->SetBlend(0.4f);

			if (SETTINGS::settings.no_flash)
			{
				SDK::IMaterial* flash = INTERFACES::MaterialSystem->FindMaterial("effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);
				SDK::IMaterial* flashWhite = INTERFACES::MaterialSystem->FindMaterial("effects\\flashbang_white", TEXTURE_GROUP_CLIENT_EFFECTS);

				flash->SetMaterialVarFlag(SDK::MATERIAL_VAR_NO_DRAW, true);
				flashWhite->SetMaterialVarFlag(SDK::MATERIAL_VAR_NO_DRAW, true);
			}
			
		}
		original_draw_model_execute(ecx, context, state, render_info, matrix);
	}
	void __fastcall HookedSceneEnd(void* ecx, void* edx)
	{
		original_scene_end(ecx);

		SDK::IMaterial *material = nullptr;

		material = INTERFACES::MaterialSystem->FindMaterial("debug/debugdrawflat", TEXTURE_GROUP_MODEL);
		static SDK::IMaterial* mat5 = INTERFACES::MaterialSystem->FindMaterial("models/inventory_items/dogtags/dogtags_outline", "Model textures");

		if (!material)
			return;

		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame()) {
			CColor color = CColor(SETTINGS::settings.glow_col[0] * 255, SETTINGS::settings.glow_col[1] * 255, SETTINGS::settings.glow_col[2] * 255, SETTINGS::settings.glow_col[3] * 255), colorTeam = CColor(SETTINGS::settings.teamglow_color[0] * 255, SETTINGS::settings.teamglow_color[1] * 255, SETTINGS::settings.teamglow_color[2] * 255, SETTINGS::settings.teamglow_color[3] * 255), colorlocal = CColor(SETTINGS::settings.glowlocal_col[0] * 255, SETTINGS::settings.glowlocal_col[1] * 255, SETTINGS::settings.glowlocal_col[2] * 255, SETTINGS::settings.glowlocal_col[3] * 255);
			
			auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

			if (!local_player)
				return;

			for (int i = 1; i < 65; i++) {
				auto entity = INTERFACES::ClientEntityList->GetClientEntity(i);


				if (!entity)
					continue;



				bool is_local_player = entity == local_player;
				bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;
				auto ignorezmaterial = SETTINGS::settings.chamstype == 0 ? material : material;
				auto notignorezmaterial = SETTINGS::settings.chamstype == 0 ? material : material;

				if (is_teammate)
					continue;

				if (local_player && SETTINGS::settings.chams_type == 1) {
					INTERFACES::ModelRender->ForcedMaterialOverride(material);
					material->ColorModulate(CColor(255, 255, 255, 255)); //0, 125, 255
					INTERFACES::RenderView->set_color_modulation((CColor(SETTINGS::settings.vmodel_col[0] * 255, SETTINGS::settings.vmodel_col[1] * 255, SETTINGS::settings.vmodel_col[2] * 255, SETTINGS::settings.vmodel_col[3] * 255)));
					entity->DrawModel(0x1, 255);
					INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);
				}

				if (local_player) {
					/*	vec3_t OrigAng;
						OrigAng = local_player->get_eye_ang( );
						local_player->set_angles( vec3_t( 0, fakeangles.y, 0 ) );
						angles->AlphaModulate( 0 );
						ctx::model_render->ForcedMaterialOverride( angles );
						local_player->DrawModel( 0x1, 255 );
						ctx::model_render->ForcedMaterialOverride( nullptr );*/
				}

				if (is_local_player)
					continue;

				if (entity && SETTINGS::settings.chams_type == 1)
				{
					INTERFACES::ModelRender->ForcedMaterialOverride(material);
					material->ColorModulate(CColor(255, 255, 255, 255)); //0, 125, 255
					INTERFACES::RenderView->set_color_modulation((CColor(SETTINGS::settings.vmodel_col[0] * 255, SETTINGS::settings.vmodel_col[1] * 255, SETTINGS::settings.vmodel_col[2] * 255, SETTINGS::settings.vmodel_col[3] * 255)));
					entity->DrawModel(0x1, 255);

					INTERFACES::ModelRender->ForcedMaterialOverride(material);
					material->ColorModulate(CColor(255, 255, 255, 255)); //0, 125, 255
					INTERFACES::RenderView->set_color_modulation((CColor(SETTINGS::settings.vmodel_col[0] * 255, SETTINGS::settings.vmodel_col[1] * 255, SETTINGS::settings.vmodel_col[2] * 255, SETTINGS::settings.vmodel_col[3] * 255)));
					entity->DrawModel(0x1, 255);
					INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);
				}
				else if (entity && SETTINGS::settings.chams_type == 2)
				{
					INTERFACES::ModelRender->ForcedMaterialOverride(material);
					material->ColorModulate(CColor(255, 255, 255, 255)); //0, 125, 255
					INTERFACES::RenderView->set_color_modulation((CColor(SETTINGS::settings.vmodel_col[0] * 255, SETTINGS::settings.vmodel_col[1] * 255, SETTINGS::settings.vmodel_col[2] * 255, SETTINGS::settings.vmodel_col[3] * 255)));
					entity->DrawModel(0x1, 255);
					//despacito
					INTERFACES::ModelRender->ForcedMaterialOverride(material);
					material->ColorModulate(CColor(255, 255, 255, 255)); //0, 125, 255
					INTERFACES::RenderView->set_color_modulation((CColor(SETTINGS::settings.invisible_col[0] * 255, SETTINGS::settings.invisible_col[1] * 255, SETTINGS::settings.invisible_col[2] * 255, SETTINGS::settings.invisible_col[3] * 255)));
					entity->DrawModel(0x1, 255);
					INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);
				}
			}


			if (in_tp)
			{
				if (SETTINGS::settings.fakechams)
				{
					/*local_player->SetAbsOrigin(GLOBAL::real_angles);
					local_player->SetAngle2(Vector(0, GLOBAL::FakePosition.y, 0));
					mat->ColorModulate(CColor(SETTINGS::settings.localchams_col[0] * 255, SETTINGS::settings.localchams_col[1] * 255, SETTINGS::settings.localchams_col[2] * 255));
					INTERFACES::ModelRender->ForcedMaterialOverride(mat);
					local_player->DrawModel(0x1, 255);
					INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);
					local_player->SetAbsOrigin(local_player->GetAbsOrigin());*/

					Vector abs_angles = local_player->GetAbsAngles();

					local_player->SetAbsAngles(Vector(0, GLOBAL::fake_angles.y, 0));



					mat5->ColorModulate(CColor(SETTINGS::settings.localchams_col[0] * 255, SETTINGS::settings.localchams_col[1] * 255, SETTINGS::settings.localchams_col[2] * 255));

					INTERFACES::RenderView->SetBlend(0.3f);

					INTERFACES::ModelRender->ForcedMaterialOverride(mat5);

					local_player->DrawModel(0x1, 255);

					INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);

					INTERFACES::RenderView->SetBlend(1.f);

					local_player->SetAbsAngles(Vector(0, abs_angles.y, 0));

				}
			}

			if (local_player->GetVelocity().Length2D() > 30 && local_player && SETTINGS::settings.localchams_fakelag && INTERFACES::Input->m_fCameraInThirdPerson)
			{
				//if (SETTINGS::settings.chamstypeselfcolor == 0)
				mat5->ColorModulate(CColor(SETTINGS::settings.fakechams_col_back[0] * 255, SETTINGS::settings.fakechams_col_back[1] * 255, SETTINGS::settings.fakechams_col_back[2] * 255));
				mat5->AlphaModulate(SETTINGS::settings.fakechams_col_back[3] * 255);
				mat5->IncrementReferenceCount();
				//else if (SETTINGS::settings.chamstypeselfcolor == 1)
					//mat5->ColorModulate(CColor::FromHSB(rainbow, 1.f, 1.f));
				INTERFACES::ModelRender->ForcedMaterialOverride(mat5);
				//mat5->Set_Flag(SDK::MATERIAL_VAR_IGNOREZ, true);
				local_player->SetAbsOrigin(GLOBAL::FakePosition);
				local_player->DrawModel(0x1, 255);
				local_player->SetAbsOrigin(local_player->GetAbsOrigin());
				INTERFACES::ModelRender->ForcedMaterialOverride(nullptr);
			}

			for (auto i = 0; i < INTERFACES::GlowObjManager->GetSize(); i++)
			{
				auto &glowObject = INTERFACES::GlowObjManager->m_GlowObjectDefinitions[i];
				auto entity = reinterpret_cast<SDK::CBaseEntity*>(glowObject.m_pEntity);

				if (!entity) continue;
	

				if (glowObject.IsUnused()) continue;

				bool is_local_player = entity == local_player;
				bool is_teammate = local_player->GetTeam() == entity->GetTeam() && !is_local_player;

				if (is_local_player && in_tp && SETTINGS::settings.glowlocal)
				{
					glowObject.m_nGlowStyle = 0;//0;
					glowObject.m_flRed = colorlocal.RGBA[0] / 255.0f;
					glowObject.m_flGreen = colorlocal.RGBA[1] / 255.0f;
					glowObject.m_flBlue = colorlocal.RGBA[2] / 255.0f;
					glowObject.m_flAlpha = 150.0f / 255.0f;
					glowObject.m_bRenderWhenOccluded = true;
					glowObject.m_bRenderWhenUnoccluded = false;
					continue;
				}
				else if (!SETTINGS::settings.glowlocal && is_local_player)
					continue;

				if (entity->GetHealth() <= 0) continue;
				if (entity->GetIsDormant())	continue;
				if (entity->GetClientClass()->m_ClassID != 40) continue;

				if (is_teammate && SETTINGS::settings.glowteam)
				{
					glowObject.m_nGlowStyle = 0; //0;
					glowObject.m_flRed = colorTeam.RGBA[0] / 255.0f;
					glowObject.m_flGreen = colorTeam.RGBA[1] / 255.0f;
					glowObject.m_flBlue = colorTeam.RGBA[2] / 255.0f;
					glowObject.m_flAlpha = 150.0f / 255.0f;
					glowObject.m_bRenderWhenOccluded = true;
					glowObject.m_bRenderWhenUnoccluded = false;
					continue;
				}
				else if (is_teammate && !SETTINGS::settings.glowteam)
					continue;

				if (SETTINGS::settings.glowenable)
				{
					glowObject.m_nGlowStyle = 0;//0;
					glowObject.m_flRed = color.RGBA[0] / 255.0f;
					glowObject.m_flGreen = color.RGBA[1] / 255.0f;
					glowObject.m_flBlue = color.RGBA[2] / 255.0f;
					glowObject.m_flAlpha = 150.0f / 255.0f;
					glowObject.m_bRenderWhenOccluded = true;
					glowObject.m_bRenderWhenUnoccluded = false;
				}
			}

						

			if (SETTINGS::settings.smoke_bool)
			{
				std::vector<const char*> vistasmoke_wireframe = { "particle/vistasmokev1/vistasmokev1_smokegrenade" };

				std::vector<const char*> vistasmoke_nodraw =
				{
					"particle/vistasmokev1/vistasmokev1_fire",
					"particle/vistasmokev1/vistasmokev1_emods",
					"particle/vistasmokev1/vistasmokev1_emods_impactdust",
				};

				for (auto mat_s : vistasmoke_wireframe)
				{
					SDK::IMaterial* mat = INTERFACES::MaterialSystem->FindMaterial(mat_s, TEXTURE_GROUP_OTHER);
					mat->SetMaterialVarFlag(SDK::MATERIAL_VAR_WIREFRAME, true); //wireframe
				}

				for (auto mat_n : vistasmoke_nodraw)
				{
					SDK::IMaterial* mat = INTERFACES::MaterialSystem->FindMaterial(mat_n, TEXTURE_GROUP_OTHER);
					mat->SetMaterialVarFlag(SDK::MATERIAL_VAR_NO_DRAW, true);
				}

				static auto smokecout = *(DWORD*)(linegoesthrusmoke + 0x8);
				*(int*)(smokecout) = 0;
			}

		}
	}

	struct hud_weapons_t {
		std::int32_t* get_weapon_count() {
			return reinterpret_cast<std::int32_t*>(std::uintptr_t(this) + 0x80);
		}
	};
	template<class T>
	static T* FindHudElement(const char* name)
	{
		static auto pThis = *reinterpret_cast<DWORD * *>(UTILS::FindSignature("client_panorama.dll", "B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08") + 1);
		static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(void*, const char*)>(UTILS::FindSignature("client_panorama.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39"));
		return (T*)find_hud_element(pThis, name);
	}
	void KnifeApplyCallbk()
	{

		static auto clear_hud_weapon_icon_fn =
			reinterpret_cast<std::int32_t(__thiscall*)(void*, std::int32_t)>(
				UTILS::FindSignature("client_panorama.dll", "55 8B EC 51 53 56 8B 75 08 8B D9 57 6B FE 2C 89 5D FC"));

		auto element = FindHudElement<std::uintptr_t*>("CCSGO_HudWeaponSelection");

		auto hud_weapons = reinterpret_cast<hud_weapons_t*>(std::uintptr_t(element) - 0xA0);
		if (hud_weapons == nullptr)
			return;

		if (!*hud_weapons->get_weapon_count())
			return;

		for (std::int32_t i = 0; i < *hud_weapons->get_weapon_count(); i++)
			i = clear_hud_weapon_icon_fn(hud_weapons, i);

		static SDK::ConVar* Meme = INTERFACES::cvar->FindVar("cl_fullupdate");
		Meme->nFlags &= ~FCVAR_CHEAT;
		INTERFACES::Engine->ClientCmd_Unrestricted("cl_fullupdate");

	}

	void dothirdperson(SDK::CViewSetup* pSetup) {
		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());

		if (!local_player)
			return;

		auto weapon = reinterpret_cast<SDK::CBaseWeapon*>(INTERFACES::ClientEntityList->GetClientEntity(local_player->GetActiveWeaponIndex()));
		if (!weapon) return;

		if (local_player->GetIsScoped())
			return;

		if (in_tp && local_player->is_dead())
			in_tp = false;

		if (!SETTINGS::settings.tp_bool)
			pSetup->fov = 110;

		if (SETTINGS::settings.tp_bool && !in_tp)
			pSetup->fov = 110;

		if (SETTINGS::settings.disable_tp_on_nade)
		{
			if (in_tp && weapon->is_grenade())
				in_tp = false;
		}
	}
	void __fastcall HookedOverrideView(void* ecx, void* edx, SDK::CViewSetup* pSetup)
	{
		auto local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
		if (!local_player) return;

		auto animstate = local_player->GetAnimState();
		if (!animstate) return;

		if (GetAsyncKeyState(SETTINGS::settings.thirdperson_int) & 1)
			in_tp = !in_tp;

		pSetup->angles -= *local_player->GetAimPunchAngle() * 0.9f + *local_player->GetViewPunchAngle();

		if (GetAsyncKeyState(SETTINGS::settings.Fakecrouchkey))
		{
			pSetup->origin.z = local_player->GetAbsOrigin().z + 64.f;
		}

		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
			GrenadePrediction::instance().View(pSetup);
			auto GetCorrectDistance = [&local_player](float ideal_distance) -> float //lambda
			{
				Vector inverse_angles;
				INTERFACES::Engine->GetViewAngles(inverse_angles);

				inverse_angles.x *= -1.f, inverse_angles.y += 180.f;

				Vector direction;
				MATH::AngleVectors(inverse_angles, &direction);

				SDK::CTraceWorldOnly filter;
				SDK::trace_t trace;
				SDK::Ray_t ray;

				ray.Init(local_player->GetVecOrigin() + local_player->GetViewOffset(), (local_player->GetVecOrigin() + local_player->GetViewOffset()) + (direction * (ideal_distance + 5.f)));
				INTERFACES::Trace->TraceRay(ray, MASK_ALL, &filter, &trace);

				return ideal_distance * trace.flFraction;
			};

			if (SETTINGS::settings.tp_bool && in_tp)
			{
				if (local_player->GetHealth() <= 0)
					local_player->SetObserverMode(5);

				if (!INTERFACES::Input->m_fCameraInThirdPerson)
				{
					INTERFACES::Input->m_fCameraInThirdPerson = true;
					INTERFACES::Input->m_vecCameraOffset = Vector(GLOBAL::real_angles.x, GLOBAL::real_angles.y, GetCorrectDistance(100));

					Vector camForward;
					MATH::AngleVectors(Vector(INTERFACES::Input->m_vecCameraOffset.x, INTERFACES::Input->m_vecCameraOffset.y, 0), &camForward);
				}
			}
			else
			{
				INTERFACES::Input->m_fCameraInThirdPerson = false;
				INTERFACES::Input->m_vecCameraOffset = Vector(GLOBAL::real_angles.x, GLOBAL::real_angles.y, 0);
			}

			auto zoomsensration = INTERFACES::cvar->FindVar("zoom_sensitivity_ratio_mouse");

			if (SETTINGS::settings.fixscopesens)
				zoomsensration->SetValue("0");

			if (SETTINGS::settings.aim_type == 0)
			{
				if (!local_player->GetIsScoped())
					pSetup->fov = SETTINGS::settings.fov_val;
				else if (local_player->GetIsScoped() && SETTINGS::settings.removescoping)
					pSetup->fov = SETTINGS::settings.fov_val;
			}
			else if (!(SETTINGS::settings.aim_type == 0) && !local_player->GetIsScoped())
				pSetup->fov = 90;

			dothirdperson(pSetup);
		}
		original_override_view(ecx, pSetup);
	}
	void __fastcall HookedTraceRay(void *thisptr, void*, const SDK::Ray_t &ray, unsigned int fMask, SDK::ITraceFilter *pTraceFilter, SDK::trace_t *pTrace)
	{
		original_trace_ray(thisptr, ray, fMask, pTraceFilter, pTrace);
		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
			pTrace->surface.flags |= SURF_SKY;
	}
	bool __fastcall HookedGetBool(void* pConVar, void* edx)
	{
		if ((uintptr_t)_ReturnAddress() == CAM_THINK)
			return true;

		return original_get_bool(pConVar);
	}
	float __fastcall GetViewmodelFOV()
	{
		if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
		{
			float player_fov = original_viewmodel_fov();

			if (SETTINGS::settings.esp_bool)
				player_fov = SETTINGS::settings.viewfov_val;

			return player_fov;
		}
	}


	ImFont* tabss;
	ImFont* fDefault;
	void OpenMenu()
	{
		static bool is_down = false;
		static bool is_clicked = false;
		if (GetAsyncKeyState(VK_INSERT))
		{
			is_clicked = false;
			is_down = true;
		}
		else if (!GetAsyncKeyState(VK_INSERT) && is_down)
		{
			is_clicked = true;
			is_down = false;
		}
		else
		{
			is_clicked = false;
			is_down = false;
		}

		if (is_clicked)
		{
			SETTINGS::settings.menu_open = !SETTINGS::settings.menu_open;

		}
	}




	LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg) {
		case WM_LBUTTONDOWN:
			PressedKeys[VK_LBUTTON] = true;
			break;
		case WM_LBUTTONUP:
			PressedKeys[VK_LBUTTON] = false;
			break;
		case WM_RBUTTONDOWN:
			PressedKeys[VK_RBUTTON] = true;
			break;
		case WM_RBUTTONUP:
			PressedKeys[VK_RBUTTON] = false;
			break;
		case WM_MBUTTONDOWN:
			PressedKeys[VK_MBUTTON] = true;
			break;
		case WM_MBUTTONUP:
			PressedKeys[VK_MBUTTON] = false;
			break;
		case WM_XBUTTONDOWN:
		{
			UINT button = GET_XBUTTON_WPARAM(wParam);
			if (button == XBUTTON1)
			{
				PressedKeys[VK_XBUTTON1] = true;
			}
			else if (button == XBUTTON2)
			{
				PressedKeys[VK_XBUTTON2] = true;
			}
			break;
		}
		case WM_XBUTTONUP:
		{
			UINT button = GET_XBUTTON_WPARAM(wParam);
			if (button == XBUTTON1)
			{
				PressedKeys[VK_XBUTTON1] = false;
			}
			else if (button == XBUTTON2)
			{
				PressedKeys[VK_XBUTTON2] = false;
			}
			break;
		}
		case WM_KEYDOWN:
			PressedKeys[wParam] = true;
			break;
		case WM_KEYUP:
			PressedKeys[wParam] = false;
			break;
		default: break;
		}

		OpenMenu();

		if (d3d_init && SETTINGS::settings.menu_open && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		return CallWindowProc(INIT::OldWindow, hWnd, uMsg, wParam, lParam);
	}

	static int selectedcfg = 0;
	static std::string cfgname = " default";

	std::vector<std::string> configs;

	void getconfig()
	{
		//get all files on folder

		configs.clear();

		static char path[MAX_PATH];
		std::string szPath1;

		if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
			return;

		szPath1 = std::string(path) + "\\deathrow\\*";


		WIN32_FIND_DATA FindFileData;
		HANDLE hf;

		configs.push_back(" choose config");

		hf = FindFirstFile(szPath1.c_str(), &FindFileData);
		if (hf != INVALID_HANDLE_VALUE) {
			do {
				std::string filename = FindFileData.cFileName;

				if (filename == ".")
					continue;

				if (filename == "..")
					continue;

				if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					if (filename.find(".cfg") != std::string::npos)
					{
						configs.push_back(std::string(filename));
					}
				}
			} while (FindNextFile(hf, &FindFileData) != 0);
			FindClose(hf);
		}
	}



	void aimbot22()
	{
		const char* acc_mode[] = { "head", "performance", "multipoint", "bodyaim" };
		//caca
		if (ImGui::Button("general", ImVec2(85, 15)))
		{
			tab2 = 1;
		}

		ImGui::SameLine();

		if (ImGui::Button("beta", ImVec2(85, 15)))
		{
			tab2 = 2;

		}

		ImGui::Spacing();
		ImGui::Spacing();

		if (tab2 == 1)
		{

			ImGui::Columns(1);

			const char* hitboxes[] = { "Head", "Body Aim", "Hitscan" };

				ImGui::Checkbox("Enable Aimbot", &SETTINGS::settings.aim_bool);

				ImGui::Text("Hitboxes");
				ImGui::Combo("", &SETTINGS::settings.acc_type, hitboxes, ARRAYSIZE(hitboxes));
				//ImGui::ListBoxHeader(""); {
				//ImGui::Selectable("head", &settings::options.hitscan_head);
				//ImGui::Selectable("neck", &settings::options.hitscan_neck);
				//ImGui::Selectable("chest", &settings::options.hitscan_chest);
				//ImGui::Selectable("pelvis", &settings::options.hitscan_pelvis);
				//ImGui::Selectable("arms", &settings::options.hitscan_arms);
				//ImGui::Selectable("legs", &settings::options.hitscan_legs);
				//}
				//ImGui::ListBoxFooter();
				//ImGui::Checkbox(("smart body-aim"), &settings::options.smartbaim);

				ImGui::SliderInt("Hit-Chance", &SETTINGS::settings.chance_val, 0, 100);
				ImGui::SliderInt("Minimum Damage", &SETTINGS::settings.damage_val, 1, 100);
				ImGui::Checkbox(("More Aimpoints"), &SETTINGS::settings.multi_bool);
				if (SETTINGS::settings.multi_bool)
				{
					ImGui::SliderFloat("Head Scale", &SETTINGS::settings.point_val, 0, 1);
					ImGui::SliderFloat("Body Scale", &SETTINGS::settings.body_val, 0, 1);
				}
				//ImGui::Combo("baim on key", &settings::options.baim_key, key_binds, sizeof(key_binds));
				ImGui::Checkbox(("Auto Stop"), &SETTINGS::settings.stop_bool);
				ImGui::Checkbox(("Lag Compensation"), &SETTINGS::settings.rage_lagcompensation);
				ImGui::Checkbox(("Fakelag Prediction"), &SETTINGS::settings.fake_bool);

			ImGui::NextColumn();

		//ImGui::Checkbox(("slow-walk"), &SETTINGS::settings.slow_walk);
			//if (SETTINGS::settings.slow_walk)
			//	ImGui::Hotkey(("##slow_walk"), &SETTINGS::settings.slow_walk_key);
			//ImGui::Checkbox(("fast-duck"), &SETTINGS::settings.remove_duck_cooldown);
			//ImGui::Checkbox(("auto-zeus"), &SETTINGS::settings.autozeus);
			//ImGui::Checkbox(("auto-scope"), &SETTINGS::settings.auto_scope);
			//ImGui::Checkbox(("auto-revolver"), &SETTINGS::settings.auto_revolver);
			//ImGui::Checkbox(("resolver"), &SETTINGS::settings.resolve_bool);
			//ImGui::Checkbox(("override"), &SETTINGS::settings.override);
			//ImGui::Hotkey(("##override_key"), &SETTINGS::settings.overridekey);
		}
		else if (tab2 == 2)
		{
			ImGui::Columns(1);

			ImGui::Checkbox(("slow-walk"), &SETTINGS::settings.slow_walk);
			if (SETTINGS::settings.slow_walk)
				ImGui::Hotkey(("##slow_walk"), &SETTINGS::settings.slow_walk_key);
			ImGui::Checkbox(("fast-duck"), &SETTINGS::settings.remove_duck_cooldown);
			ImGui::Checkbox(("auto-revolver"), &SETTINGS::settings.auto_revolver);
			ImGui::Checkbox(("resolver"), &SETTINGS::settings.resolve_bool);
			ImGui::Checkbox(("override"), &SETTINGS::settings.override);
			ImGui::Hotkey(("##override_key"), &SETTINGS::settings.overridekey);
			ImGui::Checkbox(("auto-zeus"), &SETTINGS::settings.autozeus);
			ImGui::Checkbox(("auto-scope"), &SETTINGS::settings.auto_scope);
		}

	}

	void anti_aim()
	{

		if (ImGui::Button("general", ImVec2(85, 15)))
		{
			tab2 = 1;
		}

		ImGui::SameLine();

		if (ImGui::Button("manual", ImVec2(85, 15)))
		{
			tab2 = 2;

		}

		if (tab2 == 1)
		{
			const char* pitch[] = { " none", " emotion", " minimal", " fake down" };
			const char* yaw[] = { " none", " backwards", " backwards jitter", " 180z", " keybased", " freestanding desync" };

			ImGui::Columns(1);

			ImGui::Checkbox(("enable anti-aim"), &SETTINGS::settings.aa_bool);
			ImGui::Combo(("pitch"), &SETTINGS::settings.aa_pitch_type, pitch, ARRAYSIZE(pitch));
			ImGui::Combo("yaw", &SETTINGS::settings.aa_real_type, yaw, ARRAYSIZE(yaw));

			ImGui::Spacing();

			ImGui::Checkbox("jitter desync anti-aim", &SETTINGS::settings.desync_aa);
			ImGui::Checkbox("tick-based desync anti-aim", &SETTINGS::settings.desync_aa2);
			
			if (SETTINGS::settings.desync_aa)
			{
				ImGui::SliderFloat("", &SETTINGS::settings.desync_range, 0, 58);
			}

			ImGui::Spacing();

			ImGui::Checkbox(("disable thirdperson on nade"), &SETTINGS::settings.disable_tp_on_nade);
			ImGui::Text("Indicators Color"); ImGui::SameLine();
			ImGui::ColorEdit4(("##indicator"), SETTINGS::settings.invisible_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
		//	int(SETTINGS::settings.arrows_col[0] * 255.f), int(SETTINGS::settings.arrows_col[1] * 255.f), int(SETTINGS::settings.arrows_col[2] * 255.f)
		}

		ImGui::NextColumn();
		if (tab2 == 2)
		{
			if (SETTINGS::settings.aa_real_type == 4)
			{
				ImGui::Hotkey(("left"), &SETTINGS::settings.aa_left);
				ImGui::Hotkey(("right"), &SETTINGS::settings.aa_right);
				ImGui::Hotkey(("back"), &SETTINGS::settings.aa_back);
			}
		}
	}

	void visuals22()
	{
		if (ImGui::Button("players", ImVec2(85, 15)))
		{
			tab2 = 1;
		}

		ImGui::SameLine();

		if (ImGui::Button("models", ImVec2(85, 15)))
		{
			tab2 = 2;

		}

		ImGui::SameLine();
		
		if (ImGui::Button("visuals", ImVec2(85, 15)))
		{
			tab2 = 3;

		}

		ImGui::SameLine();

		if (ImGui::Button("removals", ImVec2(85, 15)))
		{
			tab2 = 4;

		}

		ImGui::SameLine();

		if (ImGui::Button("beta", ImVec2(85, 15)))
		{
			tab2 = 5;

		}

		if (tab2 == 1)
		{
			ImGui::Columns(1);

			ImGui::Checkbox(("enable visuals"), &SETTINGS::settings.esp_bool);
			ImGui::Checkbox(("draw box"), &SETTINGS::settings.box_bool);
			ImGui::Checkbox(("draw player name"), &SETTINGS::settings.name_bool);
			ImGui::Checkbox(("draw player weapon"), &SETTINGS::settings.weap_bool);
			ImGui::Checkbox(("draw player health"), &SETTINGS::settings.health_bool);
			ImGui::Checkbox(("draw event logs"), &SETTINGS::settings.info_bool);
			ImGui::Checkbox(("draw ammo"), &SETTINGS::settings.ammo_bool);
			ImGui::Checkbox(("draw fov arrows"), &SETTINGS::settings.fov_bool);
			ImGui::SameLine();
			ImGui::ColorEdit4(("##fov_arrows"), SETTINGS::settings.arrows_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(("draw radar"), &SETTINGS::settings.radar);
			ImGui::Checkbox(("lag comp hitbox"), &SETTINGS::settings.lag_comp_hitbox);
			ImGui::Checkbox(("asus walls"), &SETTINGS::settings.asus_bool);
			ImGui::Checkbox(("nightmode"), &SETTINGS::settings.night_bool);
		}
		if (tab2 == 2)
		{
			const char* chams[] = { " none", " metallic", " normal" };
			ImGui::Combo("chams", &SETTINGS::settings.chams_type, chams, IM_ARRAYSIZE(chams), 3);
			ImGui::SameLine();
		
			ImGui::ColorEdit4(("##chams1"), SETTINGS::settings.vmodel_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(("enemy glow"), &SETTINGS::settings.glowenable);
			ImGui::SameLine();
			ImGui::ColorEdit4(("##glow"), SETTINGS::settings.glow_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
		}
		ImGui::NextColumn();
		if (tab2 == 3)
		{
			ImGui::Checkbox(("bullet tracers"), &SETTINGS::settings.beam_bool);
			ImGui::SameLine();
			ImGui::ColorEdit4(("##tracer"), SETTINGS::settings.bulletlocal_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox(("bullet impact"), &SETTINGS::settings.bullet_impact);
			ImGui::Checkbox(("thirdperson"), &SETTINGS::settings.tp_bool);
			if (SETTINGS::settings.tp_bool)
				ImGui::Hotkey("##tp_key", &SETTINGS::settings.thirdperson_int);
			ImGui::Checkbox(("fix sensitivity"), &SETTINGS::settings.fixscopesens);
			ImGui::Checkbox(("static crosshair"), &SETTINGS::settings.static_crosshair);
			ImGui::Checkbox(("force radgoll"), &SETTINGS::settings.force_ragdoll);
		}
		if (tab2 == 4)
		{
			ImGui::Checkbox(("remove smoke"), &SETTINGS::settings.smoke_bool);
			ImGui::Checkbox(("remove flash"), &SETTINGS::settings.no_flash);
			ImGui::Checkbox(("remove scope"), &SETTINGS::settings.scope_bool);
			ImGui::Checkbox(("remove zoom"), &SETTINGS::settings.removescoping);
		}
		if (tab2 == 5)
		{
			ImGui::SliderFloat("render fov", &SETTINGS::settings.fov_val, 0, 179);
			ImGui::SliderFloat("viewmodel fov", &SETTINGS::settings.viewfov_val, 0, 179);
			ImGui::Checkbox("aa arrows", &SETTINGS::settings.rifk_arrow);
			if (SETTINGS::settings.rifk_arrow)
			{
				ImGui::SliderFloat("height", &SETTINGS::settings.aa_arrows_height, 0, 30);
				ImGui::SliderFloat("width", &SETTINGS::settings.aa_arrows_width, 0, 15);
			}

		}
	}

	void misc()
	{
		if (ImGui::Button("misc", ImVec2(85, 15)))
		{
			tab2 = 1;
		}

		ImGui::SameLine();

		if (ImGui::Button("configs", ImVec2(85, 15)))
		{
			tab2 = 2;

		}

		//static bool omihitbox = 0;

		if (tab2 == 1)
		{
		
		}

		ImGui::NextColumn();
		if (tab2 == 2)
		{
			getconfig();
			ImGui::Spacing();
			if (ImGui::Combo("cfg", &selectedcfg, [](void* data, int idx, const char** out_text)
				{
					*out_text = configs[idx].c_str();
					return true;
				}, nullptr, configs.size(), 10))
			{
				cfgname = configs[selectedcfg];
				cfgname.erase(cfgname.length() - 4, 4);
				strcpy(SETTINGS::settings.config_name, cfgname.c_str());
			}

				ImGui::Spacing();

				static bool create;
				if (ImGui::Button("save"))
				{
					Config->Save();
				}
				ImGui::SameLine();
				if (ImGui::Button("load"))
				{
					Config->Load();

				}

				ImGui::Spacing();

				ImGui::Text("new cfg");
				ImGui::InputText("name", SETTINGS::settings.config_name, 52);
				if (ImGui::Button("create & save", ImVec2(-1, 15)))
				{
					Config->Save();
					create = !create;
				}
				if (ImGui::Button("cancel", ImVec2(-1, 15)))
				{
					create = !create;
				}
	//	if (ImGui::Button("new config", ImVec2(-1, 15))) create = !create;
		if (ImGui::Button("reset settings", ImVec2(-1, 15))) Config->setup();

		if (create)
		{
		/*	ImGui::Begin("##create", &create, ImVec2(160, 90), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
			ImGui::Text("config name:");
			ImGui::InputText("name", SETTINGS::settings.config_name, 52);
			if (ImGui::Button("create & save", ImVec2(-1, 15)))
			{
				Config->Save();
				create = !create;
			}
			if (ImGui::Button("cancel", ImVec2(-1, 15)))
				create = !create;
			ImGui::End();*/
		}
		}
	}

	void skins()
	{
		ImGui::Columns(2);

		ImGui::Checkbox("enable", &SETTINGS::settings.skinenabled);

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		if (tab1 == 1)//skinchanger
		{/*
			static int currWeap = SETTINGS::settings.currentWeapon;
			int pk = SETTINGS::settings.W[SETTINGS::settings.currentWeapon].ChangerSkin;
			static int currWeapSkin = SETTINGS::settings.W[SETTINGS::settings.currentWeapon].ChangerSkin;
			static char weapName[18];
			static char filterSkins[32];
			static char filterGuns[32];

			ImGui::InputText(("search"), filterGuns, IM_ARRAYSIZE(filterGuns));
			ImGui::BeginChild(5, ImVec2(-1, 250), true, 0);
			for (auto it : guns)
			{
				if (strcmp(it.second, " default") == 0)
					continue;

				if (!(std::string(it.second).find(std::string(filterGuns)) != std::string::npos))
					continue;

				const bool item_selected = ((int)it.first == (int)SETTINGS::settings.currentWeapon);

				if (ImGui::Selectable(it.second, item_selected))
				{
					SETTINGS::settings.currentWeapon = (int)it.first;
				}
			}
			ImGui::EndChild();
			ImGui::NextColumn();
			std::string skinName = weaponnames(SETTINGS::settings.currentWeapon);
			ImGui::InputText(("search##1"), filterSkins, IM_ARRAYSIZE(filterSkins));
			ImGui::InputInt(("custom id"), &SETTINGS::settings.W[SETTINGS::settings.currentWeapon].ChangerSkin);
			ImGui::BeginChild(("##skins"), ImVec2(-1, 233), true, 0);
			std::string skinStr = "";
			int curItem = -1;
			int s = 0;
			for (auto it : weapon_skins)
			{
				if (!(std::string(it.second).find(std::string(filterSkins)) != std::string::npos))
					continue;

				bool selected = ((int)it.first == (int)SETTINGS::settings.W[SETTINGS::settings.currentWeapon].ChangerSkin);

				if (ImGui::Selectable(it.second, selected))
				{
					SETTINGS::settings.W[SETTINGS::settings.currentWeapon].ChangerSkin = (int)it.first;
					
				}
			}*/
			//ImGui::EndChild();
		}
	}
	void GUI_Init(IDirect3DDevice9* pDevice)
	{
		ImGui_ImplDX9_Init(INIT::Window, pDevice);
		ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Droid_compressed_data, Droid_compressed_size, 14.f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255); // Text Color
		style.Colors[ImGuiCol_MenuMain] = ImColor(163, 117, 0, 200);
		style.Colors[ImGuiCol_MenuMain2] = ImColor(255, 183, 0, 255);
		style.Colors[ImGuiCol_WindowBg] = ImColor(5, 5, 5, 255); //Menu background color
																			  //style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);	
/*		style.Colors[ImGuiCol_Border] = ImColor(255, 196, 3, 255); //Borders color of the menu
		style.Colors[ImGuiCol_Button] = ImColor(62, 66, 76, 180);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(1, 150, 3, 100); //Buton color when we go with the mouse
		style.Colors[ImGuiCol_ButtonActive] = ImColor(1, 150, 3, 180); //Button color when we press
		style.Colors[ImGuiCol_TitleBg] = ImColor(210, 242, 0, 255); //Title of the menu background color
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(210, 242, 0, 255); //Title of the active menu background color
																		  //style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
		//fula
		style.Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30, 180); //Background color of the checkbox ...
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(210, 242, 0, 100); //Background of the item when hovered
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(210, 242, 0, 255); //Background color of the active item

		style.Colors[ImGuiCol_ComboBg] = ImColor(5, 5, 5, 255); //Combobox background color
		style.Colors[ImGuiCol_CheckMark] = ImColor(255, 196, 3, 255); //Radiobutton or checkbox mark color

		style.Colors[ImGuiCol_MenuBarBg] = ImColor(210, 242, 0, 255);
		style.Colors[ImGuiCol_ScrollbarBg] = ImColor(5, 5, 5, 255); //Scrollbar background color
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(255, 196, 3, 255); //Scrollbar color
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(210, 242, 0, 100); //Scrollbar color when hovered
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(210, 242, 0, 255); //Scrollbar color when grabed
		style.Colors[ImGuiCol_SliderGrab] = ImColor(50, 50, 50, 255); //Slider color 
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 196, 3, 255);//Slider color when grabed
		style.Colors[ImGuiCol_Header] = ImColor(255, 196, 3, 255);//Color of the selected item in a combolist
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(210, 242, 0, 100);//Color of the hovered item in a combolist
		style.Colors[ImGuiCol_HeaderActive] = ImColor(210, 242, 0, 255);//Color of the selected item in a combolist when pressed
		*/
		
		//lstest color since update v

		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	//	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.36f, 0.22f, 0.00f, 0.79f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.24f, 0.17f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.01f, 0.00f, 0.98f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.80f, 0.56f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.65f, 0.00f, 0.67f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.89f, 0.45f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.02f, 0.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.31f, 0.00f, 0.49f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.26f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.83f, 0.48f, 0.00f, 0.89f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.55f, 0.02f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.53f, 0.07f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.01f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.56f, 0.30f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.88f, 0.59f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.97f, 0.48f, 0.13f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImColor(62, 66, 76, 180);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(1, 150, 3, 100); //Buton color when we go with the mouse
		style.Colors[ImGuiCol_ButtonActive] = ImColor(1, 150, 3, 180); //Button color when we press
		style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.66f, 0.28f, 0.00f, 0.32f);
		style.Colors[ImGuiCol_Separator] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	//	style.Colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.02f, 0.00f, 0.98f);
	//	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.99f, 0.59f, 0.00f, 0.00f);
	//	style.Colors[ImGuiCol_TabActive] = ImVec4(0.83f, 0.27f, 0.00f, 1.00f);
	//	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 196, 3, 255);
	

		style.WindowRounding = 0.f;
		style.FramePadding = ImVec2(0, 0);
		style.ScrollbarSize = 6.f;
		style.ScrollbarRounding = 0.f;
		style.GrabMinSize = 6.f;

		bigmenu_font = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(rawData_compressed_data_base85, 70);
		menu_font = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(rawData_compressed_data_base85, 18);
		smallmenu_font = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(smalll_compressed_data_base85, 13);

		d3d_init = true;
	}


	SDK::CBaseWeapon* xd(SDK::CBaseEntity* xz)
	{
		if (!INTERFACES::Engine->IsConnected())
			return nullptr;
		if (!xz->IsAlive())
			return nullptr;

		HANDLE weaponData = *(HANDLE*)((DWORD)xz + OFFSETS::m_hActiveWeapon);
		return (SDK::CBaseWeapon*)INTERFACES::ClientEntityList->GetClientEntityFromHandle(weaponData);
	}

	short SafeWeaponID()
	{
		SDK::CBaseEntity* local_player = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
		if (!(local_player))
			return 0;

		SDK::CBaseWeapon* WeaponC = xd(local_player);

		if (!(WeaponC))
			return 0;

		return WeaponC->GetItemDefenitionIndex();
	}

	bool EntityIsInvalid(SDK::CBaseEntity* Entity)
	{
		if (!Entity)
			return true;
		if (Entity->GetHealth() <= 0)
			return true;
		if (Entity->GetIsDormant())
			return true;
		return false;
	}

	Vector2D RotatePoint(Vector EntityPos, Vector LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck, bool angleInRadians = false)
	{
		float r_1, r_2;
		float x_1, y_1;
		r_1 = -(EntityPos.y - LocalPlayerPos.y);
		r_2 = EntityPos.x - LocalPlayerPos.x;
		float Yaw = angle - 90.0f;
		float yawToRadian = Yaw * (float)(M_PI / 180.0F);
		x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
		y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;
		*viewCheck = y_1 < 0;
		x_1 *= zoom;
		y_1 *= zoom;
		int sizX = sizeX / 2;
		int sizY = sizeY / 2;
		x_1 += sizX;
		y_1 += sizY;
		if (x_1 < 5)
			x_1 = 5;
		if (x_1 > sizeX - 5)
			x_1 = sizeX - 5;
		if (y_1 < 5)
			y_1 = 5;
		if (y_1 > sizeY - 5)
			y_1 = sizeY - 5;
		x_1 += posX;
		y_1 += posY;
		return Vector2D(x_1, y_1);
	}

	void DrawRadar()
	{
		if (SETTINGS::settings.Radargui.Enabled)
		{
			ImGuiStyle& style = ImGui::GetStyle();
			ImVec2 oldPadding = style.WindowPadding;
			float oldAlpha = style.Colors[ImGuiCol_WindowBg].w;
			style.WindowPadding = ImVec2(0, 0);
			style.Colors[ImGuiCol_WindowBg].w = 1.f;
			if (ImGui::Begin("Radar", &SETTINGS::settings.Radargui.Enabled, ImVec2(200, 200), 0.4F, ImGuiWindowFlags_NoTitleBar |/*ImGuiWindowFlags_NoResize | */ImGuiWindowFlags_NoCollapse))
			{
				ImVec2 siz = ImGui::GetWindowSize();
				ImVec2 pos = ImGui::GetWindowPos();
				ImDrawList* DrawList = ImGui::GetWindowDrawList();
				DrawList->AddRect(ImVec2(pos.x - 6, pos.y - 6), ImVec2(pos.x + siz.x + 6, pos.y + siz.y + 6), CColor::Black().GetD3DColor(), 0.0F, -1, 1.5f);
				ImDrawList* windowDrawList = ImGui::GetWindowDrawList();
				windowDrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), CColor::Black().GetD3DColor(), 1.5f);
				windowDrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), CColor::Black().GetD3DColor(), 1.5f);
				if (INTERFACES::Engine->IsConnected() && INTERFACES::Engine->IsInGame())
				{
					auto LocalPlayer = INTERFACES::ClientEntityList->GetClientEntity(INTERFACES::Engine->GetLocalPlayer());
					if (LocalPlayer)
					{
						Vector LocalPos = LocalPlayer->GetEyePosition();
						Vector ang;
						INTERFACES::Engine->GetViewAngles(ang);
						for (int i = 0; i < INTERFACES::Engine->GetMaxClients(); i++) {
							SDK::CBaseEntity* pBaseEntity = INTERFACES::ClientEntityList->GetClientEntity(i);
							SDK::player_info_t pInfo;
							INTERFACES::Engine->GetPlayerInfo(i, &pInfo);
							if (EntityIsInvalid(pBaseEntity))
								continue;
							SDK::CBaseEntity* observerTarget = INTERFACES::ClientEntityList->GetClientEntityFromHandle(LocalPlayer->GetObserverTargetHandle());
							bool bIsEnemy = (LocalPlayer->GetTeam() != pBaseEntity->GetTeam() || pBaseEntity == observerTarget || pBaseEntity == LocalPlayer) ? true : false;
							if (SETTINGS::settings.Radargui.OnlyEnemy && !bIsEnemy)
								continue;
							bool viewCheck = false;
							Vector2D EntityPos = RotatePoint(pBaseEntity->GetVecOrigin(), LocalPos, pos.x, pos.y, siz.x, siz.y, ang.y, SETTINGS::settings.Radargui.Range, &viewCheck);
							//ImU32 clr = (bIsEnemy ? (isVisibled ? Color::LightGreen() : Color::Blue()) : Color::White()).GetU32();
							ImU32 clr = (bIsEnemy ? CColor::Red() : CColor::LightBlue()).GetD3DColor();
							static bool drawname = true;
							if (pBaseEntity == observerTarget || pBaseEntity == LocalPlayer)
							{
								clr = CColor::White().GetD3DColor();
								drawname = false;
							}
							else
								drawname = true;
							int s = 2;
							windowDrawList->AddRect(ImVec2(EntityPos.x - s, EntityPos.y - s),
								ImVec2(EntityPos.x + s, EntityPos.y + s),
								clr);
							//		RECT TextSize = D::GetTextSize(F::ESP, pInfo.name);
							//	if (drawname && Vars.Misc.Radar.Nicks)
							//		windowDrawList->AddText(ImVec2(EntityPos.x - (TextSize.left / 2), EntityPos.y - s), CColor::White().GetU32(), pInfo.name);
						}
					}
				}
			}
			ImGui::End();
			style.WindowPadding = oldPadding;
			style.Colors[ImGuiCol_WindowBg].w = oldAlpha;
		}

	}

	std::vector<int> GetObservervators(int playerId)
	{
		std::vector<int> SpectatorList;

		SDK::CBaseEntity* pPlayer = (SDK::CBaseEntity*)INTERFACES::ClientEntityList->GetClientEntity(playerId);

		if (!pPlayer)
			return SpectatorList;

		if (!pPlayer->IsAlive())
		{
			SDK::CBaseEntity* pObserverTarget = (SDK::CBaseEntity*)INTERFACES::ClientEntityList->GetClientEntityFromHandle(pPlayer->GetObserverTargetHandle());

			if (!pObserverTarget)
				return SpectatorList;

			pPlayer = pObserverTarget;
		}

		for (int PlayerIndex = 0; PlayerIndex < 65; PlayerIndex++)
		{
			SDK::CBaseEntity* pCheckPlayer = (SDK::CBaseEntity*)INTERFACES::ClientEntityList->GetClientEntity(PlayerIndex);

			if (!pCheckPlayer)
				continue;

			if (pCheckPlayer->GetIsDormant() || pCheckPlayer->IsAlive())
				continue;

			SDK::CBaseEntity* pObserverTarget = (SDK::CBaseEntity*)INTERFACES::ClientEntityList->GetClientEntityFromHandle(pCheckPlayer->GetObserverTargetHandle
			());

			if (!pObserverTarget)
				continue;

			if (pPlayer != pObserverTarget)
				continue;

			SpectatorList.push_back(PlayerIndex);
		}

		return SpectatorList;
	}

	void SpectatorList()
	{
		if (!SETTINGS::settings.spectators)
			return;

		if (!INTERFACES::Engine->IsInGame() && !INTERFACES::Engine->IsConnected())
			return;

		int specs = 0;
		int modes = 0;
		std::string spect = "";
		std::string mode = "";
		int DrawIndex = 1;

		for (int playerId : GetObservervators(INTERFACES::Engine->GetLocalPlayer()))
		{
			if (playerId == INTERFACES::Engine->GetLocalPlayer())
				continue;

			SDK::CBaseEntity* pPlayer = (SDK::CBaseEntity*)INTERFACES::ClientEntityList->GetClientEntity(playerId);

			if (!pPlayer)
				continue;

			SDK::player_info_t Pinfo;
			INTERFACES::Engine->GetPlayerInfo(playerId, &Pinfo);

			//if (Pinfo.fakeplayer)
			//	continue;

			spect += Pinfo.name;
			spect += "\n";
			specs++;

			if (spect != "")
			{
				CColor PlayerObsColor;
				switch (pPlayer->GetObserverMode())
				{
				case 4:
					mode += "Perspective";
					break;
				case 5:
					mode += "3rd Person";
					break;
				case 6:
					mode += "Free look";
					break;
				case 1:
					mode += "Deathcam";
					break;
				case 2:
					mode += "Freezecam";
					break;
				case 3:
					mode += "Fixed";
					break;
				default:
					break;
				}

				mode += "\n";
				modes++;
			}
		}
		bool Spectators = true;
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImVec4(.137f, .137f, .137f, 1.00f);
		//ImGui::PushFont(Main2);
		if (ImGui::Begin("Spectator List", &Spectators, ImVec2(200, 250), 0.5f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoScrollbar))
		{

			if (specs > 0) spect += "\n";
			if (modes > 0) mode += "\n";
			ImVec2 size = ImGui::CalcTextSize(spect.c_str());

			ImGui::SetWindowSize(ImVec2(200, 40 + size.y));
			ImGui::Columns(2);

			ImGui::Text("Name");
			ImGui::NextColumn();

			ImGui::Text("Mode");
			ImGui::NextColumn();
			ImGui::Separator();

			ImGui::Text(spect.c_str());
			ImGui::NextColumn();

			ImGui::Text(mode.c_str());
			ImGui::Columns(1);
			DrawIndex++;

		}
		//ImGui::PopFont();
		ImGui::End();
	}

	IDirect3DTexture9 *FonBar1 = nullptr;

	long __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice)
	{
		static auto ofunc = directz.get_original<EndSceneFn>(42);

		D3DCOLOR rectColor = D3DCOLOR_XRGB(255, 0, 0);
		D3DRECT BarRect = { 1, 1, 1, 1 };
		ImGuiStyle& style = ImGui::GetStyle();
		pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, rectColor, 0, 0);

		if (!d3d_init)
			GUI_Init(pDevice);

		static const D3DRENDERSTATETYPE backupStates[] = { D3DRS_COLORWRITEENABLE, D3DRS_ALPHABLENDENABLE, D3DRS_SRCBLEND, D3DRS_DESTBLEND, D3DRS_BLENDOP, D3DRS_FOGENABLE };
		static const int size = sizeof(backupStates) / sizeof(DWORD);

		DWORD oldStates[size] = { 0 };

		SaveState(pDevice);

		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

		ImGui_ImplDX9_NewFrame();

		static int page = 0;

		static bool Texturedxd, Textured, Textured2, Textured3, Textured4, Textured5, Textured6, Textured7 = false;

		if (SETTINGS::settings.menu_open)
		{
			// 750 500 
			ImVec2 pos;
		//	pos = ImGui::GetWindowPos();
		
			/*

			,,,,,,,,,,,,,,,,,,,,,,$$$$
			,,,,,,,,,,,,,,,,,,,,,,$$$$
			,,,,,,,,,,,$$$$$$$$$$$$$$$$$
			,,,,,,,$$$$$$$$$$$$$$$$$$$$$$
			,,,,,$$$$$$$,,,,,,,$$$$,,,,$$$$$$$$
			,,,$$$$$$,,,,,,,,,,$$$$,,,,,,,,$$$$$$$
			,,$$$$$$,,,,,,,,,,,$$$$,,,,,,,,,,$$$$$$
			,,$$$$$$,,,,,,,,,,,$$$$
			,,$$$$$$,,,,,,,,,,,$$$$
			,,,$$$$$$,,,,,,,,,,$$$$
			,,,,$$$$$$$$,,,,,,$$$$																		MENU 
			,,,,,,$$$$$$$$$$$$$$$																				"MADE"
			,,,,,,,,,,$$$$$$$$$$$$$$$$$$																					BY		
			,,,,,,,,,,,,,,,,,$$$$$$$$$$$$$$$$																					omi#9046 ( doin simple menus 4 free if u want just add discord and dm me )
			,,,,,,,,,,,,,,,,,,,,,,$$$$,$$$$$$$$$$
			,,,,,,,,,,,,,,,,,,,,,,$$$$,,,,,,,$$$$$$$
			,,,,,,,,,,,,,,,,,,,,,,$$$$,,,,,,,,,,$$$$$$
			,,,,,,,,,,,,,,,,,,,,,,$$$$,,,,,,,,,,,$$$$$$
			$$$$$$$,,,,,,,,,,,,$$$$,,,,,,,,,,$$$$$$$
			,$$$$$$,,,,,,,,,,,,$$$$,,,,,,,,,,$$$$$$$
			,,$$$$$$$,,,,,,,,,,$$$$,,,,,,,,$$$$$$$$
			,,,$$$$$$$$,,,,,,,$$$$,,,,,,$$$$$$$$
			,,,,,,$$$$$$$$$$$$$$$$$$$$$$$$
			,,,,,,,,,,$$$$$$$$$$$$$$$$$$$
			,,,,,,,,,,,,,,,,,,$$$$$$$$
			,,,,,,,,,,,,,,,,,,,,,,$$$$
			,,,,,,,,,,,,,,,,,,,,,,$$$$

			*/



			ImGui::SetNextWindowSize(ImVec2(840, 560), ImGuiCond_FirstUseEver);
			ImGui::Begin("premium pay2cheat name here. | deathrow ", &menu_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
			{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				ImGui::BeginChild("tab child", ImVec2(820, 60), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
				{
					if (ImGui::Button("aimbot", ImVec2(127, 45))) page = 0; ImGui::SameLine();
					if (ImGui::Button("anti-hit", ImVec2(127, 45))) page = 1; ImGui::SameLine();
					if (ImGui::Button("players", ImVec2(127, 45))) page = 2; ImGui::SameLine();
					if (ImGui::Button("esp", ImVec2(127, 45))) page = 3; ImGui::SameLine();
					if (ImGui::Button("misc", ImVec2(127, 45))) page = 4; ImGui::SameLine();
					if (ImGui::Button("config", ImVec2(127, 45))) page = 5;

				}
				ImGui::EndChild();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				ImGui::BeginChild("main child", ImVec2(820, 473), ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
				{
					if (page == 0)//rage
					{
						ImGui::Columns(3, false);

						const char* hitboxes[] = { "head", "body aim", "hitscan" };

						ImGui::Checkbox("enable rage aimbot", &SETTINGS::settings.aim_bool);
						static bool omihitbox = 0;
					
						ImGui::Combo("", &SETTINGS::settings.acc_type, hitboxes, ARRAYSIZE(hitboxes));
						ImGui::Checkbox("open hitboxes window", &omihitbox);

						if (omihitbox)
						{
							ImGui::SetNextWindowSize(ImVec2(160, 250), ImGuiCond_FirstUseEver);
							ImGui::Begin("##create", &omihitbox, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
							{
								ImGui::Text("select hitboxes");
								ImGui::Checkbox("head", &SETTINGS::settings.hitscan_head);
								ImGui::Checkbox("neck", &SETTINGS::settings.hitscan_neck);
								ImGui::Checkbox("chest", &SETTINGS::settings.hitscan_chest);
								ImGui::Checkbox("pelvis", &SETTINGS::settings.hitscan_pelvis);
								ImGui::Checkbox("arms", &SETTINGS::settings.hitscan_arms);
								ImGui::Checkbox("legs", &SETTINGS::settings.hitscan_legs);
							}ImGui::End();
						}
						ImGui::Checkbox(("smart body-aim"), &SETTINGS::settings.smartbaim);

						ImGui::SliderInt("hit-chance", &SETTINGS::settings.chance_val, 0, 100);
						ImGui::SliderInt("awall min dmg", &SETTINGS::settings.damage_val, 1, 100);
						ImGui::Checkbox(("manual hitbox scale"), &SETTINGS::settings.multi_bool);
						if (SETTINGS::settings.multi_bool)
						{
							ImGui::SliderFloat("head", &SETTINGS::settings.point_val, 0, 1);
							ImGui::SliderFloat("body", &SETTINGS::settings.body_val, 0, 1);
						}

						ImGui::NextColumn();

						static const char* autostops[] =
						{
									"disabled",
									"fast",
									"full stop",
									"quick"

						};
						ImGui::Text("autostop mode");
						ImGui::Combo(XorStr("##autostop"), &SETTINGS::settings.autostopmethod, autostops, ARRAYSIZE(autostops));

						static const char* accuracyboost[] =
						{
							"disabled",
							"enabled"

						};
						ImGui::Text("boost accuracy");
						ImGui::Combo(XorStr("##boost"), &SETTINGS::settings.Accuracyboost, accuracyboost, ARRAYSIZE(accuracyboost));

						ImGui::Checkbox(("lag compensation"), &SETTINGS::settings.rage_lagcompensation);
						ImGui::Checkbox(("predict fake-lag"), &SETTINGS::settings.fake_bool);
						ImGui::Checkbox(("delay shot"), &SETTINGS::settings.delay_shot);


						ImGui::NextColumn();

						ImGui::Checkbox("slow walk", &SETTINGS::settings.Slowwalkenable);
						if (SETTINGS::settings.Slowwalkenable)
						{
							ImGui::Hotkey("slow walk key", &SETTINGS::settings.Slowwalkkey, ImVec2(40, 25));
							ImGui::Text("slow walk speed");
							ImGui::SliderFloat("###Slowwalkspeed", &SETTINGS::settings.Slowwalkspeed, 0, 100);
						}

						ImGui::Checkbox(("fast-duck"), &SETTINGS::settings.remove_duck_cooldown);
						const char* key_binds[] = { "none", "mouse1", "mouse2", "mouse3", "mouse4", "mouse5", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12" };
						ImGui::Checkbox("fake duck", &SETTINGS::settings.fakeduck);
						if (SETTINGS::settings.fakeduck)
						{
							ImGui::Combo(("fake duck key"), &SETTINGS::settings.fakeducsk, key_binds, ARRAYSIZE(key_binds));
						}
						ImGui::Checkbox(("auto-revolver"), &SETTINGS::settings.auto_revolver);
						ImGui::Checkbox(("resolver"), &SETTINGS::settings.resolve_bool);
						ImGui::Checkbox(("auto-scope"), &SETTINGS::settings.auto_scope);
						ImGui::Checkbox(("extrapolate"), &SETTINGS::settings.extrapolation);
						ImGui::Checkbox(("ignore limbs"), &SETTINGS::settings.IgnoreLimbs);
						ImGui::Checkbox(("ignore heads"), &SETTINGS::settings.ignoreheads);

					}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (page == 1)//antihit
					{
						
						const char* pitch[] = { " none", " emotion", " minimal", " up", "zero", "1080", "random" };
						const char* yaw[] = { " none", " backwards", " backjitter", " 180z", " keybased", "smart yaw", "offset" };

						ImGui::Columns(3, false);

						ImGui::Checkbox(("enable anti-aim"), &SETTINGS::settings.aa_bool);
						ImGui::Combo(("pitch"), &SETTINGS::settings.aa_pitch_type, pitch, ARRAYSIZE(pitch));
						ImGui::Combo("yaw", &SETTINGS::settings.aa_real_type, yaw, ARRAYSIZE(yaw));

						ImGui::Spacing();
						//b1g right?
						if (SETTINGS::settings.anti_untrusted)
						{
							ImGui::Text("omi#9046 on discord btw");
						}
						else
						{
							ImGui::Checkbox("nospread mode", &SETTINGS::settings.Beta_AA);
						}
						static bool fake = 0;
						ImGui::Spacing();
					


						ImGui::NextColumn();

						ImGui::Checkbox("enable fake angles", &SETTINGS::settings.omibool);
						if (SETTINGS::settings.omibool)
						{	
							
							ImGui::Checkbox("jitter desync", &SETTINGS::settings.desync_aa); //omi
							ImGui::Checkbox("tick-based desync anti-aim", &SETTINGS::settings.desync_aa2); //omi
							///////////////////////// top 2 are working, bottom 4 rnt
							ImGui::Checkbox(("switch desync"), &SETTINGS::settings.desync_aa3); //dutu
							ImGui::Checkbox(("balance desync"), &SETTINGS::settings.desync_aa4);//dutu
							ImGui::Checkbox(("tank desync"), &SETTINGS::settings.desync_aa5);//dutu
							ImGui::Checkbox(("roll desync"), &SETTINGS::settings.desync_aa6);//dutu
				
							if (SETTINGS::settings.desync_aa) //omi
							{
								ImGui::Text("If you want to increase it past the limit hold CTRL");
								ImGui::Text("and click on the slider. May cause bugs!");
								ImGui::SliderFloat("", &SETTINGS::settings.desync_range, 0, 58);
							}

							ImGui::Checkbox(("visualise"), &SETTINGS::settings.fakechams);
							ImGui::Checkbox(("indicator"), &SETTINGS::settings.desyncindicator);
						}

						ImGui::NextColumn();

						ImGui::Checkbox(("clamp angles (anti-ut)"), &SETTINGS::settings.anti_untrusted);
						ImGui::Checkbox(("disable thirdperson on nade"), &SETTINGS::settings.disable_tp_on_nade);

						if (SETTINGS::settings.aa_real_type == 4)
						{
							ImGui::Hotkey(("left"), &SETTINGS::settings.aa_left);
							ImGui::Hotkey(("right"), &SETTINGS::settings.aa_right);
							ImGui::Hotkey(("back"), &SETTINGS::settings.aa_back);
						}
						/////////////////////////this is broken idk y we keep it in the menu tbh
						const char* fakelag_mode[] = { "factor", "adaptive" };
						ImGui::Checkbox(("enable fakelag"), &SETTINGS::settings.lag_bool);
						ImGui::SliderFloat("fakelag", &SETTINGS::settings.fake_lag_choke, 1, 15);
						/////////////////////////this is broken idk y we keep it in the menu tbh
					}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (page == 2)//players
					{
						ImGui::Columns(2, false);

						ImGui::Checkbox(("enable player esp"), &SETTINGS::settings.esp_bool);
						ImGui::Checkbox(("box"), &SETTINGS::settings.box_bool);
						ImGui::Checkbox(("name"), &SETTINGS::settings.name_bool);
						ImGui::Checkbox(("weapon"), &SETTINGS::settings.weap_bool);
						ImGui::Checkbox(("health"), &SETTINGS::settings.health_bool);
						ImGui::Checkbox(("event logs"), &SETTINGS::settings.info_bool);
						ImGui::Checkbox(("ammo"), &SETTINGS::settings.ammo_bool);
						ImGui::Checkbox(("fov arrows"), &SETTINGS::settings.fov_bool); ImGui::SameLine();
						ImGui::ColorEdit4(("##fov_arrows"), SETTINGS::settings.arrows_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
						ImGui::Checkbox(("lag comp hitbox"), &SETTINGS::settings.lag_comp_hitbox);

						ImGui::NextColumn();

						const char* chams[] = { " none", " metallic", " invisible" };
						ImGui::Combo("chams", &SETTINGS::settings.chams_type, chams, IM_ARRAYSIZE(chams), 3);
						ImGui::SameLine();
						ImGui::ColorEdit4(("##chams1"), SETTINGS::settings.vmodel_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
						ImGui::Checkbox(("glow"), &SETTINGS::settings.glowenable);
						ImGui::SameLine();
						ImGui::ColorEdit4(("##glow"), SETTINGS::settings.glow_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

						ImGui::Checkbox(("bullet tracers"), &SETTINGS::settings.beam_bool);
						ImGui::SameLine();
						ImGui::ColorEdit4(("##tracer"), SETTINGS::settings.bulletlocal_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);
						ImGui::Checkbox(("bullet impact"), &SETTINGS::settings.bullet_impact);

					}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (page == 3)//esp
					{
						ImGui::Columns(3, false);

						ImGui::Checkbox(("thirdperson"), &SETTINGS::settings.tp_bool);
						ImGui::Spacing();
						if (SETTINGS::settings.tp_bool)
						{
							ImGui::Hotkey("##tp_key", &SETTINGS::settings.thirdperson_int);
						}

						ImGui::Checkbox(("fix sensitivity"), &SETTINGS::settings.fixscopesens);
						ImGui::Checkbox(("static crosshair"), &SETTINGS::settings.static_crosshair);
						ImGui::Checkbox(("force radgoll"), &SETTINGS::settings.force_ragdoll);
						ImGui::Checkbox(("nightmode"), &SETTINGS::settings.night_bool);
						ImGui::Checkbox(("fullbright"), &SETTINGS::settings.full_bright);
						ImGui::Checkbox(("damage indicator"), &SETTINGS::settings.dmg_bool);
						ImGui::Text("accent color"); ImGui::SameLine();
						ImGui::ColorEdit4(("##indicator"), SETTINGS::settings.invisible_col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar);

						ImGui::NextColumn();

						ImGui::Checkbox("styles hands", &SETTINGS::settings.wire_hand);
						ImGui::SameLine();
						ImGui::ColorEdit4(("###wire_colr"), SETTINGS::settings.wire_color_h, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
						ImGui::SliderFloat("render fov", &SETTINGS::settings.fov_val, 0, 179);
						ImGui::SliderFloat("viewmodel fov", &SETTINGS::settings.viewfov_val, 0, 179);
						const char* hit_sound[] = { "none", "metallic", "click", "fingers", "bame", "bubble", "lightsquare", "cod", "roblox", "keyboard", "fatality", "pew" };
						ImGui::Combo(("hitsound"), &SETTINGS::settings.hit_sound, hit_sound, ARRAYSIZE(hit_sound));

						ImGui::NextColumn();

						ImGui::Checkbox(("remove smoke"), &SETTINGS::settings.smoke_bool);
						ImGui::Checkbox(("remove flash"), &SETTINGS::settings.no_flash);
						ImGui::Checkbox(("remove scope"), &SETTINGS::settings.scope_bool);
						ImGui::Checkbox(("remove zoom"), &SETTINGS::settings.removescoping);
						ImGui::Checkbox("remove sky", &SETTINGS::settings.removesky);
						ImGui::Checkbox(("remove sleeves"), &SETTINGS::settings.misc_no_sleeves);
						ImGui::Checkbox("gravity ragdoll", &SETTINGS::settings.ragdol);
						ImGui::Checkbox(("enable postprocessing"), &SETTINGS::settings.matpostprocessenable);
						ImGui::Checkbox("preserve killfeed", &SETTINGS::settings.KillfeedBool);
					
						if (SETTINGS::settings.KillfeedBool)
						{
							SETTINGS::settings.PreserveKillfeed = 90;
						}
						else
						{
							SETTINGS::settings.PreserveKillfeed = 0;
						}

					}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (page == 4)//misc
					{
						ImGui::Columns(2, false);

						ImGui::Checkbox(("enable misc"), &SETTINGS::settings.misc_bool);
						ImGui::Checkbox(("clantag changer"), &SETTINGS::settings.misc_clantag);

						ImGui::NextColumn();

						ImGui::Checkbox(("bunnyhop"), &SETTINGS::settings.bhop_bool);
						ImGui::Checkbox(("auto-strafe"), &SETTINGS::settings.strafe_bool);
						ImGui::Checkbox(("z-hop"), &SETTINGS::settings.zbhob);
						ImGui::Checkbox(("directional bhop"), &SETTINGS::settings.wasd);
						ImGui::Checkbox(("duck in air"), &SETTINGS::settings.duck_bool);
					//	ImGui::Checkbox(("spectators"), &SETTINGS::settings.spectators);
			



					

				
					}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (page == 5)//skins
					{
						ImGui::Columns(3, false);

						getconfig();
						ImGui::Spacing();
						if (ImGui::Combo("cfg", &selectedcfg, [](void* data, int idx, const char** out_text)
							{
								*out_text = configs[idx].c_str();
								return true;
							}, nullptr, configs.size(), 10))
						{
							cfgname = configs[selectedcfg];
							cfgname.erase(cfgname.length() - 4, 4);
							strcpy(SETTINGS::settings.config_name, cfgname.c_str());
						}

							ImGui::Spacing();

							static bool create;
							if (ImGui::Button("save"))
							{
								Config->Save();
							}
							ImGui::SameLine();
							if (ImGui::Button("load"))
							{
								Config->Load();

							}
							if (ImGui::Button("reset settings", ImVec2(-1, 15))) Config->setup();


							ImGui::Text("new config");
							ImGui::Text("config name:");
							ImGui::InputText("name", SETTINGS::settings.config_name, 52);
							if (ImGui::Button("create & save", ImVec2(-1, 15)))
							{
								Config->Save();
								create = !create;
							}
						
					
						
						

					}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				ImGui::EndChild();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			ImGui::End();

		}	
		

		ImGui::Render();

		RestoreState(pDevice);

		return ofunc(pDevice);
	}

	long __stdcall Hooked_EndScene_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		static auto ofunc = directz.get_original<EndSceneResetFn>(16);

		if (!d3d_init)
			return ofunc(pDevice, pPresentationParameters);

		ImGui_ImplDX9_InvalidateDeviceObjects();

		auto hr = ofunc(pDevice, pPresentationParameters);

		ImGui_ImplDX9_CreateDeviceObjects();

		return hr;
	}

	typedef bool(__thiscall *FireEventClientSide)(void*, SDK::IGameEvent*);

	bool __fastcall Hooked_FireEventClientSide(void *ecx, void* edx, SDK::IGameEvent* pEvent) {

		static auto ofunct = fireevent.get_original<FireEventClientSide>(9);

		if (!pEvent)
			return ofunct(ecx, pEvent);

		return ofunct(ecx, pEvent);
	}




	void InitHooks()
	{
		iclient_hook_manager.Init(INTERFACES::Client);
		original_frame_stage_notify = reinterpret_cast<FrameStageNotifyFn>(iclient_hook_manager.HookFunction<FrameStageNotifyFn>(37, HookedFrameStageNotify));

		panel_hook_manager.Init(INTERFACES::Panel);
		original_paint_traverse = reinterpret_cast<PaintTraverseFn>(panel_hook_manager.HookFunction<PaintTraverseFn>(41, HookedPaintTraverse));

		model_render_hook_manager.Init(INTERFACES::ModelRender);
		original_draw_model_execute = reinterpret_cast<DrawModelExecuteFn>(model_render_hook_manager.HookFunction<DrawModelExecuteFn>(21, HookedDrawModelExecute));

		scene_end_hook_manager.Init(INTERFACES::RenderView);
		original_scene_end = reinterpret_cast<SceneEndFn>(scene_end_hook_manager.HookFunction<SceneEndFn>(9, HookedSceneEnd));

		trace_hook_manager.Init(INTERFACES::Trace);
		original_trace_ray = reinterpret_cast<TraceRayFn>(trace_hook_manager.HookFunction<TraceRayFn>(5, HookedTraceRay));

		override_view_hook_manager.Init(INTERFACES::ClientMode);
		original_override_view = reinterpret_cast<OverrideViewFn>(override_view_hook_manager.HookFunction<OverrideViewFn>(18, HookedOverrideView));
		original_create_move = reinterpret_cast<CreateMoveFn>(override_view_hook_manager.HookFunction<CreateMoveFn>(24, HookedCreateMove));
		original_viewmodel_fov = reinterpret_cast<GetViewmodelFOVFn>(override_view_hook_manager.HookFunction<GetViewmodelFOVFn>(35, GetViewmodelFOV));

		auto sv_cheats = INTERFACES::cvar->FindVar("sv_cheats");
		get_bool_manager = VMT::VMTHookManager(reinterpret_cast<DWORD**>(sv_cheats));
		original_get_bool = reinterpret_cast<SvCheatsGetBoolFn>(get_bool_manager.HookFunction<SvCheatsGetBoolFn>(13, HookedGetBool));

		fireevent.setup(INTERFACES::GameEventManager);
		fireevent.hook_index(9, Hooked_FireEventClientSide);


		while (!(INIT::Window = FindWindowA("Valve001", nullptr)))
			Sleep(100);
		if (INIT::Window)
			INIT::OldWindow = (WNDPROC)SetWindowLongPtr(INIT::Window, GWL_WNDPROC, (LONG_PTR)Hooked_WndProc);
		DWORD DeviceStructureAddress = **(DWORD**)(UTILS::FindSignature("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 1);
		if (DeviceStructureAddress) {
			directz.setup((DWORD**)DeviceStructureAddress);
			directz.hook_index(16, Hooked_EndScene_Reset);
			directz.hook_index(42, Hooked_EndScene);

		}
	}
	void EyeAnglesPitchHook(const SDK::CRecvProxyData *pData, void *pStruct, void *pOut)
	{
		*reinterpret_cast<float*>(pOut) = pData->m_Value.m_Float;

		auto entity = reinterpret_cast<SDK::CBaseEntity*>(pStruct);
		if (!entity)
			return;

	}
	void EyeAnglesYawHook(const SDK::CRecvProxyData *pData, void *pStruct, void *pOut)
	{
		*reinterpret_cast<float*>(pOut) = pData->m_Value.m_Float;

		auto entity = reinterpret_cast<SDK::CBaseEntity*>(pStruct);
		if (!entity)
			return;
	}
	void InitNetvarHooks()
	{
		UTILS::netvar_hook_manager.Hook("DT_CSPlayer", "m_angEyeAngles[0]", EyeAnglesPitchHook);
		UTILS::netvar_hook_manager.Hook("DT_CSPlayer", "m_angEyeAngles[1]", EyeAnglesYawHook);
	}
}