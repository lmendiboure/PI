#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Objectif : réussir à chiffrer/déchiffrer la chaine de caractère lue depuis l'entrée standard

#define ALPH_SIZE 26

/* 's' => "..." et 'o' => "---", la longueur de la chaine d'arrivée lors du chiffrement ne sera pas égale à celle de départ : il est nécessaire que l'on calcule la nouvelle longueur pour l'allocation de mémoire
*/
int calcul_longueur(char * str)
{
  int len = 0;
  for (int i=0;i<strlen(str);i++){
    if((str[i] == 's') || (str[i] == 'o')){
      len += 3;
    }
    else{
        len++;
    }
  }
  len ++;
  return len;
}

/* Modulo pourrait lors du déchiffrement renvoyer une valeur négative, ex on est à la lettre 'a' et la clé est 2, modulo renverrait -1 alors que ce que l'on veut est 25 pour rester dans l'alphabet!

*/

int mod(int a)
{
    int modulo=26;
    int r = a % modulo;
    return r < 0 ? r + modulo : r;
}

/*
Chiffrement de Cesar : on décalle dans l'alphabet en fonction de la clé en vayant à rester dans le bon espace de la table ASCII
*/

char cesar(char val, int key){
  char res=val;
  if ((val>='a') && (val<='z')){
     res = mod(val - 'a'+key) + 'a';
  }
  else if ((val>='A') && (val<='Z')){
    res = ((val - 'A' + key)%26 + 'A');
  }
  return res;  //Si ce n'est pas une lettre : on retourne la même valeur
}

/*
Fonction de chiffrement
*/

void chiffrer(char *str, int key)
{
  /*On initialise base qui correspondra à la chaine encryptée en veillant à allouer la mémoire nécessaire
  */
  char *base = NULL;
  int size = calcul_longueur(str);
  base = malloc(size*sizeof(char));
  memset(base,'\0',size*sizeof(char));

/*
on initialise une variable qui va nous permettre de savoir où on est est, si c'est un 's' ou un 'o' : on va trois positions plus loin !
*/
  int position =0;
/*
On chiffre en parcourant un à un les caractères de la chaine d'entrée, sur chacun d'eux on applique le chriffrement demandé
*/

  for (int i=0;i<strlen(str);i++){
    if (str[i]=='s'){
      base[position]='.';
      base[position+1]='.';
      base[position+2]='.';
      position=position+3;
    }
    else if (str[i]=='o'){
      base[position]='-';
      base[position+1]='-';
      base[position+2]='-';
      position=position+3;
    }
    else{
      base[position]=cesar(str[i],key);
      position++;
    }
  }
   fprintf(stdout,"%s\n",base);
   fflush(stdout);

}
/*
Fonction de chiffrement
*/

void dechiffrer(char *str, int key)
{
  /* On initialise base à la longueur de la chaine à décrypter (la chaine d'arrivée sera forcément plus courte !)
  */
  char *base = NULL;
  int size = strlen(str)+1;
  base = malloc(size*sizeof(char));
  memset(base,'\0',size*sizeof(char));

  // On peut une nouvelle fois utiliser une position, en effet on ne se déplacera pas de la même manière dans la chaine à décrypter et la chaine d'arrivée (si on rencontre "---"=> on ira directement 3 postiions plus loin !)
  int position=-1;

  // On déchiffre en fonction des différents cas

  for (int i=0;i< strlen(str);i++){
    position++;
    if ((strlen(str)-i)>2){
      if ((str[i]=='.')&&(str[i+1]=='.')&&(str[i+2]=='.')){
        base[position]='s';
        i+=2;
      }
      else if ((str[i]=='-')&&(str[i+1]=='-')&&(str[i+2]=='-')){
        base[position]='o';
        i+=2;
      }
      else{
        base[position]=cesar(str[i],-key);
      }
    }
    else{

      base[position]=cesar(str[i],-key);

    }
  }

  printf("%s\n",base);
}


int main(int argc, char *argv[])
{
  if(argc > 1) {
    int key = atoi(argv[2]);
    char *str = NULL;
    size_t size = 0;

    // Récupération depuis l'entrée standard, on stocke dans str !

    getline(&str,&size,stdin);

    // en fonction des cas on chiffre ou déchiffre
    if( strcmp(argv[1],"-c")==0){
      chiffrer(str,key);

    }
    else if (strcmp(argv[1],"-d")==0){
      dechiffrer(str,key);
    }

  } else {
    fprintf(stdout,"Pas assez de paramètres ! ");
  }
  return 0;
}
