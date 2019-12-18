#ifndef ZIP_H_
#define ZIP_H_

#include <type_traits>
#include <iterator>
#include <utility>
#include <concepts>

template <typename IterI, typename IterII>
struct zip_iterator
{
protected:
	using vtypeI = typename std::iterator_traits<IterI>::value_type;
	using vtypeII = typename std::iterator_traits<IterII>::value_type;
public:
	using self = zip_iterator<IterI, IterII>;
	using value_type = std::pair<vtypeI, vtypeII>;
	using reference = value_type&;

	zip_iterator(IterI beginI, IterII beginII)
		:iter(std::make_pair(beginI, beginII))
	{

	}

	reference operator*() noexcept
	{
		return iter;
	}

	self& operator++() noexcept
	{
		++iter.first;
		++iter.second;
		return *this;
	}

	self operator++(int) noexcept
	{
		auto temp = *this;
		++* this;
		return temp;
	}

	bool operator==(const self& x) const noexcept
	{
		return iter.first == (x.iter.first)
			|| iter.second == x.iter.second;
	}

	bool operator!=(const self& x) const noexcept
	{
		return iter.first != (x.iter.first)
			&& iter.second != x.iter.second;
	}
private:
	std::pair<IterI, IterII> iter;
};


template <typename IterI, typename IterII>
struct const_zip_iterator
{
protected:
	using vtypeI = typename std::iterator_traits<IterI>::value_type;
	using vtypeII = typename std::iterator_traits<IterII>::value_type;
public:
	using self = zip_iterator<IterI, IterII>;
	using value_type = std::pair<vtypeI, vtypeII>;
	using reference = value_type const&;

	const_zip_iterator(IterI beginI, IterII beginII)
		:iter(std::make_pair(beginI, beginII))
	{

	}

	reference operator*() const noexcept
	{
		return iter;
	}

	self& operator++() noexcept
	{
		++iter.first;
		++iter.second;
		return *this;
	}

	self operator++(int) noexcept
	{
		auto temp = *this;
		++* this;
		return temp;
	}

	bool operator==(const self& x) const noexcept
	{
		return iter.first == (x.iter.first)
			|| iter.second == x.iter.second;
	}

	bool operator!=(const self& x) const noexcept
	{
		return iter.first != (x.iter.first)
			&& iter.second != x.iter.second;
	}
private:
	std::pair<IterI, IterII> iter;
};

template <typename Cont>
concept has_iterator_mem = requires { typename Cont::iterator; };

template <typename ContI, typename ContII>
struct zip
{
	static_assert(has_iterator_mem<ContI>&& has_iterator_mem<ContII>, "");
protected:
	using iterI = typename ContI::iterator;
	using iterII = typename ContII::iterator;
	using citerI = typename ContI::const_iterator;
	using citerII = typename ContII::const_iterator;

public:
	using iterator = zip_iterator<iterI, iterII>;
	using const_iterator = const_zip_iterator<citerI, citerII>;

	zip(ContI& first, ContII& second)
		:first_(first), second_(second)
	{ }

	iterator begin() noexcept
	{
		return iterator(std::begin(first_), std::begin(second_));
	}

	const_iterator begin() const noexcept
	{
		return const_iterator(std::cbegin(first_), std::cend(second_));
	}

	iterator end() noexcept
	{
		return iterator(std::end(first_), std::end(second_));
	}

	const_iterator end() const noexcept
	{
		return const_iterator(std::cend(first_), std::cend(second_));
	}

	const_iterator cbegin() const noexcept
	{
		return const_iterator(std::cbegin(first_), std::cend(second_));
	}

	const_iterator cend() const noexcept
	{
		return const_iterator(std::cend(first_), std::cend(second_));
	}
private:
	ContI& first_;
	ContII& second_;
};

#endif /* ZIP_H_ */
