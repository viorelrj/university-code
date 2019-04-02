from sort import bubble
from sort import heap
from sort import insertion
from sort import merge
from sort import qsort
from sort import radix
from sort import selection
from sort import shell
import random
import time

data = []
for i in range(0, 1000000):
	data.append(random.randint(0, 32000))

def metrics(function, *args):
	start = time.time()
	function(*args)
	print("executed in ", time.time() - start)

metrics(lambda x: x.sort(), data)