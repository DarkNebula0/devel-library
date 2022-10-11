#pragma once
#include <vector>

namespace Devel::VectorUtils {
	template<typename T>
	bool IsDataInVector(const std::vector<T>& i_atVector, const T& i_tData, size_t* i_pOutIndex = nullptr)
	{
		for (size_t i = 0, nSize = i_atVector.size(); i < nSize; i++)
		{
			if (i_atVector[i] == i_tData)
			{
				if (i_pOutIndex)
				{
					*i_pOutIndex = i;
				}

				return true;
			}
		}

		return false;
	}
}