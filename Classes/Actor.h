#pragma once

namespace mygame
{
	class Actor
	{
	public:
		Actor() {}

		virtual bool init();
		virtual void update();

		//Access
		bool isActive() const;
		void setActive(const bool value);
	private:
		//Data
		bool active = false;

		//Helper functions
		void addToWorld();
	};
}