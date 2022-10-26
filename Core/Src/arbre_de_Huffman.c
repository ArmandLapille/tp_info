#include "arbre_de_Huffman.h"
#include <stdio.h>
#include <stdlib.h>


//txt non compressé
uint8_t texte[] = "aaaabbbccd";

//txt compressé
uint8_t texteCompress[TAILLE_MAX_COMPRESS];

//tab du nombre d'occurences de chaque caractère
uint32_t tabCaractere[256]={0};

//nb de caractères total dans le txt non compressé
uint32_t nbrCaractereTotal = 0;

//nb de caracteres différents dans le txt non compressé
uint32_t nbrCaractereDifferent = 0;

//arbre de Huffman
struct Noeud* arbreHuffman[256];

//Racine de l'arbre
struct Noeud* racine;


//fonction test de l'abre de Huffman
void arbre_de_Huffman(void){
	uint8_t taille = 0;

	 /*
	 * appel de la fct occurence, arg texte et tab : on comptabilise le nb d'occurence de chaque caractère
	 */
	occurence(texte,tabCaractere);

	//création des feuilles de l'arbre
	taille = creerFeuille(arbreHuffman,tabCaractere);
    printf("///////////////////////////////////////////////////////////////////////// \n");
	printf("Arbre Initiale \n");
	afficheArbre(arbreHuffman,taille);

	//tri de l'arbre
	tri_de_Arbre(arbreHuffman,taille);
	printf("///////////////////////////////////////////////////////////////////////// \n");
	printf("Arbre trié \n");
	afficheArbre(arbreHuffman,taille);

	printf("///////////////////////////////////////////////////////////////////////// \n");
	printf("Création de la racine \n");
	cree_racine(arbreHuffman, taille, racine);
	racine = arbreHuffman[0];

	printf("///////////////////////////////////////////////////////////////////////// \n");
	printf("On parcourt l'arbre \n");
	parcourirArbre(racine);

	printf("///////////////////////////////////////////////////////////////////////// \n");
	printf("caractère en binaire : \n");
	creerCode(racine, code, tailleCode);

	printf("///////////////////////////////////////////////////////////////////////// \n");
	printf("compression de l'arbre \n");
	compression(texteCompress, racine, texte);

	/*
	printf("///////////////////////////////////////////////////////////////////////// \n");
	printf("On créé l'entête \n");
	entete = creerentete(texte, texteCompress);
	*/
}

//Fonction qui crée & initie les feuille d'un arbre à partir du texte
/*ENTREE = arbre[256] (tableau qui contient les adressse de chaque feuille)
 * 		   texte[256] (texte à compresser)
 *SORTIE = taille (nbr de caractères différents)
*/
uint8_t creerFeuille(struct Noeud* arbre[256], uint32_t texte[256]){
	int i=0;
	uint8_t taille=0;
	struct Noeud* feuille;
	for(i=0;i<256;i++){
		if(texte[i] != 0){
			feuille = malloc(sizeof(struct Noeud));
			/*
			 * allocution dynamique qui permet d'allouer le bon espace mémoire pour le nombre de feuilles
			 */

			feuille->c = i;
			feuille->occurence = texte[i]; // occurence prend la valeur du caractère correspondant dans le tableau
			feuille->code = 0;
			feuille->tailleCode = 0;
			feuille->gauche = NULL;
			feuille->droite = NULL;
			arbre[taille] =  feuille;
			taille+=1; // on insère un nouveau caractère donc on incrémente la taille de +1
		}
	}
	return taille;
}

//COmpteur d'occurence de chaque caractére dans la chaine
/*ENTREE = tabCaractere[256] (le tab recense le nb d'occurence de chaque caractère du code ASCII
 * 		   texte[256] (texte à compressée)
*/
void occurence(uint8_t texte[256], uint32_t tabCaractere[256]){
	int i=0;
    for(i=0;i<strlen(texte);i++){
        tabCaractere[texte[i]] ++; // prend lettre à lettre du texte et incrémente de +1
    }
}

//Fonction qui affiche l'arbre
/*ENTREE = arbre[256] (tableau qui contient les adressses de chaque feuille)
 * 		   taille (nbr de caractères differents dans la chaine de caractères)
*/
void afficheArbre(struct Noeud *arbre[256],uint32_t taille){
	int i=0;
    struct Noeud feuille;
    for(i=0;i<taille;i++){
        feuille = *arbre[i]; // récupère chaque élément de l'arbre
        if(feuille.c != '\0'){ // on affiche uniquement les caractères dont le nb d'occurence n'est pas nul
        	printf("Adresse : %p,Cara: %c ,occu : %ld,code : %ld, taille : %ld, noeud gauche : %p, noeud droit : %p \n",arbre[i],feuille.c,feuille.occurence,feuille.code,feuille.tailleCode,feuille.gauche,feuille.droite);
        }
    }
    printf("\r\n");

}

//Fonction qui trie l'arbre par un tri par selection
/*ENTREE = arbre[256] (tableau qui contient les adressse de chaque feuille)
 * 		   taille (nb de caractères différents)
*/

void tri_de_Arbre(struct Noeud* arbre[256],uint8_t taille){
	int i,j;

	struct Noeud *feuille, *feuille1, *feuille_c;

	for( i=0;i<(taille-1);i++){
	    for(j=i+1;j<taille;j++){
			feuille = arbre[i]; // prend le premier élément de la structure noeud et le met dans fauille
	    	feuille1 = arbre[j];
	        if ( feuille->occurence > feuille1->occurence ) {
	            feuille_c = feuille;
	            arbre[i] = feuille1;
	            arbre[j] = feuille_c;
	            // compare et trie deux éléments, avec mémoire tampon "feuille_c" (buffer
	        }
		}
	}
}

void cree_racine(struct Noeud* arbre[256], uint32_t taille,struct Noeud* racine){
	struct Noeud *noeud, *noeud1, *newnoeud;
	uint8_t occu = 0;
	uint8_t i = taille;
	while(i != 1){
		triArbre(arbre,taille);
		printf("///////////////////////////////////////////////////////////////////////// \n");
		afficheArbre(arbreHuffman,taille);
		noeud = arbre[0];
		noeud1 = arbre[1];
		occu = noeud->occurence + noeud1->occurence; // on somme le nb d'occurence des 2 plus petits éléments
		newnoeud = malloc( sizeof(struct Noeud)); // on créé un nouveau noeud avec cette somme
		newnoeud->c = '!'; // mise d'un nouveau char dans ce noeud
		newnoeud->occurence = occu; // occurence du nouveau noeud prend la valeur de la somme des 2 noeuds précédents les plus petits
		newnoeud->code = 0; //
		newnoeud->tailleCode = 0;
		newnoeud->gauche = noeud; // on fournit l'adresse des deux noeuds de l'étage inférieur de l'arbre
		newnoeud->droite = noeud1;
		arbre[0] = newnoeud; // l'élément gauche du tableau somme les valeurs des plus petites occurences
		arbre[1] = 0; // on supprime l'élément droit du tableau
		i--;
	}
	afficheArbre(arbreHuffman,taille);
}

// permet de dissocier les feuilles des Noueds
void parcourirArbre(struct Noeud* ptrNoeud){
	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		printf("je suis une feuille\r\n");
	}
	else{
		printf("Je suis un noeud : droite : %p, gauche : %p \r\n",ptrNoeud->droite,ptrNoeud->gauche);
		parcourirArbre(ptrNoeud->droite);
		parcourirArbre(ptrNoeud->gauche);
	}
}

void creerCode(struct Noeud* ptrNoeud,uint32_t code, uint32_t taille){
	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		ptrNoeud->tailleCode=taille;
		ptrNoeud->code=code;
		printf("%c \t code : %d \t taille :%d \r\n",ptrNoeud->c, ptrNoeud->code, ptrNoeud->tailleCode);
	}
	else{
		creerCode(ptrNoeud->droite,code<<1,taille+1);
		creerCode(ptrNoeud->gauche,(code<<1)+1,taille+1);
	}
}

struct Noeud* getAdress(struct Noeud* ptrNoeud, uint8_t caractere){
	struct Noeud* noeud;
	if(ptrNoeud->droite==NULL && ptrNoeud->gauche==NULL){
		if(ptrNoeud->c == caractere){
			noeud = ptrNoeud;
			return noeud;
		}
		else{
			return NULL;
		}
	}
	else{
		noeud = getAdress(ptrNoeud->droite,caractere);
		if(noeud == NULL){
			return getAdress(ptrNoeud->gauche,caractere);
		}
	}
}

struct Entete* creeentete(uint8_t *texte, uint8_t texteCompress[TAILLE_MAX_COMPRESS])
{
	struct Entete* entete;
	struct Noeud* noeud;

	entete->taille_fichier = strlen(texteCompress);
	entete->taille_entete = sizeof(struct Entete);
	entete->nbr_total = strlen(texte);

	for(int i=0;i<taille;i++){
		noeud = getAdress(racine,texte[i]);
		entete->code_Huffman[i] = noeud->code;
		entete->code_ascii[i] = noeud->c;
		entete->taille_code[i] = noeud->tailleCode;

	}
	return entete;
}

void compression(uint8_t texteCompress[TAILLE_MAX_COMPRESS],struct Noeud* racine,uint8_t texte[10]){
	uint8_t k=0,v=0;
	int f=0,BIT=7;
		for(int i=0;i<strlen(texte);i++){
			noeud_test = getAdress(racine,texte[i]);
			v=0;
			for(int j=(noeud_test->tailleCode+k);j>k;j--){
				texteCompress[f] |= (READ_BIT(noeud_test->code,v) << BIT);

				BIT -- ;
				v++;
				printf("%d \n",BIT);
				if(BIT<0){
					BIT=7;
					f++;
				}
			}
			k += noeud_test->tailleCode;
			printf("\n");
		}
}

