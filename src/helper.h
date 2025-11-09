#pragma once
#include <concepts>
#include <print>
#include <span>

template <std::integral T> consteval uint16_t int_count_space()
{
	uint16_t ret = 0;
	auto val = std::numeric_limits<T>::max();

	while (val) {
		val /= 10;
		ret++;
	}
	return ret + ((std::numeric_limits<T>::min() < 0) ? 1 : 0);
}

template <std::floating_point T> void print_array(std::span<T> A)
{
	for (auto n : A)
		std::print("{:7.2f} ", n);
	std::println();
}

template <std::integral T> void print_array(std::span<T> A)
{
	for (auto n : A)
		std::print("{:{}} ", n, int_count_space<T>() + 1);
	std::println();
}
