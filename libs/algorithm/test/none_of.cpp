#ifndef SPROUT_LIBS_ALGORITHM_TEST_NONE_OF_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_NONE_OF_CPP

#include <sprout/algorithm/none_of.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_none_of_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::none_of(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::greater_than<int>(5)
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::none_of(
					sprout::begin(arr1),
					sprout::end(arr1),
					testspr::greater_than<int>(10)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::none_of(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::greater_than<int>(5)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::none_of(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					testspr::greater_than<int>(10)
					);
				TESTSPR_BOTH_ASSERT(result);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_none_of_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_NONE_OF_CPP
