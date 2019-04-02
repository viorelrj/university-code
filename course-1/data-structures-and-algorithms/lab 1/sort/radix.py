def radix(data, method='asc'):
	exp = 0
	exponents = {}
	while len(data) > 0:
		exponents[exp] = {x: [] for x in range(0, 10)}
		for number in data:
			exponents[exp][number // 10**(exp) % 10].append(number)
		del data[:]
		for digit in exponents[exp]:
			carry = list(filter(lambda x: x // 10**(exp + 1) > 0, exponents[exp][digit]))
			exponents[exp][digit] = list( filter(lambda x: x not in carry, exponents[exp][digit]))
			data.extend(carry)
			del carry[:]
		exp += 1

	if method == 'asc':
		for exponent in exponents:
			for digit in exponents[exponent]:
				for number in exponents[exponent][digit]:
					data.append(number)
		
	return data
