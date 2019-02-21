class Qsort:
	#Lomuto partition scheme
	def lomuto(self, data, method = 'asc'):
		if len(data) < 2:
			return data
		else:
			pivot = 0
			for i in range(pivot + 1, len(data)):
				if data[i] <= data[pivot]:
					data.insert(pivot, data.pop(i))
					pivot = pivot + 1

			self.lomuto(data[0:pivot])
			return self.lomuto(data[pivot: len(data)])
		
qsort = Qsort()