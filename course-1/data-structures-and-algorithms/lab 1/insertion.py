class insertion_sort:
	def classical(self, data, method = 'asc'):
		if method == 'asc':
			for item in range(1, len(data)):
				index = item
				while (index > 0 and data[item] < data[index - 1]):
					index = index - 1
				data.insert(index, data.pop(item))
			return data
		elif method == 'desc':
			for item in range(1, len(data)):
				index = item
				while (index > 0 and data[item] > data[index - 1]):
					index = index - 1
				data.insert(index, data.pop(item))
			return data

	def binary(self, data, method = 'asc'):
		if method == 'asc':
			for item in range (1, len(data)):

				index = item
			
				data.insert(index, data.pop(item))

			return data


insertion = insertion_sort()
