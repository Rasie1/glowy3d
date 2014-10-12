#ifndef __CREATURE_STATS_H__
#define __CREATURE_STATS_H__

#include "cocos2d.h"

USING_NS_CC;

struct CreatureStats
{
	/*
	DMG damage
	ATK attack
	DEF defense
	RES resistance
	CH chance
	D dependance
	*/
	enum RawStats
	{
		LEVEL,
		CURRENT_EXPERIENCE,
		MAX_EXPERIENCE,
		K_EXPERIENCE,

		CURRENT_HP,
		MAX_HP,
		CURRENT_MP,
		HP_REGEN,
		MAX_MP,
		MP_REGEN,

		PIERCE_DMG_BASE,
		PIERCE_DMG_K,
		PIERCE_RES,
		BLUNT_DMG_BASE,
		BLUNT_DMG_K,
		BLUNT_RES,

		D_STR, //hp, regen
		D_AGI, //physical and magical dmg (illogical name)
		D_INT, //mp, regen
		//suggested names: POWER, ENERGY, VITALITY (POW, ENE, VIT)
		//or ANGER, ENDURANCE, THOUGHT (ANG, END, THO)

		DELAY_ATTACK_BEFORE,
		DELAY_ATTACK_AFTER,
		MOVESPEED,

		COLLISION_RADIUS,
		SIGHT_RANGE,
		SIGHT_ANGLE,
		ATTACK_RANGE,
		ATTACK_ANGLE,
		SKILL_RADIUS,

		D_BLOCK_CHANCE,
		D_BLOCK_ABILITY,
		D_EVASION_CHANCE,
		D_EVASION_ABILITY,
		D_CRITICAL_CHANCE,
		D_CRITICAL_ABILITY,
		D_MAGIC_DMG,
		D_MAGIC_RES,

		D_FIRE_DMG,
		D_FIRE_RES,
		FIRE_ATK,
		FIRE_DEF,
		FIRE_TIME_DMG,
		FIRE_TIME_DMG_DEF,
		FIRE_TIME_DUR,
		FIRE_TIME_DUR_DEF,

		D_COLD_DMG,
		D_COLD_RES,
		COLD_ATK,
		COLD_DEF,
		COLD_TIME_DMG,
		COLD_TIME_DMG_DEF,
		COLD_TIME_DUR,
		COLD_TIME_DUR_DEF,

		D_LIGHTNING_DMG,
		D_LIGHTNING_RES,
		LIGHTNING_ATK,
		LIGHTNING_DEF,
		LIGHTNING_TIME_DMG,
		LIGHTNING_TIME_DMG_DEF,
		LIGHTNING_TIME_DUR,
		LIGHTNING_TIME_DUR_DEF,

		D_POISON_DMG,
		D_POISON_RES,
		POISON_ATK,
		POISON_DEF,
		POISON_TIME_DMG,
		POISON_TIME_DMG_DEF,
		POISON_TIME_DUR,
		POISON_TIME_DUR_DEF,

		D_HEAL_EFF,
		D_HEAL_RES,
		HEAL_ATK,
		HEAL_DEF,
		HEAL_TIME_EFF,
		HEAL_TIME_EFF_SELF,
		HEAL_TIME_DUR,
		HEAL_TIME_DUR_SELF,

		STUN_DUR,
		STUN_DUR_SELF,

		CURSE_DUR,
		CURSE_DUR_SELF,
		CURSE_EFF,
		CURSE_EFF_SELF,

		BLESS_DUR,
		BLESS_DUR_SELF,
		BLESS_EFF,
		BLESS_EFF_SELF,

		D_LUCK,
		MAGIC_FIND,
		SKILL_FIND,
		GOLD_FIND,

		STATS_NUMBER,
	};

	std::vector<float> stats;
	CreatureStats();

	static void initDefault(CreatureStats& stats);
};

#endif