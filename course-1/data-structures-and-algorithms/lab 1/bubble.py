class bubblesort:
	def flag (self, data, method = 'asc'):
		changed = True
		while (changed):
			changed = False
			for i in range(0, len(data) - 1):
				if (method == 'asc'):
					if data[i] > data[i + 1]:
						data[i], data[i+1] = data[i + 1], data[i]
						changed = True
				elif (method == 'desc'):
					if (data[i] < data[i + 1]):
						data[i], data[i+1] = data[i + 1], data[i]
						changed = True
		
		return data


	def two_for(self, data, method='asc'):
		for k in range(0, len(data)):
			for i in range(0, len(data) - 1):
				if (method == 'asc'):
					if data[i] > data[i + 1]:
						data[i], data[i+1] = data[i + 1], data[i]
				elif (method == 'desc'):
					if (data[i] < data[i + 1]):
						data[i], data[i+1] = data[i + 1], data[i]

		return data


	def two_for_o(self, data, method='asc'):
		for k in range(0, len(data)):
			for i in range(0, len(data) - k - 1):
				if (method == 'asc'):
					if data[i] > data[i + 1]:
						data[i], data[i+1] = data[i + 1], data[i]
				elif (method == 'desc'):
					if (data[i] < data[i + 1]):
						data[i], data[i+1] = data[i + 1], data[i]

		return data

bubble = bubblesort()
