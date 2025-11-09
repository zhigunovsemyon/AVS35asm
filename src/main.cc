#include "helper.h"
#include <cstdint>
#include <cstdio>

typedef float f32;
typedef double f64;
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;

static void sse_i32_sum()
{
	using type = i32;
	puts("Задание 1. i32 C = A + B");
	type a[4] = {8, -1, std::numeric_limits<type>::max(), 11};
	type b[4] = {0, 3, 4, 2};
	type c[4] = {};

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

static void sse_u16_sub()
{
	using type = u16;
	puts("Задание 2. u16 C = A - B");
	type a[8] = {0, 1, std::numeric_limits<type>::max(), 11, 256, 4, 99, 0};
	type b[8] = {1, 38, 4, 211, 0, 2, 19, std::numeric_limits<type>::max()};
	type c[8] = {};

	printf("a: ");
	print_array(std::span{a, 8});
	printf("b: ");
	print_array(std::span{b, 8});

	_asm {
		movdqu xmm0, a
		movdqu xmm1, b
		psubw xmm0, xmm1
		movdqu c, xmm0
	}

	printf("c: ");
	print_array(std::span{c, 8});
}

static void sse_i8_sum()
{
	using type = i8;
	puts("Задание 3. i8 C = A + B");
	type a[16] = {0, 1, std::numeric_limits<type>::max(), 11, -120, 4, 99, 1, 12, -77, 11, 12, -13, 14, -88};
	type b[16] = {1, 38, 4, 125, 0, 2, 19, std::numeric_limits<type>::min(), -99, 100, 111, -12, 26, -28, 66};
	type c[16] = {};

	printf("a: ");
	print_array(std::span{a, 16});
	printf("b: ");
	print_array(std::span{b, 16});

	_asm {
		movdqu xmm0, a
		movdqu xmm1, b
		paddb xmm0, xmm1
		movdqu c, xmm0
	}

	printf("c: ");
	print_array(std::span{c, 16});
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

static void sse_f64_div()
{
	using type = f64;
	puts("Задание 5. f64 C = A / B");
	type a[2] = {3.5f, 1.0f};
	type b[2] = {0.5f, -5.1f};
	type c[2] = {0.0f, 0.0f};

	printf("a: ");
	print_array(std::span{a, 2});
	printf("b: ");
	print_array(std::span{b, 2});

	_asm {
		movupd xmm0, a
		movupd xmm1, b
		divpd xmm0, xmm1
		movupd c, xmm0
	}

	printf("c: ");
	print_array(std::span{c, 2});
}

int main()
{
	sse_i32_sum();
	std::println();
	
	sse_u16_sub();
	std::println();

	sse_i8_sum();
	std::println();

	sse_f32_mult();
	std::println();

	sse_f64_div();

	puts("Нажмите любую кнопку для завершения");
	(void)getchar();
	return 0;
}
