#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include <memory>
#include <vector>
#include "Hittable.hpp"

using std::make_shared;
using std::shared_ptr;

namespace MyRT {
	class HittableList {
		public:
			std::vector<shared_ptr<Hittable>> objects;

			HittableList();
			
	};
}

#endif // !HITTABLE_LIST
