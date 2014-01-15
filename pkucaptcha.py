import cv, os, sys, ctypes
path = os.path.dirname(os.path.realpath(sys.argv[0]))

def identify(filepath):
	im = cv.LoadImage(filepath)
	imbit = []
	for j in range(0, im.width):
		imbit.append(0)
		for i in range(0, im.height):
			if cv.Get2D(im, i, j)[0] > 127:
				imbit[j] |= 1 << i
	carr = ctypes.c_int * im.width
	cimbit = carr(*imbit)
	res = 'aaaaa'
	dll = ctypes.CDLL(path + '/libpkucaptcha.so')
	dll.identify(im.height, im.width, cimbit, res)
	res = res[: res.find('\0')]
	return res

if __name__ == '__main__':
	import sys
	print identify(sys.argv[1])
