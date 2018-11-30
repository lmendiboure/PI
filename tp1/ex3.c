#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*Objectif : chercher dans un fichier (un mot par ligne !) les mots possédant une lettre donnée à une position donnée*/

#define MAX_WORD_SIZE 64 //taille max d'un mot

int main(int argc, char *argv[])
{
  // On récupère les différents paramètres demandé pour le programme

  int len = atoi(argv[1]); // Argument inutile
  int position=atoi(argv[2])-1; //Position de la lettre dans le mot, -1 car les postions commencent à 0 en C
  char letter = *(argv[3]); //on récupère la lettre à rechercher
  int size = atoi(argv[4])+1; //On récupère la taille de mot voulue, +1 correspond au '\0' récupéré lors de la lecture des mots dans le fichier, plutôt sale...
  char str[WORD_SIZE]; //on définit un tableau de longueur 64
  memset(str,0,WORD_SIZE); // on remplit de 0
  while( fgets(str,WORD_SIZE,stdin) != NULL ){ //On lit ligne à ligne l'entrée standard (tant qu'il y a des lignes à lire!)

    if ((strlen(str)==size)&&(str[position]==letter)){ // On regarde si le mot correspond bien à ce que l'on cherche, lettre à la bonne position ? Bonne longueur ? si oui, on affiche !
      printf("%s\n",str);
    }
    memset(str,0,WORD_SIZE); // On remplit à nouveau str de 0 avant lecture de la ligne suivante
  }

  return 0;
}
