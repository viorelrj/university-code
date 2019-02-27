def heap(data):
	def heapify(data, n, i):
		largest = i  # Initialize largest as root
		left = 2 * i + 1     # left = 2*i + 1
		right = 2 * i + 2     # right = 2*i + 2
		# See if left child of root exists and is
		# greater than root
		if left < n and data[i] < data[left]:
			largest = left
		# See if right child of root exists and is
		# greater than root
		if right < n and data[largest] < data[right]:
			largest = right
		# Change root, if needed
		if largest != i:
			data[i], data[largest] = data[largest], data[i]  # swap
			# Heapify the root.
			heapify(data, n, largest)

	n = len(data)
	# Build a maxheap.
	for i in range(n, -1, -1):
		heapify(data, n, i)
	# One by one extract elements
	for i in range(n-1, 0, -1):
		data[i], data[0] = data[0], data[i]  # swap
		heapify(data, i, 0)

	return data
