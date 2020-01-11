import re
regex_instruction = re.compile('[\[\]\"\n]')
regex_parameter = re.compile('[\[\]\n]')

def write_instruction(file_name, display):
	with open(file_name, 'r') as file_in:
		lines = [line for line in file_in]
		instructions = [regex_instruction.sub('', element) for element in lines[0].split(',')]
		parameters = [regex_parameter.sub('', element) for element in lines[1].split(',')]

	print(instructions[0] + ' ' + instructions[0].lower()+';\n', end='')
	for i in range(1, len(instructions)):
		try:
			print(display[instructions[i]] * 'cout << ' + instructions[0].lower() + '.' + instructions[i] + '(' + parameters[i] + ')'+ display[instructions[i]] * ' << endl' +';\n', end='')
		except KeyError:
			print(instructions[0].lower() + '.' + instructions[i] + '(' + parameters[i] + ')'+ ';\n', end='')
	# with open(file_name.split('.')[0] + '_out.txt', 'w') as out:
	# 	out.write(instructions[0] + ' ' + instructions[0].lower()+';\n')
	# 	for i in range(1, len(instructions)):
	# 		out.write(display[instructions[i]] * 'cout << ' + instructions[0].lower() + '.' + instructions[i] + '(' + parameters[i] + ')'+ display[instructions[i]] * ' << endl' +';\n')

def write_test_interface(file_name):
	display = {}
	display['search'] = 1; 
	write_instruction(file_name, display)

def write_convert_to_cpp(file_name, lis):
	data = ""
	with open(file_name, 'r') as file:
		string = 0
		char = 0
		dimention = 0
		lines = file.readlines()
		
		if('\n' in lines):
			lines.remove('\n')

		idx = 0
		dimention  += min(len(lines) - 1, 2) * ('[[') not in lines[1]
		if dimention == 2:
			data += '{\n'

		while idx < len(lines): 
			if(not string and not char and ("string" in lines[idx] or "char" in lines[idx])):
				string = "string" in lines[idx]
				char = "char" in lines[idx]
				idx += 1
				continue

			if(dimention == 0):
				for c in lines[idx]:
					dimention += c == ord('[')
					if dimention == 2:
						data += '{\n'
						break;
			
			d = lines[idx].replace('\'', '').replace('\"', '').replace('[', '').replace(']', '').replace('\n', '').replace(',', ' ').split()
			data += '{' + '\"' * string + '\'' * char
			data += ('\"' * string  + '\'' * char + ',' + '\"' * string  + '\'' * char).join(d)
			data +=  '\"' * string  + '\'' * char+ '}' + (dimention == 2) * ',' + '\n'
			idx += 1

		if(dimention == 2):
			data += '}\n'
		
	print(data)
		# with open(file_name.split('.')[0] + '_out.txt', 'w') as out:
		# 	for line in file:
		# 		out.write(line.replace('[','{').replace(']', '}').replace(' ',''))


if __name__ == '__main__':
	write_convert_to_cpp('test.txt', [[0]])
	# write_test_interface('instruction.txt')


