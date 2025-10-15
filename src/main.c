#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static void i32_overflow(int32_t a)
{
	int32_t b = a, c = 0;
	int32_t x = a, y = b, z = 0;
	printf("a = %d\n", a);
	
	// сложение в C
	c = a + b;
	printf("a+b = %d\n", c);

	//сложение asm
	__asm {
		mov eax, x // eax=x
		add eax, y // eax+=y
		mov z, eax // z=eax
		
		jo OVRF    //jo -> jumps if overflow   
	}
	
	//ok
	printf("x+y = %d\n", z);
	return;

	OVRF:	
	puts("i32 OVERFLOW");

	return;
}

static void i8_overflow(int8_t a)
{
	int8_t b = a, c = 0;
	int8_t x = a, y = b, z = 0;
	printf("a = %hhd\n", a);

	c = a + b;
	printf("a+b = %hhd\n", c);

	// сложение asm
	__asm {
		mov al, x // al=x
		add al, y // al+=y
		mov z, al // z=al
		
		jo OVRF // jo -> jumps if overflow
	}

	// ok
	printf("x+y = %hhd\n", z);
	return;

OVRF:
	puts("i8 OVERFLOW");

	return;
}

static void i16_overflow(int16_t a) 
{
	int16_t b = a, c = 0;
	int16_t x = a, y = b, z = 0;
	printf("a = %hd\n", a);
	
	c = a + b;
	printf("a+b = %hd\n", c);

	// сложение asm
	__asm {
		mov ax, x // ax=x
		add ax, y // ax+=y
		mov z, ax // z=ax
		
		jo OVRF // jo -> jumps if overflow
	}

	// ok
	printf("x+y = %hd\n", z);
	return;

OVRF:
	puts("i16 OVERFLOW");

	return;
}

static void sqeq(float a, float b, float c)
{
	float const _4 = 4.0, _0 = 0.0, _2 = 2.0, _neg1 = -1.0;
	float sqd, x1, x2;

	printf("Для a = %.3f; b = %.3f, c = %.3f:\n", a, b, c);

	__asm {
		fld b
		fmul b //b^2

		fld a
		fmul c
		fmul _4 //4ac

		fsub //b^2-4ac
		
		fcom _0
		jl NEG_D

		fsqrt
		fstp sqd // получили корень дискриминанта

		fld _2
		fmul a
		fstp a

		fld sqd // -b + sqrt(d) или же sqrt(d) - b
		fld b
		fsub
		fdiv a
		fstp x1

		fld sqd // -b - sqrt(d) или же -(sqrt(d) + b)
		fld b
		fadd
		fmul _neg1
		fdiv a
		fstp x2
	}
	
	printf("sqrt(d) = %.3f, ", sqd);
	printf("x1 = %.3f, x2 = %.3f", x1, x2);
	return;

	NEG_D:
	printf("Нет корней\n");
	return;
}

int main()
{
	i32_overflow(2'000'000'000);
	puts("");
	i32_overflow(2'000'000);
	getchar();

	i16_overflow(20'000);
	puts("");
	i16_overflow(2'000);
	getchar();

	i8_overflow(120);
	puts("");
	i8_overflow(2);
	getchar();

	sqeq(2,5,2);
	getchar();

	return 0;
}
