import matplotlib.pyplot as plt

file = open("generated.txt", "r");
nums_str = (file.read())

gen_num_arr = []
index_num_arr = []

i = 0

for num in map(int, nums_str.split(" ")):
	gen_num_arr.append(num)
	index_num_arr.append(i)
	i += 1


plt.plot(index_num_arr, gen_num_arr)
plt.show()
