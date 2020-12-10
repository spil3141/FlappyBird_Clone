#pragma once


#include <random>

namespace Tiny {

	class Random
	{
	public:
		static void Init()
		{
			s_RandomEngine.seed(std::random_device()());
		}

		static float Float()
		{
			return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
		}

		// Summary -> IntRange has a max range number of 1000
		static int IntRange(uint32_t from,uint32_t to) // "to" is exclusive
		{
			T_ASSERT(to < 1000, "IntRange Max Range exceeded!");
			return ((int)(((float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max()) * 1000)) % to;
		}
	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
	};
}
