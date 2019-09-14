#include <cstdio>
#include <cmath>
#include <limits>

float esquare(float f, unsigned m, int iter) {
	float v = f;
    unsigned x = *((unsigned*)&v);
	x = m + (x>>1);
	v = *(float*)&x;
    for (int i = 0; i < iter; i++) {
        v = (v + f / v) / 2;
    }
	return v;
}
void loss_ratio(
        double n, int m1, int m2, int iter,
        double max=std::numeric_limits<float>::max()) {
    double l1 = 0, l2 = 0, s = max / n;
    for (double f = 1; f <= max; f += s) {
        double s1 = esquare(f, m1, iter);
        double s2 = esquare(f, m2, iter);
        double s = sqrt(f);
        l1 += fabs(s1 - s) / s / n;
        l2 += fabs(s2 - s) / s / n;
    }
    printf("Percent error l1, l2, ratio with %d Newton iterations: %f%% %f%% %f\n", 
           iter, l1*100, l2*100, l1/l2);
}
int main() {
    unsigned m1 = 0x1FBFCBDC;
    unsigned m2 = 0x1FBD5F78;
    loss_ratio(1e+8, m1, m2, 0);
    loss_ratio(1e+8, m1, m2, 1);
    return 0;
}