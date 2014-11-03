#pragma once
#include "Base/IncludesEngine.h"

namespace glowy2d
{
	class Action
	{
	public:
		Action(std::function<void()> actionFunction) : action(actionFunction) {}

		~Action() {}

		void activate() const;

	private:
		std::function<void()> action;
	};
}