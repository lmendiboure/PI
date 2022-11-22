#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// light = | on/off (un bit) | w/b/r/p (deux bits) | intensity (5%) (4 bits) |
// 0: white 1: blue 2: red 3: pink


int
menu () {
	int c;
	printf ("Select an order\n");
	printf ("\t1) On\n");
	printf ("\t2) Off\n");
	printf ("\t3) Change color\n");
	printf ("\t4) Change intensity\n");
	printf ("\t5) Exit\n");
	printf ("Choice : ? ");
	do
		scanf ("%d", &c);
	while (c < 1 || c > 5);
	return c;
}

void display_light (char light) {
	printf ("Light state:\n");
	if (light & 0x80) { // On vérifie que le premier bit est bien à un, si c'est le cas, la lampe est allumée !
		printf ("On\n");
	}
	else { // Sinon, elle est éteinte...)
	printf ("Off\n");
	}
 // Optimisations possibles pour l'intensité et la couleur : afficher l'intensité non pas entre 0 et 10 mais 10 et 100 (*10) et afficher la vraie couleur en différenciant les cas : 0 blanc, 1 bleu,...

	printf ("Intensity : %d\n", (light & 0x1e)>>1); // On met les bits qui ne correspondent pas à l'intensité à 0 et on décalle afin d'obtenir une valeur entre  et  : exemple : 00010010 > 00001001
	printf ("Color = %d\n", (light & 0x60)>>5); // On met les bits qui ne correspondent pas à l'intensité à 0 et on décalle

}

// 0: white 1: blue 2: red 3: pink
char set_color (char light, int color) {
	light &= ~ 0x60; // on commence par mettre à 0 les bits correspondant à la couleur
	light |= (color << 5); // on stocke la valeur de color (codée sur 2 bits) dans les bits 6 et 7 de light
	return light;
}

char menu_color (char light) {
	printf ("\n0: white\n1: blue\n2: red\n3: pink\n");
	printf ("Color : ? ");
	int color;
  do
    scanf ("%d", &color);
  while (color < 0 || color > 3); // on vérifie qu'on a bien une valeur comprise entre 0 et 3 !
  return set_color (light, color);
}

char set_intensity (char light, int intensity) {
	light &= 0xe1; // On met les bits correspondant à l'intensité à 0 !
	light |= intensity <<1; // on stocke la valeur de l'intensité dans les bits 1 à 5 de light
	return light;
}

char menu_intensity (char light) {
  printf ("Intensity : 0-10\n");
  int intensity;
  scanf ("%d", &intensity);
  return set_intensity (light, intensity);
}


char on (char light) {
  light |= 0x80; // On met le bit 8 à 1
  return light;
}


char off (char light) {
  light &= 0x7F; // On met le bit 8 à 0
  return light;
}

int main (int argc, char **argv) {

  char light = 0x00;
  while (1) {
    display_light (light);

    int c = menu ();
    if (c == 1)
      light = on (light);
    else if (c == 2)
      light = off (light);
    else if (c == 3)
      light = menu_color (light);
    else if (c == 4)
      light = menu_intensity (light);
  	else if (c == 5)
  	  exit(0);
  }

  return EXIT_SUCCESS;
}
