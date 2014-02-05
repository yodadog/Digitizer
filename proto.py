#!/usr/bin/env python

import numpy as np
import itertools as it

np.set_printoptions(linewidth=9001)

IMG_COUNT = 28000
num_imgs = 5
data = np.genfromtxt('training_data/test.csv', delimiter=',',
                        skip_header=1, skip_footer=IMG_COUNT-1-num_imgs)

chunk_size = 28
for img in data:
    for i in xrange(0, len(img), chunk_size):
        for n in img[i:i+chunk_size]:
            if n != 0:
                if n > 240:
                    print '@',
                else:
                    print '0',
            else:
                print ' ',
        print
