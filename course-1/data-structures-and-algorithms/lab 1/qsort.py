import time as time
class Qsort:
	# Nico Lomuto's partition scheme
	def lomuto(self, data, lo, hi):
		if hi - lo > 1:
			hi -= 1
			pivot = data[hi]
			wall = 0
			for i in range(lo, hi):
				if data[i] <= pivot:
					data.insert(lo, data.pop(i))
					wall += 1
			data.insert(wall, data.pop(hi))
			self.lomuto(data, lo, wall)
			self.lomuto(data, wall, hi)
		return data
	
	# C.A.R Hoare's partition scheme
	def hoare(self, data, lo, hi):
		pivot = data[int((lo + hi) / 2)]
		i = lo - 1
		j = hi
		while True:
			while True:
				i += 1
				if data[i] >= pivot:
					break
			while True:
				j -= 1
				if data[j] <= pivot:
					break
			if i >= j :
				break
			data[i], data[j] = data[j], data[i]
		return data
		
qsort = Qsort()
