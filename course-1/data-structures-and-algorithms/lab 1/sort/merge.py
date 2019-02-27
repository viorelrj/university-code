def classical(self, data, method = 'asc'):
	if len(data) > 1:
		mid = len(data) // 2
		left = self.classical(data[0:mid])
		right = self.classical(data[mid: len(data)])
		del data[:]
		while len(left) > 0 or len(right) > 0:
			if len(left) == 0:
				data.append(right.pop(0))
			elif len(right) == 0:
				data.append(left.pop(0))
			else:
				if left[0] <= right[0]:
					data.append(left.pop(0))
				else:
					data.append(right.pop(0))
		return data
	else:
		return data

