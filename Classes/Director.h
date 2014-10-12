#pragma once
#include "World.h"


namespace mygame
{
	class Director
	{
	public:
		static Director * getInstance();
		bool init();

		World * getWorld() const;

		//Scheduled updates
		void update_16ms();
		void update_128ms();
		void update_512ms();
		void update_1024ms();
		void update_8172ms();
		void update_65536ms();

	private:
		Director();
		~Director();
		static bool singletonInitialised;
		static Director singletonInstance;

		World * world;
	};
}