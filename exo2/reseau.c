#include <stdio.h>
#include <stdlib.h>
#define MAX_TOKENS 5
#include <string.h>
#include <math.h>
#include "reseau.h"

void addresse_reseau(int* bin_reseau)
{
	int reseau[4];
	int tab[35];
	int i=0;
	int n=0;
	int puissance=0;
	int p=0;
	for(n=0 ;n<8 ;n++)
	{
		puissance=pow(2,p);
		tab[n]=bin_reseau[n]*puissance;
		p++;
	}
	reseau[0]=0;
	for(i=0;i<8;i++)
	{
		reseau[0] +=tab[i];
	}
	
	///printf("%d",reseau[0]);
	p=0;
	for(n=8 ;n<16 ;n++)
	{
		puissance=pow(2,p);
		tab[n]=bin_reseau[n]*puissance;
		p++;
	}
	reseau[1]=0;
	for(i=8;i<16;i++)
	{
		reseau[1] +=tab[i];
	}
	
	p=0;
	for(n=16 ;n<24 ;n++)
	{
		puissance=pow(2,p);
		tab[n]=bin_reseau[n]*puissance;
		p++;
	}
	reseau[2]=0;
	for(i=16;i<24;i++)
	{
		reseau[2] +=tab[i];
	}
	
	p=0;
	for(n=24 ;n<32 ;n++)
	{
		puissance=pow(2,p);
		tab[n]=bin_reseau[n]*puissance;
		p++;
	}
	reseau[3]=0;
	for(i=24;i<32;i++)
	{
		reseau[3] +=tab[i];
	}
	
	for(int k=0 ; k<4 ;k++)
	{
		printf("%d",reseau[k]);
		if(k<3)
		{
			printf(".");
		}
	}
}

int *addresse_broadcast_binaire(int *binaire,int *bin_tmp)
{
	int *bin_broadcast;
	bin_broadcast=(int*)malloc(40*sizeof(int));
	int i=0;
	for(i=0;i<32;i++)
	{
		if(binaire[i]==1 || bin_tmp[i]==1)
		{
			bin_broadcast[i]=1;
		}
		else
		{
			bin_broadcast[i]=0;
		}
	}
	
	return(bin_broadcast);
}

int *contraire(int *bin_mask)
{
	int *bin_tmp;
	bin_tmp=(int*)malloc(40*sizeof(int));
	int i=0;
	for(i=0;i<32;i++)
	{
		if(bin_mask[i]==1)
		{
			bin_tmp[i]=0;
		}
		else
		{
			bin_tmp[i]=1;
		}
	}

	return(bin_tmp);
}

int *addresse_reseau_binaire(int *binaire,int *bin_mask)
{
	int *bin_reseau;
	bin_reseau=(int*)malloc(40*sizeof(int));
	int i=0;
	for(i=0;i<32;i++)
	{
		if(binaire[i]==0 || bin_mask[i]==0)
		{
			bin_reseau[i]=0;
		}
		else
		{
			bin_reseau[i]=1;
		}
	}
	
	return(bin_reseau);
}

void condition_mask(int *bin_mask)
{
	int i=0;
	for(i=0;i<32;i++)
	{
		if(bin_mask[i]==0 && bin_mask[i+1]==1)
		{
			printf("masque de sous reseau invalide\n");
			exit(4);
		}
	}
	
}

int* calc_bin(int* tab)
{
	int *bin;
	bin=(int*)malloc(40*sizeof(int));
	int puissance=0;
	int moins=0;
	int n=0;
	int colonne=0;
	int i=0;
	for(i=0;i<4;i++)
	{
		moins=tab[i];
		for(n=7;n>=0;n--)
		{
			puissance=pow(2,n);
			if(moins>=puissance)
			{
				moins=moins-puissance;
				bin[colonne]=1;
				colonne++;
			}
			else
			{
				bin[colonne]=0;
				colonne++;
			}
		}
	}
	
	return(bin);
	
}

int *tableau(char* ip)
{
	int *tabaddresse;
	tabaddresse=(int*)malloc(40*sizeof(int));
	int j=0;
	int i=0;
	char *tokens[MAX_TOKENS];
	const char delimiter[] = ".";
	char *token = strtok(ip, delimiter); 
	while (token != NULL && j < MAX_TOKENS)
	{
        tokens[j] = token;
        j++;
        token = strtok(NULL, delimiter);
    }
    
    for(i=0 ; i<4 ; i++)
    {
		tabaddresse[i]=atoi(tokens[i]);
	}
	return(tabaddresse);
}

void condition(char *addresse)
{
	int nombre_point=0;
	int len =0;
	len=strlen(addresse);
	int i=0;
	for(i=0; i<len; i++)
	{
		if(addresse[i]=='.')
		{
			nombre_point++;
		}
	}
	
	if(nombre_point !=3 )
	{
		printf("ceci n'est pas un addresse IP V4");
		exit (3);
	}
	
}

void class(char *addresse,int *tabaddresse)
{
    
	for(int i=0 ; i<4 ; i++)
	{
		if(tabaddresse[i]<0)
		{
			printf("adresse IP non valide\n");
			printf("%d inférieur à 0",tabaddresse[i]);
			exit (1);
		}
		if(tabaddresse[i]>255)
		{
			printf("adresse IP non valide\n");
			printf("%d supérieur à 8-bit",tabaddresse[i]);
			exit (2);
		}
	}
	if(tabaddresse[0]>=0 && tabaddresse[0]<=127)
	{
		printf("l'addresse IP est de classe A\n");
	}
	
	if(tabaddresse[0]>=128 && tabaddresse[0]<=191)
	{
		printf("l'addresse IP est de classe B\n");
	}
	
	if(tabaddresse[0]>=192 && tabaddresse[0]<=223)
	{
		printf("l'addresse IP est de classe C\n");
	}
	
	if(tabaddresse[0]>=224 && tabaddresse[0]<=239)
	{
		printf("l'addresse IP est de classe D\n");
	}
	if(tabaddresse[0]>=240 && tabaddresse[0]<=255)
	{
		printf("l'addresse IP est de classe E\n");
	}
}
