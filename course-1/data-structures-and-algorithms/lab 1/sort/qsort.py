import random

# Nico Lomuto's partition scheme
def lomuto(data, method = 'asc', partition='last'):
	if method == 'asc':
		def compare(a, b):
			return a < b
	else:
		def compare(a, b):
			return a > b

	def _partition_last(data, lo, hi):
		pivot = data[hi]

		wall = lo - 1
		for j in range(lo, hi):
			if compare(data[j], pivot):
				wall += 1
				data[wall], data[j] = data[j], data[wall]
		data[wall + 1], data[hi] = data[hi], data[wall + 1]
		return wall + 1
	
	def _partition_rand(data, lo, hi):
		pivot = random.randint(lo, hi)
		data[pivot], data[hi] = data[hi], data[pivot]
		pivot = data[hi]

		wall = lo - 1
		for j in range(lo, hi):
			if compare(data[j], pivot):
				wall += 1
				data[wall], data[j] = data[j], data[wall]
		data[wall + 1], data[hi] = data[hi], data[wall + 1]
		return wall + 1
	
	def _partition_med(data, lo, hi):
		pivot = [data[lo], data[(lo + hi) // 2], data[hi]]
		pivot.remove(max(pivot))
		pivot.remove(min(pivot))
		pivot = data.index(pivot.pop())
		data[hi], data[pivot] = data[pivot], data[hi]
		pivot = data[hi]

		wall = lo - 1
		for j in range(lo, hi):
			if compare(data[j], pivot):
				wall += 1
				data[wall], data[j] = data[j], data[wall]
		data[wall + 1], data[hi] = data[hi], data[wall + 1]
		return wall + 1
	
	def _partition_first(data, lo, hi):
		pivot = data[lo]
		wall = hi + 1
		for j in range(hi, lo, -1):
			if not compare(data[j], pivot):
				wall -= 1
				data[wall], data[j] = data[j], data[wall]
		data[wall - 1], data[lo] = data[lo], data[wall - 1]
		return wall - 1
	
	partitions = {
		'first': _partition_first,
		'last': _partition_last,
		'rand': _partition_rand,
		'med': _partition_med
	}
	
	def _quicksort(data, lo, hi):
		if lo < hi:
			p = partitions[partition](data, lo, hi)
			_quicksort(data, lo, p - 1)
			_quicksort(data, p + 1, hi)
		return data
		
	return _quicksort(data, 0, len(data) - 1)

# C.A.R Hoare's partition scheme
def hoare(data, method = 'asc'):
	if method == 'asc':
		def compare(a, b):
			return a <= b
	else:
		def compare(a, b):
			return a >= b

	def _partition(data, start, end):
		i, j = start, end - 1

		while True:
			while compare(data[i], data[end]) and i < j:
				i += 1

			while compare(data[end], data[j]) and i < j:
				j -= 1

			if i == j:
				if compare(data[i], data[end]):
					i += 1

				data[i], data[end] = data[end], data[i]
				return i
			else:
				data[i], data[j] = data[j], data[i]

	def _quicksort(data, lo, hi):
		if lo < hi:
			p = _partition(data, lo, hi)
			_quicksort(data, lo, p - 1)
			_quicksort(data, p + 1, hi)
		return data

	return _quicksort(data, 0, len(data) - 1)

