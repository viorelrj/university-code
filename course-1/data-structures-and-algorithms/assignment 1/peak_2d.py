def peak_2d(data):
  # Split the list in half
  index_y = int(len(data) / 2)

  # If there is only one list left, return the max of this list
  if (len(data) == 1):
    return max(data.pop())
  else:
    # index_max_x is the row index with the max value for the central column
    # of a specific list
    index_max_x = data[index_y].index(max(data[index_y]))

    # If the left or right neighbour of the max row on the central column is
    # bigger than the picked item, analyze that part of the list
    if(data[index_y][index_max_x - 1] > data[index_y][index_max_x]):
      return peak_2d(data[0: index_y])
    elif(data[index_y][index_max_x - 1] < data[index_y][index_max_x]):
      return peak_2d(data[index_y: len(data)])
    # If the values are equal, try to check them both (in case that there is no max in
    # one column selected )
    else:
      peak_2d(data[0: index_y])
      return peak_2d(data[index_y: len(data)])
