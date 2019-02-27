def shell(data, method = 'asc'): 
	if method == 'asc':
		def compare(a, b):
			return a > b
	else:
		def compare(a, b):
			return a < b
	n = len(data) 
	gap = n//2
	while gap > 0: 
		for i in range(gap,n): 
			temp = data[i] 
			j = i 
			while j >= gap and compare(data[j-gap], temp):
				data[j] = data[j-gap] 
				j -= gap 
			data[j] = temp 
		gap //= 2
	return data
