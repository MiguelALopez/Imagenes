__author__ = 'miguelalf'


archivo = open('tiki.ppm', 'r')
tiki = open('newTiki.pgm', 'w')
tiki.write('P2\n20 20\n3\n')

print archivo.readline()
print archivo.readline()
print archivo.readline()
# print archivo.readline()
for i in range(0, 20):
    array = archivo.readline().split()
    for j in range(0, len(array), 3):
        num = float(array[j]) * 0.299 + float(array[j+1]) * 0.587 + float(array[j+2]) * 0.114
        tiki.write(str(int(num)) + ' ')
    tiki.write('\n')

archivo.close()
tiki.close()