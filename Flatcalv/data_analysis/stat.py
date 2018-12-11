import os
import glob
import numpy as np

liste=glob.glob('/home/semmer/Bureau/sbcp/projet_num/flatcal/code_source/stat/resultats/test*.txt');#l est une liste dont chaque element est l'adresse d'un fichier commençant par test et finissant par.txt
Xerror=[];
Xm=[];
Y=[];
print(l);
#précise que ce programme marche surtout pour faire des moyennes sur plusieurs ./a.out dans le cas particulier où l'on veut taux de saturation en fonction de t. Il est donc à modifier
for i in range(15):#le range vaut E(Ng*0.8)
	x=[];
	for j in l:
		fichier=open(j,"r");
		contenu=fichier.read();
		c=(contenu.split(" "));
		print(c);
		for z in range(len(c)//2):
			if float(c[1+2*z])==(float(i)/20):#float(i)/Ng
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
	


