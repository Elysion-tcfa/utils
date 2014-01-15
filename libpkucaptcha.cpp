#include <cstring>
#include <cmath>
#include <algorithm>

const char *char_sym = "23456789ABCDEFGHJKLMNPRSTUVWXYZabcdefghjkmnpqrsuvwxyz";
const int char_imbit[60][20] = {{1017, 508, 1276, 1660, 1852, 1948, 1985, 2019}, {5113, 1948, 1948, 1948, 1948, 780, 4129, 6257}, {7423, 7231, 7183, 7367, 7409, 0, 0, 7423, 7423}, {4992, 1920, 1948, 1948, 1948, 828, 4156, 6268}, {7183, 4099, 4913, 1948, 1948, 1948, 796, 4153, 6271}, {8188, 2044, 508, 6268, 7964, 8140, 8160, 8184}, {6399, 4193, 768, 1932, 1948, 1820, 768, 4209, 6399}, {8131, 4993, 1816, 1852, 1852, 1852, 4505, 6145, 7687}, {2047, 255, 6175, 7171, 7360, 7420, 7392, 7171, 6175, 255, 2047}, {0, 0, 1948, 1948, 1932, 800, 4209, 6399}, {7175, 6147, 4593, 1016, 2044, 2044, 2044, 2044, 5113}, {0, 0, 2044, 2044, 2044, 2044, 1016, 4593, 6147, 7175}, {0, 0, 1948, 1948, 1948, 1948, 1948, 2044}, {0, 0, 7996, 7996, 7996, 7996, 8188}, {7183, 7171, 4337, 1016, 2044, 2044, 2044, 2044, 124, 4217}, {0, 0, 8095, 8095, 8095, 8095, 8095, 8095, 0, 0}, {16383, 16383, 16383, 8191, 32768, 49152, 65535}, {0, 0, 8127, 7967, 7751, 7395, 6649, 5116, 2046, 4095}, {0, 0, 2047, 2047, 2047, 2047, 2047, 2047}, {0, 0, 8176, 8065, 7183, 4223, 5119, 4223, 7183, 8065, 8176, 0, 0}, {0, 0, 8177, 8131, 8079, 7743, 6271, 4607, 0, 0}, {0, 0, 7996, 7996, 7996, 8088, 8065, 8131}, {0, 0, 7996, 7996, 7740, 7192, 6529, 5059, 2047, 4095}, {5089, 1984, 1948, 1948, 1852, 4153, 6271}, {8188, 8188, 8188, 8188, 0, 0, 8188, 8188, 8188, 8188}, {6144, 4096, 1023, 2047, 2047, 2047, 1023, 4096, 6144}, {4094, 4080, 3971, 3087, 127, 1023, 127, 3087, 3971, 4080, 4094}, {8188, 8128, 7171, 63, 1023, 15, 7680, 8184, 7168, 15, 1023, 63, 7171, 8128, 8188}, {4094, 1016, 4593, 7239, 7695, 7695, 7239, 4593, 1016, 4094}, {8190, 8184, 8161, 8135, 4127, 4127, 8135, 8161, 8184, 8190}, {1020, 508, 1148, 1596, 1932, 1988, 2032, 2040}, {575, 25, 204, 204, 588, 512, 1, 255}, {0, 0, 5071, 2023, 2023, 967, 4111, 6175}, {771, 513, 120, 252, 252, 252, 633}, {6175, 4111, 967, 2023, 2023, 5071, 0, 0}, {771, 513, 72, 204, 204, 193, 579}, {8167, 1, 0, 8164, 8164, 8188}, {16131, 9728, 3192, 3324, 3324, 1657, 8192, 12288}, {0, 0, 8159, 8175, 8167, 8167, 7, 15}, {32767, 32767, 32767, 4, 65540}, {0, 0, 8063, 7743, 7327, 6607, 5095, 2039, 4095}, {0, 0, 1019, 1021, 1020, 1020, 0, 1, 1019, 1021, 1020, 1020, 0, 1}, {0, 0, 1019, 1021, 1020, 1020, 0, 1}, {0, 0, 15993, 15612, 15612, 15480, 15873, 16131}, {16131, 15873, 15480, 15612, 15484, 15993, 0, 0}, {0, 0, 1017, 1020, 1020}, {625, 224, 196, 204, 28, 569}, {512, 0, 255, 255, 767, 895, 0, 0}, {1020, 992, 771, 31, 255, 31, 771, 992, 1020}, {1016, 768, 7, 255, 7, 896, 1020, 896, 7, 255, 7, 768, 1016}, {510, 120, 529, 903, 775, 545, 120, 510}, {16380, 16352, 3971, 31, 12543, 15391, 16259, 16352, 16380}, {124, 60, 156, 204, 228, 240, 248}};
const int char_h[60] = {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 16, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 13, 13, 13, 13, 10, 13, 10, 13, 10, 13, 14, 13, 17, 13, 10, 10, 14, 14, 10, 10, 10, 10, 10, 10, 14, 10};
const int char_w[60] = {8, 8, 9, 8, 9, 8, 9, 9, 11, 8, 9, 10, 8, 7, 10, 10, 7, 10, 8, 13, 10, 8, 10, 7, 10, 9, 11, 15, 10, 10, 8, 8, 8, 7, 8, 7, 6, 8, 8, 5, 9, 14, 8, 8, 8, 5, 6, 8, 9, 13, 8, 9, 7};

struct recog_t {
	int x; char ch;
};
bool operator < (recog_t a, recog_t b) {
	return a.x < b.x;
}

extern "C" void identify(int h, int w, int *imbit, char *res);
void identify(int h, int w, int *imbit, char *res) {
	int num = strlen(char_sym);
	for (int j = 0; j < w; j++)
		for (int i = 0; i < h; i++)
			if (!(imbit[j] & 1<<i)) {
				double black = 0, cnt = 0;
				for (int k = -3; k <= 3; k++)
					for (int l = -3; l <= 3; l++)
						if ((k != 0 || l != 0) && i+k >= 0 && i+k < h && j+l >= 0 && j+l < w) {
							cnt += 1 / exp(sqrt(k*k+l*l));
							if (!(imbit[j+l] & 1<<i+k))
								black += 1 / exp(sqrt(k*k+l*l));
						}
				if (black < cnt * 0.2)
					imbit[j] |= 1<<i;
			}
	double *pool = new double[h*w*num];
	double (*f)[w][num] = (double (*)[w][num]) pool;
	recog_t recog[4];
	int lasti, lastj, lasth, lastw;
	int turns = 0;
	for (; turns < 4; turns++) {
		double valmax = -100;
		int maxi, maxj, maxk = -1;
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				for (int k = 0; k < num; k++) {
					int chh = char_h[k], chw = char_w[k];
					int tot = chh * chw;
					if (i+chh > h) chh = h-i;
					if (j+chw > w) chw = w-j;
					if (chh*chw < tot * 0.6) continue;
					double val;
					if (turns == 0 || i+chh > lasti && i < lasti+lasth && j+chw > lastj && j < lastj+lastw) {
						val = 0;
						for (int l = 0; l < chw; l++) {
							int bit = imbit[j+l] >> i & ((1<<chh)-1);
							int chbit = char_imbit[k][l];
							val -= 3.0 * __builtin_popcount(bit & ~chbit);
							val += 1.0 * __builtin_popcount(~(bit | chbit) & (1<<chh)-1);
							val -= 0.5 * __builtin_popcount(~bit & chbit);
						}
						f[i][j][k] = val;
					} else
						val = f[i][j][k];
					if (val > valmax) {
						valmax = val;
						maxi = i, maxj = j, maxk = k;
					}
				}
		if (maxk == -1) break;
		recog[turns].x = maxj, recog[turns].ch = char_sym[maxk];
		int i = maxi, j = maxj, k = maxk, chh = char_h[k], chw = char_w[k];
		if (i+chh > h) chh = h-i;
		if (j+chw > w) chw = w-j;
		for (int l = 0; l < chw; l++)
			imbit[j+l] |= (~char_imbit[k][l] & (1<<chh)-1) << i;
		lasti = i, lastj = j, lasth = chh, lastw = chw;
	}
	std::sort(recog, recog + turns);
	for (int i = 0; i < turns; i++)
		res[i] = recog[i].ch;
	res[turns] = 0;
	delete [] pool;
}
