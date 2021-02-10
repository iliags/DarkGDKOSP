#pragma once

namespace PointerConverter
{
	/**
	 * @return a reference from @a intPtr of the generic type.
	 */
	template<typename T1>
	T1 & GetRefFromInt(__int64 intPtr)
	{
		return *(T1*)intPtr;
	}

	/**
	 * @return a pointer from @a intPtr of the generic type.
	 */
	template<typename T2>
	T2 * GetPtrFromInt(__int64 intPtr)
	{
		return (T2*)intPtr;
	}
}