import sys
import string

#fp = open("

fi = open(sys.argv[1], "r")
fp = open("new_yapl.txt", "w")
bracket_status = 0
delimiters = [' ', '\t']
text = fi.read().split('\n')
for word in text:
	if ("insert_c{" in word) or ("{" in word and bracket_status > 0):
		bracket_status += 1
		print bracket_status
	if "}" in word and bracket_status > 0:
		bracket_status -= 1
		print bracket_status
	if bracket_status >= 1:
		#word = word.replace("\n", "")
		word = word.replace("\t", "")
		print "Inside bracket: " + str(bracket_status) +" " + word
		fp.write(word)
	else:
		fp.write(word + "\n")
		print "Outide bracket: " + str(bracket_status) + " " + word
		
print text
