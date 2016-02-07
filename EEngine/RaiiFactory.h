#pragma once

#include <vector>

namespace EEngine
{
	template <typename T>
	class RaiiFactory
	{
	public:
		RaiiFactory() {}
		~RaiiFactory()
		{
			while (!container.empty())
			{
				const T* p = container.back();
				container.pop_back();
				delete p;
			}
		}

		//T* Create(T* p)
		//{
		//	container.push_back(p);
		//	return p;
		//}

		T& Create(T* p)
		{
			container.push_back(p);
			return *p;
		}
	private:
		std::vector<const T*> container;

		// non-copyable
		RaiiFactory(const RaiiFactory&);
		RaiiFactory& operator= (const RaiiFactory&);
	};
}