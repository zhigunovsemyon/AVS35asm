#include <concepts>
#include <cstdint>
#include <cstdio>

template <std::floating_point T> void print_array(T const * A, int n)
{
	if (!n) {
		putchar('\n');
		return;
	}

	printf("%lf ", *A);
	print_array(A + 1, n - 1);
}

int main()
{
	float a[4] = {3.5f, 1.1f, 10.0f, -10.0f};
	float b[4] = {0.5f, -5.1f, -0.1f, 12.3f};
	float c[4] = {0.0f, 0.0f, 0.0f, 0.0f};

	printf("a: ");
	print_array(a, sizeof(a) / sizeof(*a));
	printf("b: ");
	print_array(b, sizeof(b) / sizeof(*b));

	_asm {
		movups xmm0, a
		movups xmm1, b
		mulps xmm0, xmm1
		movups c, xmm0
	}

	printf("c: ");
	print_array(c, sizeof(c) / sizeof(*c));

	getchar();
	return 0;
}
