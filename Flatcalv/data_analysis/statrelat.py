import os
import glob
import numpy as np
import matplotlib.pyplot as plt

liste=glob.glob('/home/semmer/Bureau/sbcp/projet_num/flatcal/code_source/3D/data_analysis/Resultats/Nb*.txt');
terror=[];
tm=[];
X=[];

for j in liste:
	t=[];
	fichier=open(j,"r");
	contenu=fichier.read();
	c=(contenu.split(" "));
	X.append(float(c[0])/(0.4*60));
	print(c);
	for z in range(len(c)//2):
		t.append(float(c[2*z+1]));
	fichier.close();
	if len(t)!=0 :
		terror.append(np.std(t));
		tm.append(np.mean(t));

fichier=open('/home/semmer/Bureau/sbcp/projet_num/flatcal/code_source/3D/data_analysis/Resultats/statrelat.txt','w');
for i in range(len(X)):
	fichier.write(str(tm[i]));
	fichier.write(" ");
	fichier.write(str(terror[i]));
	fichier.write(" ");
	fichier.write(str(X[i]));
	fichier.write("\n");
fichier.close();

plt.scatter(X,tm,zorder=2)
plt.errorbar(X,tm,yerr=terror,fmt='none',capsize=10,ecolor='red',zorder=1)
plt.show()	
	


