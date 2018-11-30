#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAB_SIZE 26

/*
Idée : créer un tableau de 26 caractères et lorsqu'on rencontre un 'a' ou 'A' dans la chaine de caractères passée en argument, on incrémente la première case du talbeau correspondant au nombre de 'a', même chose pour chacune des lettres.
*/
int main(int argc, char **argv)
{
  if (argv[1]){

    /* On initialise un tableau ayant la longueur de l'alphabet et on le remplit à 0, utiliser memset à la création d'un nouveau tableau est important
    */
    int res_tab[TAB_SIZE];
    memset(res_tab,0,TAB_SIZE*sizeof(int));

    /*On parcourt un à un les caractères composant la chaine de caractères passée en arguments,*/

    for (int i=0; i<strlen(argv[1]); i++){
	//MAJ et MIN indifférenciés
        char letter = tolower(argv[1][i]); 

	// On vérifie que le caractère que l'on est en train de traiter est bien une lettre de l'alphabet
        if ((letter >='a') && (letter<='z')){

	/*Si c'est le cas, on incrémente la case du tableau correspondante, exemple avec la lettre 'a' : letter -'a'= 0, on incrémente la première case
        */

          res_tab[letter - 'a']++; 

        }
    }

    /*On affiche le tableau que l'on vient de remplir ainsi que la lettre correspondante
    */

    for(int i = 0; i < TAB_SIZE ; i++){
      if (res_tab[i]){
	      printf("%c : %i\n",'a'+i,res_tab[i]);
	}
    }

  }

  return 0;
}
