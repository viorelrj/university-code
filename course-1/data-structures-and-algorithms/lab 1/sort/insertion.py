def classical(data, method = 'asc'):
	if method == 'asc':
		def compare(a, b):
			return a > b
	else:
		def compare(a, b):
			return a < b

	for item in range(1, len(data)):
		index = item
		while (index > 0 and compare(data[index - 1], data[item])):
			index = index - 1
		data.insert(index, data.pop(item))
	return data

def recursive(data, method = 'asc'):
	if method == 'asc':
		def compare(a, b):
			return a > b
	else:
		def compare(a, b):
			return a < b

	def _exec(data, n):
		if n > 1:
			_exec(data, n - 1)
			n -= 1
			index = n
			while index > 0 and compare(data[index - 1], data[n]):
				index -= 1
			data.insert(index, data.pop(n))
			return data
	return _exec(data, len(data))


def binary( data, method = 'asc'):
	if method == 'asc':
		for item in range (1, len(data)):
			index = item

			while index > 0 and not (data[index - 1] < data[index] and data[index] < data[index + 1]):

				if data[index] < data[index - 1]:
					data.insert(index // 2, data.pop(index))
					index = index // 2
				else:
					index += 1
	else:
		for item in range(1, len(data) - 1):
			index = item

			while index > 0 and not (data[index - 1] > data[index] and data[index] > data[index + 1]):

				if data[index] > data[index - 1]:
					data.insert(index // 2, data.pop(index))
					index = index // 2
				else:
					index += 1

	return data
