a = int
b = int
 
a = int(input('<< Quanto vale a: '))
b = int(input('<< Quanto vale b: '))
a, b = b, a
 
print ('a = ' + str(a) + ' e ' + 'b = ' + str(b))
