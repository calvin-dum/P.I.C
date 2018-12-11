import os
import glob
import numpy as np

l=glob.glob('/home/semmer/Bureau/sbcp/projet_num/flatcal/code_source/stat/resultats/test*.txt');
Xerror=[];
Xm=[];
Y=[];
print(l);
for i in range(15):
	x=[];
	for j in l:
		fichier=open(j,"r");
		contenu=fichier.read();
		c=(contenu.split(" "));
		print(c);
		for z in range(len(c)//2):
			if float(c[1+2*z])==(float(i)/20):
				c[2*z]=c[2*z].replace('\n','');
				x.append(float(c[2*z]));
		fichier.close();
	if len(x)!=0 :
		Xerror.append(np.std(x));
		Xm.append(np.mean(x));
		Y.append(float(i)/20);
fichier=open('/home/semmer/Bureau/sbcp/projet_num/flatcal/code_source/stat/resultats/stat.txt','w');
for i in range(len(Y)):
	fichier.write(str(Xm[i]));
	fichier.write(" ");
	fichier.write(str(Xerror[i]));
	fichier.write(" ");
	fichier.write(str(Y[i]));
	fichier.write("\n");
fichier.close();	
	


