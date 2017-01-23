from random import randint

thelist = []

for i in range(0,1001):
  thelist.append(randint(0,1000))

thefile = open('test.txt', 'w')
for item in thelist:
  thefile.write(str(item) + ",")