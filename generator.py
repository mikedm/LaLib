#!/usr/bin/env python

## @file generator.py
## @package generator
## @author Michael Meloney
## @date June 26, 2019
## @brief This program will generate accurate matrix operations using numpy to be utilized against the LaLib TestRunner to prove correctness.
##
## Options:\n
##       -t [count=1] [minValue=0] [maxValue=10] [minSize=1] [maxSize=10]  Transpose\n
##       -m [count=1] [minValue=0] [maxValue=10] [minSize=1] [maxSize=10]  Multiply\n\n
##
## Sample Usage:\n
##
## Generate 1000 matrix products from random matricies with element values in range [50,50] and matrix size [1,20]\n
## ./generator.py -m 1000 -50 50 1 20 > product.test\n\n
##
## Generate 1000 matrix transpose operations from random matricies with element values in range [50,50] and matrix size [1,20]\n
## ./generator.py -t 1000 -50 50 1 20 > transpose.test

import numpy.matlib
import numpy as np
import os
import random
import sys
import traceback

## Default value for how many to generate
DEFAULT_COUNT = 1

## Default value for matrix element minimum random number
DEFAULT_MIN_VALUE = 0

## Default value for matrix element maximum random number
DEFAULT_MAX_VALUE = 10

## Default value for matrix size minimum random number
DEFAULT_MIN_SIZE = 1

## Default value for matrix size maximum random number
DEFAULT_MAX_SIZE = 10

## Print given matrix to stdout, optionally include the size of the matrix on the first line
def matrixPrint(matrix, includeSize):
    if includeSize:
        print ' '.join(map(str, matrix.shape))
    # Use the os line serperator to easily view the matrix rows/cols
    print os.linesep.join(' '.join(str(cell) for cell in row) for row in matrix)
    sys.stdout.flush()

## Return a random number between given low and high
def rand(low, high):
    return random.randint(low, high)

## Utilize numpy to generate random matrix with given seed values
def getRandomMatrix(minValue, maxValue, x, y):
    return np.random.randint(minValue, maxValue, size=(x,y))

## Generate [count] transpose matricies with given seed values
def generateTrans(count, minValue, maxValue, minSize, maxSize):
    for i in range(count):
        a = getRandomMatrix(minValue, maxValue, rand(minSize, maxSize), rand(minSize, maxSize))
        trans = np.transpose(a) # Call into numpy to calculate expected result
        matrixPrint(a, True)
        matrixPrint(trans, False) # No need to print size because we know it to be inverse of input matrix

## Generate [count] product matricies with given seed values
def generateMultiply(count, minValue, maxValue, minSize, maxSize):
    for i in range(count):
        a = getRandomMatrix(minValue, maxValue, rand(minSize, maxSize), rand(minSize, maxSize))
        b = getRandomMatrix(minValue, maxValue, a.shape[1], rand(minSize, maxSize))
        product = np.dot(a, b) # Call into numpy to calculate expected product
        matrixPrint(a, True)
        matrixPrint(b, True)
        matrixPrint(product, False) # No need to print size because we know it to be c1xr2 (cols of matrix a x rows of matrix b)

## Print help to user
def printHelp():
    print "Hello Brain!"
    print "This program will generate accurate matrix operations to be"
    print "utilized against the LaLib TestRunner to prove correctness"
    print "Options:"
    print "   -t [count=%s] [minValue=%s] [maxValue=%s] [minSize=%s] [maxSize=%s]  Transpose" % (
        DEFAULT_COUNT, DEFAULT_MIN_VALUE, DEFAULT_MAX_VALUE, DEFAULT_MIN_SIZE, DEFAULT_MAX_SIZE)
    print "   -m [count=%s] [minValue=%s] [maxValue=%s] [minSize=%s] [maxSize=%s]  Multiply" % (
        DEFAULT_COUNT, DEFAULT_MIN_VALUE, DEFAULT_MAX_VALUE, DEFAULT_MIN_SIZE, DEFAULT_MAX_SIZE)
    sys.stdout.flush()

if __name__ == '__main__': 
    try:
        ## Get count from user
        count = DEFAULT_COUNT
        if len(sys.argv) >= 3:
            count = int(sys.argv[2])

        ## Get min value of matrix element from user
        minValue = DEFAULT_MIN_VALUE
        if len(sys.argv) >= 4:
            minValue = int(sys.argv[3])

        ## Get max value of matrix element from user
        maxValue = DEFAULT_MAX_VALUE
        if len(sys.argv) >= 5:
            maxValue = int(sys.argv[4])

        ## Get min value of matrix size
        minSize = DEFAULT_MIN_SIZE
        if len(sys.argv) >= 6:
            minSize= int(sys.argv[5])

        ## Get max value of matrix size
        maxSize = DEFAULT_MAX_SIZE
        if len(sys.argv) >= 7:
            maxSize= int(sys.argv[6])

        if len(sys.argv) < 2:
            printHelp()
        elif "-t" == sys.argv[1]:
            generateTrans(count, minValue, maxValue, minSize, maxSize)
        elif "-m" == sys.argv[1]:
            generateMultiply(count, minValue, maxValue, minSize, maxSize)
        else:
            printHelp()
    except KeyboardInterrupt:
        pass
    except Exception, e:
        print str(e)
        # traceback.print_exc() # View full stack trace
