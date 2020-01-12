#pragma once
#include <cstddef>
class Utils {
public:
	static const std::size_t CalculateOffset(const std::size_t baseAddress, const std::size_t alignment) {
		const std::size_t multiplier = (baseAddress / alignment) + 1;
		const std::size_t alignedAddress = multiplier * alignment;
		const std::size_t offset = alignedAddress - baseAddress;
		return offset;
	}

	static const std::size_t CalculateOffsetWithHeader(const std::size_t baseAddress, const std::size_t alignment, const std::size_t headerSize) {
		std::size_t offset = CalculateOffset(baseAddress, alignment);
		std::size_t neededSpace = headerSize;

		if (neededSpace > offset) {
			neededSpace -= offset;
   
			offset += neededSpace % alignment > 0 ?
				alignment * (1 + (neededSpace / alignment)) :
				alignment * (neededSpace / alignment)
		}
		return offset;
	}
};