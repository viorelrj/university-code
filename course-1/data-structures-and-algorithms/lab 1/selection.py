def selection (data, method = 'asc'):
	func = min if method == 'asc' else max
	for i in range(0, len(data)):
		max_index = data.index(func(list(data[i: len(data)])))
		data[i], data[max_index] = data[max_index], data[i]
	
	return data
