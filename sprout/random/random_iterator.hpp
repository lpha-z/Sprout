#ifndef SPROUT_RANDOM_RANDOM_ITERATOR_HPP
#define SPROUT_RANDOM_RANDOM_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/random/random_result.hpp>

namespace sprout {
	namespace random {
		//
		// random_iterator
		//
		template<typename Engine, typename Distribution = void, typename Enable = void>
		class random_iterator;

		template<typename Engine, typename Distribution>
		class random_iterator<
			Engine,
			Distribution,
			typename std::enable_if<!std::is_same<Distribution, void>::value>::type
		>
			: public std::iterator<
				typename std::iterator_traits<sprout::random::random_result<Engine, Distribution> >::iterator_category,
				typename std::iterator_traits<sprout::random::random_result<Engine, Distribution> >::value_type,
				typename std::iterator_traits<sprout::random::random_result<Engine, Distribution> >::difference_type,
				typename std::iterator_traits<sprout::random::random_result<Engine, Distribution> >::pointer,
				typename std::iterator_traits<sprout::random::random_result<Engine, Distribution> >::reference
			>
		{
		public:
			typedef sprout::random::random_result<Engine, Distribution> random_result_type;
			typedef typename random_result_type::engine_type engine_type;
			typedef typename random_result_type::distribution_type distribution_type;
			typedef typename random_result_type::result_type result_type;
			typedef typename std::iterator_traits<random_result_type>::iterator_category iterator_category;
			typedef typename std::iterator_traits<random_result_type>::value_type value_type;
			typedef typename std::iterator_traits<random_result_type>::difference_type difference_type;
			typedef typename std::iterator_traits<random_result_type>::pointer pointer;
			typedef typename std::iterator_traits<random_result_type>::reference reference;
		private:
			random_result_type random_;
			difference_type count_;
		public:
			SPROUT_CONSTEXPR random_iterator()
				: random_()
				, count_()
			{}
			SPROUT_CONSTEXPR random_iterator(
				engine_type const& engine,
				distribution_type const& distribution,
				difference_type count = -1
				)
				: random_(distribution(engine))
				, count_(count)
			{}
			SPROUT_CONSTEXPR explicit random_iterator(
				random_result_type const& random,
				difference_type count = -1
				)
				: random_(random)
				, count_(count)
			{}
			SPROUT_CONSTEXPR random_iterator operator()() const {
				return count_ != 0
					? random_iterator(random_(), count_ > 0 ? count_ - 1 : count_)
					: throw "assert(count_ != 0)"
					;
			}
			random_result_type& random_result() {
				return random_;
			}
			SPROUT_CONSTEXPR random_result_type const& random_result() const {
				return random_;
			}
			result_type& result() {
				return random_.result();
			}
			SPROUT_CONSTEXPR result_type const& result() const {
				return random_.result();
			}
			engine_type& engine() {
				return random_.engine();
			}
			SPROUT_CONSTEXPR engine_type const& engine() const {
				return random_.engine();
			}
			distribution_type& distribution() {
				return random_.distribution();
			}
			SPROUT_CONSTEXPR distribution_type const& distribution() const {
				return random_.distribution();
			}
			SPROUT_CONSTEXPR result_type min() const {
				return random_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return random_.max();
			}
			SPROUT_CONSTEXPR result_type count() const {
				return count_;
			}
			void swap(random_iterator& other) {
				using std::swap;
				swap(random_, other.random_);
				swap(count_, other.count_);
			}
			friend SPROUT_CONSTEXPR bool operator==(random_iterator const& lhs, random_iterator const& rhs) {
				return lhs.count_ == rhs.count_ && (lhs.count_ == 0 || lhs.random_ == rhs.random_);
			}
			friend SPROUT_CONSTEXPR bool operator!=(random_iterator const& lhs, random_iterator const& rhs) {
				return !(lhs == rhs);
			}
			SPROUT_CONSTEXPR reference operator*() const {
				return count_ != 0
					? random_.result()
					: throw "assert(count_ != 0)"
					;
			}
			SPROUT_CONSTEXPR pointer operator->() const {
				return count_ > 0
					? &random_.result()
					: throw "assert(count_ != 0)"
					;
			}
			random_iterator& operator++() {
				random_iterator temp((*this)());
				temp.swap(*this);
				return *this;
			}
			random_iterator operator++(int) {
				random_iterator result(*this);
				++*this;
				return result;
			}
		};
		template<typename Engine, typename Distribution>
		class random_iterator<
			Engine,
			Distribution,
			typename std::enable_if<std::is_same<Distribution, void>::value>::type
		>
			: public std::iterator<
				typename std::iterator_traits<sprout::random::random_result<Engine> >::iterator_category,
				typename std::iterator_traits<sprout::random::random_result<Engine> >::value_type,
				typename std::iterator_traits<sprout::random::random_result<Engine> >::difference_type,
				typename std::iterator_traits<sprout::random::random_result<Engine> >::pointer,
				typename std::iterator_traits<sprout::random::random_result<Engine> >::reference
			>
		{
		public:
			typedef sprout::random::random_result<Engine> random_result_type;
			typedef typename random_result_type::engine_type engine_type;
			typedef typename random_result_type::result_type result_type;
			typedef typename std::iterator_traits<random_result_type>::iterator_category iterator_category;
			typedef typename std::iterator_traits<random_result_type>::value_type value_type;
			typedef typename std::iterator_traits<random_result_type>::difference_type difference_type;
			typedef typename std::iterator_traits<random_result_type>::pointer pointer;
			typedef typename std::iterator_traits<random_result_type>::reference reference;
		private:
			random_result_type random_;
			difference_type count_;
		public:
			SPROUT_CONSTEXPR random_iterator()
				: random_()
				, count_()
			{}
			SPROUT_CONSTEXPR random_iterator(
				engine_type const& engine,
				difference_type count = -1
				)
				: random_(engine())
				, count_(count)
			{}
			SPROUT_CONSTEXPR explicit random_iterator(
				random_result_type const& random,
				difference_type count = -1
				)
				: random_(random)
				, count_(count)
			{}
			SPROUT_CONSTEXPR random_iterator operator()() const {
				return count_ != 0
					? random_iterator(random_(), count_ > 0 ? count_ - 1 : count_)
					: throw "assert(count_ != 0)"
					;
			}
			random_result_type& random_result() {
				return random_;
			}
			SPROUT_CONSTEXPR random_result_type const& random_result() const {
				return random_;
			}
			result_type& result() {
				return random_.result();
			}
			SPROUT_CONSTEXPR result_type const& result() const {
				return random_.result();
			}
			engine_type& engine() {
				return random_.engine();
			}
			SPROUT_CONSTEXPR engine_type const& engine() const {
				return random_.engine();
			}
			SPROUT_CONSTEXPR result_type min() const {
				return random_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return random_.max();
			}
			SPROUT_CONSTEXPR result_type count() const {
				return count_;
			}
			void swap(random_iterator& other) {
				using std::swap;
				swap(random_, other.random_);
				swap(count_, other.count_);
			}
			friend SPROUT_CONSTEXPR bool operator==(random_iterator const& lhs, random_iterator const& rhs) {
				return lhs.count_ == rhs.count_ && (lhs.count_ == 0 || lhs.random_ == rhs.random_);
			}
			friend SPROUT_CONSTEXPR bool operator!=(random_iterator const& lhs, random_iterator const& rhs) {
				return !(lhs == rhs);
			}
			SPROUT_CONSTEXPR reference operator*() const {
				return count_ != 0
					? random_.result()
					: throw "assert(count_ != 0)"
					;
			}
			SPROUT_CONSTEXPR pointer operator->() const {
				return count_ > 0
					? &random_.result()
					: throw "assert(count_ != 0)"
					;
			}
			random_iterator& operator++() {
				random_iterator temp((*this)());
				temp.swap(*this);
				return *this;
			}
			random_iterator operator++(int) {
				random_iterator result(*this);
				++*this;
				return result;
			}
		};
		//
		// swap
		//
		template<typename Engine, typename Distribution>
		void swap(
			sprout::random::random_iterator<Engine, Distribution>& lhs,
			sprout::random::random_iterator<Engine, Distribution>& rhs
			)
		{
			lhs.swap(rhs);
		}

		//
		// next
		//
		template<typename Engine, typename Distribution>
		SPROUT_CONSTEXPR sprout::random::random_iterator<Engine, Distribution> next(
			sprout::random::random_iterator<Engine, Distribution> const& it
			)
		{
			return it();
		}
	}	// namespace random

	using sprout::random::random_iterator;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_RANDOM_ITERATOR_HPP
