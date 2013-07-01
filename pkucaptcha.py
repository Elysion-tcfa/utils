import cv, math, zlib, base64
data = 'eJztWstu2zAQ/BXffNGBTNGkza1N2wR9BEEfSVsjX1Lk3xMKNsx9zO6SlmIBDSAU6M6KXM7MUqKcf+tX6/PVZpOHVaLXUyTfD6tNEki5tkim1w7JUWQ71RYBFUikukeO1lZBhuuhK8UVaFU/QeuTHmLzRMRGKedhjuzDBCFhTkXmiBKOmEtDCrGvR2Kbbw0U0oMQXV1pF+3Ys25iG4vHVER9mXVfYseSGyJebnY5QAqxp7utgOikrMzTDPDY6l4OagXpYnMQew9bFoNyKUkBzb5Sjf224h+0rDk6Wi6muIGLxuUm3S1my5mg8JkJcnqgfWv/vwH80wFMdTH/MTBVoNlzUZCNeTxDONUW/t/R/UeSQhcdSyG+my1Fqgc0kiM2pOid5njf86gwo4oH7FGlFDUv8NPEtINmJDKBbsFKEljdcUFQrblOjyHAbeH/PXhNEkUJWXQbxhFzHo0WUFvMnNiTAEkcwRyI2gqxH5f5Ym8Wj+k7vIJwbd6J6QMm1h3aKipAgSvSwnGz/oA5BH+A/yLTpbmx76aBO9dgb++Z45IJ7yk1Ky583InX/Hg44A/zX2T6hLoJiAwWPXFY+MQMz1kJDRfGrirGJu7PyXFsjBh+7Po78SLTFyyTaaB9BL9i6DgfqwkPtANfbPz+WH3e+gL8BPhlMn0Gpzn07ewlTGOUaOIV4J+R9m9025cC7SdwbIi3lSkTpX1JfOZEDhIXz55ItJ4qUZd79MZX4wH3/KeDJSP8ck4u1w1vDnpbWJ3Thuv2b8JbrNuP16buxLOP1/6/mfaTSNtnB4+otg8Sy+mZQuwP7UdkzCqgtONVPuuUcPcM6MGLfno2woHmpFMKTgpj3w0reoaErADq5bI78WDDmNLD+j2cpzzLS+wv+6xhzvH/gYpXlB7QelJxycj/T+Nbq9V7iRege2hA+8ILHsaLTHegTZS2twxlpsu5kenAD12p+tdLT1U6D/alq1nKfcdIh4sAx1IUmTm9OO3WfNMWdkEpwCIBF3na8v9OnYLcNkeKKksopUj1J3QoUhn2FDDp94j17O2R4TGxXJxfo0y/FyRTQIZDZTpofLP+g/gx+S8y/Z3/rx6FXKZQnoQmeSFE4SRyQm1g5/7hEXWpL4s='
chars = '2356789ABCDEFGHJKLMNPRSTUVWXYZ'
charims = eval(zlib.decompress(base64.decodestring(data)))
def identify(filepath):
	im = cv.LoadImage(filepath)
	imarr = []
	for i in range(0, im.height):
		imarr.append([])
		for j in range(0, im.width):
			imarr[i].append(0 if cv.Get2D(im, i, j)[0] < 127 else 1)
	s = ''
	for i in range(0, im.height):
		for j in range(0, im.width):
			if imarr[i][j] == 0:
				black = 0.0
				cnt = 0
				for k in range(-3, 3):
					for l in range(-3, 3):
						if (k != 0 or l != 0) and i + k >= 0 and i + k < im.height and j + l >= 0 and j + l < im.width:
							cnt += 1.0 / math.exp(math.sqrt(k * k + l * l))
							if imarr[i + k][j + l] == 0:
								black += 1.0 / math.exp(math.sqrt(k * k + l * l))
				if black < cnt * 0.2: cv.Set2D(im, i, j, (255, 255, 255, 0))
	for i in range(0, im.width):
		for j in range(0, im.height):
			chlist = []
			for ch in chars:
				nowerror = 0
				h = len(charims[ch])
				w = len(charims[ch][0])
				error = h * w * 0.1
				for k in range(0, h):
					for l in range(0, w):
						if j + k >= im.height or i + l >= im.width:
							if charims[ch][k][l] == 0:
								nowerror += 0.4
						elif imarr[j + k][i + l] != charims[ch][k][l]:
							nowerror += 1
						if nowerror > error: break
					if nowerror > error: break
				if nowerror <= error:
					chlist.append((nowerror, ch))
			if chlist == []: continue
			chlist.sort()
			ch = chlist[0][1]
			h = len(charims[ch])
			w = len(charims[ch][0])
			for k in range(0, h):
				for l in range(0, w):
					if j + k < im.height and i + l < im.width and charims[ch][k][l] == 0:
						imarr[j + k][i + l] = 1
			s += ch
	return s

if __name__ == '__main__':
	import sys
	print identify(sys.argv[1])
