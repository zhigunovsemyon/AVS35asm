#include <concepts>
#include <print>
#include <cstdio>
#include <span>
#include <iostream>
#include <cstdint>

typedef float f32;
typedef double f64;
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;

template <std::floating_point T> void print_array(std::span<T> A)
{
	for (auto n : A)
		std::print("{:7.2f} ", n);
	std::cout << std::endl;
}

template <std::integral T> void print_array(std::span<T> A)
{
	for (auto n : A)
		std::print("{:4} ", n);
	std::cout << std::endl;
}

static void sse_f32_mult()
{
	f32 a[4] = {3.5f, 1.1f, 10.0f, -10.0f};
	f32 b[4] = {0.5f, -5.1f, -0.1f, 12.3f};
	f32 c[4] = {0.0f, 0.0f, 0.0f, 0.0f};

	printf("a: ");
	print_array(std::span{a, 4});
	printf("b: ");
	print_array(std::span{b, 4});

	_asm {
		movups xmm0, a
		movups xmm1, b
		mulps xmm0, xmm1
		movups c, xmm0
	}

	printf("c: ");
	print_array(std::span{c, 4});
}

int main()
{
	sse_f32_mult();
	getchar();
	return 0;
}
