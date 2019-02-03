def peak_1d(data):
  # If there is one item, it is the max
	if (len(data) == 1):
		return data.pop()
	else:
		index = int(len(data) / 2)
    # Split the list in two and process the one with the max
    # value from the closest edges
		if (data[index - 1] > data[index]):
			return peak_1d(data[0: index])
		elif (data[index - 1] > data[index]):
			return peak_1d(data[index: len(data)])
		else:
      # If edges are equal, process them sequencely, to find
      # At least one edge in every side of the list
			peak_1d(data[0: index])
			return peak_1d(data[index: len(data)])

