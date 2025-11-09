#include <concepts>
#include <cstdint>
#include <cstdio>
#include <print>
#include <span>

typedef float f32;
typedef double f64;
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;

template <std::floating_point T> void print_array(std::span<T> A)
{
	for (auto n : A)
		std::print("{:7.2f} ", n);
	std::println();
}

template <std::integral T> void print_array(std::span<T> A)
{
	for (auto n : A)
		std::print("{:11} ", n);
	std::println();
}

static void sse_i32_sum()
{
	puts("Задание 1. i32 C = A + B");
	i32 a[4] = {8, -1, std::numeric_limits<i32>::max(), 11};
	i32 b[4] = {0, 3, 4, 2};
	i32 c[4] = {};

	printf("a: ");
	print_array(std::span{a, 4});
	printf("b: ");
	print_array(std::span{b, 4});

	_asm {
		movdqu xmm0, a
		movdqu xmm1, b
		paddd xmm0, xmm1
		movdqu c, xmm0
	}

	printf("c: ");
	print_array(std::span{c, 4});
}

static void sse_f32_mult()
{
	puts("Задание 4. f32 C = A * B");
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
	sse_i32_sum();
	std::println();
	sse_f32_mult();

	puts("Нажмите любую кнопку для завершения");
	(void)getchar();
	return 0;
}
