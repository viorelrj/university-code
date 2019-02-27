from sort import shell
import random
import time

data = []
for i in range(0, 100):
	data.append(random.randint(0, 32000))

def metrics(function, *args):
	start = time.time()
	print(function(*args))
	print("executed in ", time.time() - start)


metrics(shell.shell, data, 'desc')
