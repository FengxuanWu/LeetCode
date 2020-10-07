import re
regex_instruction = re.compile('[\[\]\"\n]')

def write_instruction(file_name, display):
	with open(file_name, 'r') as file_in:
		lines = [line for line in file_in]
		instructions = [regex_instruction.sub('', element) for element in lines[0].split(',')]
		parameters = [element for element in lines[1][1 : -2].replace('[', '').split('],')]

	print(instructions[0] + ' ' + instructions[0].lower() + '(' + parameters[0] + ')' + ';\n', end='')
	for i in range(1, len(instructions)):
		print((instructions[i] in display.keys()) * 'cout << ' + instructions[0].lower() + '.' + instructions[i] + '(' + parameters[i].replace(']','') + ')' + (instructions[i] in display.keys()) * ' << endl' +';\n', end='')
	# with open(file_name.split('.')[0] + '_out.txt', 'w') as out:
	# 	out.write(instructions[0] + ' ' + instructions[0].lower()+';\n')
	# 	for i in range(1, len(instructions)):
	# 		out.write(display[instructions[i]] * 'cout << ' + instructions[0].lower() + '.' + instructions[i] + '(' + parameters[i] + ')'+ display[instructions[i]] * ' << endl' +';\n')

def test_interface(file_name):
	display = {}
	display['get'] = 1; 
	#display['startsWith'] = 1
	write_instruction(file_name, display)

def convert_to_cpp(file_name):
	data = ""
	with open(file_name, 'r') as file:
		string = 0
		char = 0
		dimention = 0
		lines = file.readlines()
		
		if('\n' in lines):
			lines.remove('\n')

		idx = 0
		if(len(lines) > 2):
			dimention = 2
			data += '{\n'

		while idx < len(lines): 
			if(']' == lines[idx]):
				idx += 1
				continue
				
			if(not string and not char and ("string" in lines[idx] or "char" in lines[idx])):
				string = "string" in lines[idx]
				char = "char" in lines[idx]
				idx += 1
				continue

			if(dimention == 0):
				for c in lines[idx]:
					dimention += c == '['
					if dimention == 2:
						data += '{\n'
						break;

			line = lines[idx].replace('\'', '').replace('\"', '').replace('[', '').replace('],', '\n').replace(',', ' ').replace('{', '').replace('}', '')
			for d in line.split('\n'):
				if(len(d) > 0):
					d = d.replace(']', '')
					data += '\t' * (dimention == 2) + '{' + '\"' * string + '\'' * char
					data += ('\"' * string  + '\'' * char + ', ' + '\"' * string  + '\'' * char).join(d.split())
					data +=  '\"' * string  + '\'' * char+ '}' + (dimention == 2) * ',' + '\n'
			idx += 1

		if(dimention == 2):
			data += '}'
	print(data)
	# with open(file_name.split('.')[0] + '_out.txt', 'w') as out:
	# 	out.write(data)


if __name__ == '__main__':
	convert_to_cpp('test.txt')
	# test_interface("instruction.txt")