import cv, os, sys, ctypes
from PIL import Image
path = os.path.dirname(os.path.realpath(sys.argv[0]))

def identify(filepath, prep=False):
	imbit = []
	if filepath[-4:] == '.gif':
		im = Image.open(filepath)
		pal = im.getpalette()
		pal = map(lambda x: pal[3*x:3*x+3], range(0, len(pal)/3))
		w, h = im.size
		im = im.load()
		for j in range(0, w):
			imbit.append(0)
			for i in range(0, h):
				if sum(pal[im[j,i]]) > 384:
					imbit[j] |= 1 << i
	else:
		im = cv.LoadImage(filepath)
		w, h = im.width, im.height
		for j in range(0, im.width):
			imbit.append(0)
			for i in range(0, im.height):
				if cv.Get2D(im, i, j)[0] > 127:
					imbit[j] |= 1 << i
	carr = ctypes.c_int * w
	cimbit = carr(*imbit)
	res = 'aaaaa'
	dll = ctypes.CDLL(path + '/libpkucaptcha.so')
	dll.identify(h, w, cimbit, res, prep)
	res = res[: res.find('\0')]
	return res

if __name__ == '__main__':
	import sys
	print identify(sys.argv[1])
