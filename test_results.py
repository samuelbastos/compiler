expectedOne = open('one_expected.txt', 'r')
outputOne   = open('one_output.txt', 'r')

expectedListOne = []
outputListOne   = []  

errorList = []
for line in expectedOne:
	#line.strip()
	#print(line)
	expectedListOne.append(line)

for line in outputOne:
	#line.strip()
	#print(line)
	outputListOne.append(line)	

resultOne = open('result_one.txt', 'w')

i = 0
while i < len(expectedListOne) and i < len(outputListOne):

	if i == (len(expectedListOne)-1):
		resultOne.write(" EXPECTED: " + expectedListOne[i] + '\n' + " OUTPUT: " + outputListOne[i])
	else:
		resultOne.write(" EXPECTED: " + expectedListOne[i] + " OUTPUT: " + outputListOne[i] + '\n')
	i = i+1
	
resultOne.close()

expectedTwo = open('two_expected.txt', 'r')
outputTwo   = open('two_output.txt', 'r')

expectedListTwo = []
outputListTwo   = []  

errorList = []
for line in expectedTwo:
	#line.strip()
	#print(line)
	expectedListTwo.append(line)

for line in outputTwo:
	#line.strip()
	#print(line)
	outputListTwo.append(line)	

resultTwo = open('result_two.txt', 'w')

i = 0
while i < len(expectedListTwo) and i < len(outputListTwo):

	if i == (len(expectedListTwo)-1):
		resultTwo.write(" EXPECTED: " + expectedListTwo[i] + '\n' + " OUTPUT: " + outputListTwo[i])
	else:
		resultTwo.write(" EXPECTED: " + expectedListTwo[i] + " OUTPUT: " + outputListTwo[i] + '\n')
	i = i+1
	
resultTwo.close()

expectedThree = open('three_expected.txt', 'r')
outputThree   = open('three_output.txt', 'r')

expectedListThree = []
outputListThree   = []  

errorList = []
for line in expectedThree:
	#line.strip()
	#print(line)
	expectedListThree.append(line)

for line in outputThree:
	#line.strip()
	#print(line)
	outputListThree.append(line)	

resultThree = open('result_three.txt', 'w')

i = 0
while i < len(expectedListThree) and i < len(outputListThree):

	if i == (len(expectedListThree)-1):
		resultThree.write(" EXPECTED: " + expectedListThree[i] + '\n' + " OUTPUT: " + outputListThree[i])
	else:
		resultThree.write(" EXPECTED: " + expectedListThree[i] + " OUTPUT: " + outputListThree[i] + '\n')
	i = i+1
	
resultThree.close()