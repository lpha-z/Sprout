/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_COORDS_VECTOR_HPP
#define SPROUT_DARKROOM_COORDS_VECTOR_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/darkroom/access/access.hpp>

namespace sprout {
	namespace darkroom {
		namespace coords {
			//
			// x
			// y
			// z
			//
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			x(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			y(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			z(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<2>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<2>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<2>(sprout::forward<T>(t));
			}

			//
			// vector3d_t
			// vector3d
			//
			typedef sprout::tuples::tuple<double, double, double> vector3d_t;

			inline SPROUT_CONSTEXPR sprout::darkroom::coords::vector3d_t
			vector3d(double x = 0, double y = 0, double z = 0) {
				return sprout::darkroom::coords::vector3d_t(x, y, z);
			}

			//
			// length_sq
			//
			template<typename Vector>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Vector>::type
			length_sq(Vector const& vec) {
				return sprout::darkroom::coords::x(vec) * sprout::darkroom::coords::x(vec)
					+ sprout::darkroom::coords::y(vec) * sprout::darkroom::coords::y(vec)
					+ sprout::darkroom::coords::z(vec) * sprout::darkroom::coords::z(vec)
					;
			}
			//
			// length
			//
			template<typename Vector>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Vector>::type
			length(Vector const& vec) {
				return sprout::sqrt(sprout::darkroom::coords::length_sq(vec));
			}
			//
			// add
			//
			template<typename Vector1, typename Vector2>
			inline SPROUT_CONSTEXPR Vector1
			add(Vector1 const& lhs, Vector2 const& rhs) {
				return sprout::tuples::remake<Vector1>(
					lhs,
					sprout::darkroom::coords::x(lhs) + sprout::darkroom::coords::x(rhs),
					sprout::darkroom::coords::y(lhs) + sprout::darkroom::coords::y(rhs),
					sprout::darkroom::coords::z(lhs) + sprout::darkroom::coords::z(rhs)
					);
			}
			//
			// sub
			//
			template<typename Vector1, typename Vector2>
			inline SPROUT_CONSTEXPR Vector1
			sub(Vector1 const& lhs, Vector2 const& rhs) {
				return sprout::tuples::remake<Vector1>(
					lhs,
					sprout::darkroom::coords::x(lhs) - sprout::darkroom::coords::x(rhs),
					sprout::darkroom::coords::y(lhs) - sprout::darkroom::coords::y(rhs),
					sprout::darkroom::coords::z(lhs) - sprout::darkroom::coords::z(rhs)
					);
			}
			//
			// scale
			//
			template<typename Vector, typename Fac>
			inline SPROUT_CONSTEXPR Vector
			scale(Vector const& lhs, Fac const& rhs) {
				return sprout::tuples::remake<Vector>(
					lhs,
					sprout::darkroom::coords::x(lhs) * rhs,
					sprout::darkroom::coords::y(lhs) * rhs,
					sprout::darkroom::coords::z(lhs) * rhs
					);
			}
			//
			// negate
			//
			template<typename Vector>
			inline SPROUT_CONSTEXPR Vector
			negate(Vector const& vec) {
				return sprout::tuples::remake<Vector>(
					vec,
					-sprout::darkroom::coords::x(vec),
					-sprout::darkroom::coords::y(vec),
					-sprout::darkroom::coords::z(vec)
					);
			}
			//
			// dot
			//
			template<typename Vector>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Vector>::type
			dot(Vector const& lhs, Vector const& rhs) {
				return sprout::darkroom::coords::x(lhs) * sprout::darkroom::coords::x(rhs)
					+ sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::y(rhs)
					+ sprout::darkroom::coords::z(lhs) * sprout::darkroom::coords::z(rhs)
					;
			}
			//
			// cross
			//
			template<typename Vector1, typename Vector2>
			inline SPROUT_CONSTEXPR Vector1
			cross(Vector1 const& lhs, Vector2 const& rhs) {
				return sprout::tuples::remake<Vector1>(
					lhs,
					sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::z(rhs)
						- sprout::darkroom::coords::z(lhs) * sprout::darkroom::coords::y(rhs)
						,
					sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::x(rhs)
						- sprout::darkroom::coords::x(lhs) * sprout::darkroom::coords::y(rhs)
						,
					sprout::darkroom::coords::x(lhs) * sprout::darkroom::coords::y(rhs)
						- sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::x(rhs)
					);
			}
			//
			// normalize
			//
			namespace detail {
				template<typename Vector>
				inline SPROUT_CONSTEXPR Vector
				normalize_impl(Vector const& vec, typename sprout::darkroom::access::unit<Vector>::type const& len) {
					return sprout::tuples::remake<Vector>(
						vec,
						sprout::darkroom::coords::x(vec) / len,
						sprout::darkroom::coords::y(vec) / len,
						sprout::darkroom::coords::z(vec) / len
						);
				}
			}	// namespace detail
			template<typename Vector>
			inline SPROUT_CONSTEXPR Vector
			normalize(Vector const& vec) {
				return sprout::darkroom::coords::detail::normalize_impl(
					vec,
					sprout::darkroom::coords::length(vec)
					);
			}
			//
			// resize
			//
			template<typename Vector, typename Fac>
			inline SPROUT_CONSTEXPR Vector
			resize(Vector const& lhs, Fac const& rhs) {
				return sprout::darkroom::coords::detail::normalize_impl(
					lhs,
					sprout::darkroom::coords::length(lhs) / rhs
					);
			}
			//
			// reflect
			//
			template<typename Incident, typename Normal>
			inline SPROUT_CONSTEXPR Incident
			reflect(Incident const& incid, Normal const& nor) {
				return sprout::darkroom::coords::sub(
					incid,
					sprout::darkroom::coords::scale(nor, sprout::darkroom::coords::dot(incid, nor) * 2)
					);
			}
		}	// namespace coords
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_COORDS_VECTOR_HPP
