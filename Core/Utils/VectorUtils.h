#pragma once
#include <vector>

/// @namespace Devel::VectorUtils
/// @brief This namespace includes utilities for working with vectors.
///
/// <b>Example</b>
///
/// @code{.cpp}
///     std::vector<int> vec = {1, 2, 3, 4, 5};
///     int data = 3;
///     size_t index = 0;
///
///     // Check if the data is in the vector
///     bool isInVector = Devel::VectorUtils::IsDataInVector(vec, data, &index);
///
///     // If the data is in the vector, print its index
///     if (isInVector) {
///         std::cout << "Data found at index: " << index << std::endl;
///     } else {
///         std::cout << "Data not found in vector" << std::endl;
///     }
/// @endcode
namespace Devel::VectorUtils {
    /// @brief This function checks if a given data is present in the vector.
    ///
    /// It iterates through the input vector and compares each element with the input data.
    /// If it finds a match, it sets the index of the matching element to the out index (if provided) and returns true.
    ///
    /// @param [in] i_atVector The input vector.
    /// @param [in] i_tData The data to search for in the vector.
    /// @param [out] i_pOutIndex Pointer to an index variable where the index of the found element will be stored. If this parameter is not provided, the function simply checks if the data exists in the vector.
    /// @return Returns true if the data is found in the vector, false otherwise.
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