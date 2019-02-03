# This program is an implementation of peak finding algorithm
# recommended by the free course on Data Structures and
# Algorithms published by MIT (2011). This program implements
# both 1d and 2d peak finding in a single code.
#
# Author: Viorel Rinja
# contact: viorel.rinja@gmail.com

# Import time tracking functionality
import time

# Import custom implemented functions of peak finding
from peak_1d import peak_1d
from peak_2d import peak_2d

# This function takes a function as a value and a single parameter
def run_with_metrics(find_peak, *data):
  start_time = time.time()
  print(find_peak(*data))
  print('Executed in ' + str(time.time() - start_time) + 'seconds.')


# Open the reding file
f = open('input', 'r')
data = f.read().split()

if (type(data.pop()) is list):
  # In case of 2d list
  data = f.read().splitlines()
  data = list(map(lambda x: list(map(int, x.split())), data))

  run_with_metrics(peak_2d, data)
else:
  # In case of 1d list
  data = list(map(int, data))

  run_with_metrics(peak_1d, data)
  
