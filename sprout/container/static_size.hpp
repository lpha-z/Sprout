/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_STATIC_SIZE_HPP
#define SPROUT_CONTAINER_STATIC_SIZE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// static_size
		//
		template<typename Container>
		struct static_size
			: public std::integral_constant<
				typename sprout::container_traits<Container>::size_type,
				sprout::container_traits<Container>::static_size
			>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_STATIC_SIZE_HPP
