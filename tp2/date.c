#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Definition de la structure data
typedef struct date{
  int day;
  int mounth;
  int year;
} Date;


// Creation d'une structure date à partir d'une chaine de caractères
struct date *date_from_string(char *s){
  Date *ptr = malloc (sizeof(Date)); // On alloue de la mémoire à un pointeur sur une structure Data
  memset(ptr,0,sizeof(Date));  
  ptr->day =atoi(strtok(s, "/"));  // le jour correspond aux caractères présentes avant le premier slash
  ptr->mounth=atoi(strtok(NULL, "/")); // On récupère la chaine de caractères restante : 12/2018 par exemple et on coupe au niveau du premier slash !
  
  ptr->year=atoi(strtok(NULL, "/")); // On récupère ce qu'il reste

  //Note, autre façon de faire :strncpy(dest, src + beginIndex, endIndex - beginIndex);
  return ptr;
}

// Simple comparaison de dates : On vérifie quelle est la date la plus récente

int date_compare(struct date*d1, struct date *d2){
  if (d1->year == d2->year){
    if (d1->mounth==d2->mounth){
      if (d1->day >d2->day){
        return 1;
      }
      else if (d1->day < d2->day){
        return -1;
      }
      return 0;
    }
    if (d1->mounth > d2->mounth){
      return 1;
    }
    return -1;
  }
  else if (d1->year > d2->year){
    return 1;
  }
  return -1;
}

int main(int argc, char** argv){

  // On alloue deux dates : celle que l'on va retourner et celle qui va nous permettre de parcourir la liste
  
  Date *to_return =malloc (sizeof(Date)); 

  Date *new_date = malloc (sizeof(Date));

  memset(to_return,0,sizeof(Date));
  memset(new_date,0,sizeof(Date));

  // Pour afficher le mois, on utilise simplement un tableau stockant les mois de l'année

  const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

  // Au début la date à retourner correspond à la première date passée en argument

  memcpy(to_return,date_from_string(argv[1]),sizeof(Date));

  // On la compare ensuite aux autres dates
  for (int i=2;i<argc;i++){


    memcpy(new_date,date_from_string(argv[i]),sizeof(Date));

    // Si la date passée en argument est plus récente : on remplace ! 
    if (date_compare(new_date,to_return)>0){

      memset(to_return,0,sizeof(Date));

      memcpy(to_return, new_date, sizeof(Date));

      memset(new_date,0,sizeof(Date));

    }
  }

  // On affiche au format demandé (on utilise le tableau mounths pour récupérer le mois de l'année)
  printf("%d %s %d\n",to_return->day,months[to_return->mounth-1],to_return->year);
  return 0;
}
