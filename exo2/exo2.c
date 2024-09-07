#include <stdio.h>
#include <stdlib.h>
#define MAX_TOKENS 5
#include <string.h>
#include <math.h>
#include "reseau.h"

int main()
{
	char ip[22];
	int decoupage=0;
	
	printf("Entrez le CIDR : ");
	scanf("%[^/]/%d",ip,&decoupage);
	condition(ip);
	int *tab=NULL;
	tab=malloc(40*sizeof(char));
	tab=tableau(ip);
	class(ip,tab);
	
	int *binaire=NULL;
	binaire=malloc(40*sizeof(char));
	binaire=calc_bin(tab);
	
	int mask[32];
	for(int i=0;i<32;i++)
	{
		if(i<decoupage)
		{
			mask[i]=1;
		}
		else
		{
			mask[i]=0;
		}
	}
	
	int *bin_reseau=NULL;
	bin_reseau=malloc(40*sizeof(char));
	bin_reseau=addresse_reseau_binaire(binaire,mask);
	
	
	int *bin_tmp=NULL;
	bin_tmp=malloc(40*sizeof(char));
	bin_tmp=contraire(mask);
	
	int *bin_broadcast=NULL;
	bin_broadcast=malloc(40*sizeof(char));
	bin_broadcast=addresse_broadcast_binaire(binaire,bin_tmp);
	
	printf("addresse reseau : ");
	addresse_reseau(bin_reseau);
	printf("\n");
	
	printf("addresse de broadcast : ");
	addresse_reseau(bin_broadcast);
	printf("\n");

	printf("\n");
}

