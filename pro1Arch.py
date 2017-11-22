from __future__ import division
#import threading
import multiprocessing
import time
import math

def Redu(formul):
    redu=[0]*16
    for i in formul:
        if ord(i)==99:
            redu[0]+=1
        elif ord(i)==67:
            redu[1]+=1
        elif ord(i)==78:
            redu[2]+=1
        elif ord(i)==79:
            redu[3]+=1
        elif ord(i)==64:
            redu[4]=1
        elif ord(i)==66:
            redu[5]+=1
        elif ord(i)==70:
            redu[6]+=1
        elif ord(i)==72:
            redu[7]+=1
        elif ord(i)==73:
            redu[8]+=1
        elif ord(i)==80:
            redu[9]+=1
        elif ord(i)==83:
            redu[10]+=1
        elif ord(i)==108:
            redu[11]+=1
        elif ord(i)==110:
            redu[12]+=1
        elif ord(i)==111:
            redu[13]+=1
        elif ord(i)==114:
            redu[14]+=1
        elif ord(i)==115:
            redu[15]+=1


    return redu

def totalComp(formu):
    total=0
    for i in formu:
        total+=i

    return total

def calSimi(formA,formB):
    total=0
    i=0
    for c in formA:
        if c<formB[i]:
            total+=c
        else:
            total+=formB[i]
        i+=1
    return total

def CoeT(Na,Nb,Nc):
    coef = Nc / (Na + Nb - Nc)
    
    #return coef
    return round(coef, 2)

def divWork(lim1,lim2,name,formu,totalP,arch):
    f = open(arch, 'w')
    for i in range(lim1, lim2):
        for j in range(i+1, n):
            v=CoeT(totalP[i],totalP[j],calSimi(formu[i],formu[j]))
	    #lock.acquire()
            f.write(name[i]+'\t'+name[j]+'\t'+repr(v)+'\n')
	    #lock.release()
    f.close()

def calcularLimites(a):
    limites = []
    for a in range(p+1):
	l=int(n - math.sqrt((p - a) / p) * n)     
	limites.append(l)
	print 'limites:'+repr(l)
        #limites.append(int(n - math.sqrt((p - a - 1) / p) * n))
    return limites

def startjoin_all(thread_array):
    for t in thread_array:
        #t.setDaemon(True)
        t.start()
    for t in thread_array:
        t.join()

#****Principal****
identif = []
totalPar=[]
formula = []
formRedu= []

archivo = open('ZINC_chemicals.tsv', 'r')
lineasT = archivo.readlines()
for linea in lineasT:
    identif.append( (linea.split('\t'))[1].strip('\n') )
    formula.append( (linea.split('\t'))[3].strip('\n') )
archivo.close()

for f in formula:
    #aux=contar(f)
    aux=Redu(f)
    formRedu.append(aux)
    totalPar.append(totalComp(aux))

start = time.time()
p=4
n=12422


#paraelizo-btengo coeficiente Tanimoto
threads=[]
limites=calcularLimites(p)
#bloqueo escritura
#lock=multiprocessing.Lock()
#pool=multiprocessing.Pool(processes=p)

for i in range(p):
   threads.append(multiprocessing.Process(target=divWork, args=(limites[i],limites[i+1],identif,formRedu,totalPar,'rPy'+repr(i)+'.txt')))

startjoin_all(threads)

end = time.time()

print (end - start)
