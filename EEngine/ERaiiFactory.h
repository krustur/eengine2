#pragma once

#include <vector>

namespace EEngine
{
	template <typename T>
	class ERaiiFactory
	{
	public:
		ERaiiFactory() {}
		~ERaiiFactory()
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
		ERaiiFactory(const ERaiiFactory&);
		ERaiiFactory& operator= (const ERaiiFactory&);
	};
}