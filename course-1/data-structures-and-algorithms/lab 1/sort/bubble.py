# Use flag for when array is sorted
def flag (data, method = 'asc'):
	if method == 'asc':
		def compare(a, b):
			return a > b
	else:
		def compare(a, b):
			return a < b

	changed = True
	while (changed):
		changed = False
		for i in range(0, len(data) - 1):
			if compare(data[i], data[i + 1]):
				data[i], data[i+1] = data[i + 1], data[i]
				changed = True
	
	return data

# Basic for implementation
def two_for(data, method='asc'):
	if method == 'asc':
		def compare(a, b):
			return a > b
	else:
		def compare(a, b):
			return a < b

	for k in range(0, len(data)):
		for i in range(0, len(data) - 1):
			if compare(data[i], data[i + 1]):
				data[i], data[i+1] = data[i + 1], data[i]

	return data

# Optimized for implementation (don't double check)
def two_for_o(data, method='asc'):
	if method == 'asc':
		def compare(a, b):
			return a > b
	else:
		def compare(a, b):
			return a < b
	for k in range(0, len(data)):
		for i in range(0, len(data) - k - 1):
			if compare(data[i], data[i + 1]):
				data[i], data[i+1] = data[i + 1], data[i]

	return data

