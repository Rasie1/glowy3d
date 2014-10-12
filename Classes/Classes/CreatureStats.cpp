#include "CreatureStats.h"

CreatureStats::CreatureStats() : stats(STATS_NUMBER)
{
	
}

void CreatureStats::initDefault(CreatureStats& stats)
{
	stats.stats[LEVEL] = 1;
	stats.stats[CURRENT_EXPERIENCE] = 0;
	stats.stats[MAX_EXPERIENCE] = 100;
	stats.stats[K_EXPERIENCE] = 1;
	stats.stats[COLLISION_RADIUS] = 128;
}