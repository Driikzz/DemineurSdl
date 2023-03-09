#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#define taille 32
SDL_Window* fenetre;
SDL_Renderer* renderer;
SDL_Rect cases[taille];
SDL_Event events;



void afficherJeux(SDL_Rect t[taille]) {
	// Création de la fenêtre :
	fenetre = SDL_CreateWindow("Demineur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, 0);
	if (fenetre == NULL) // Gestion des erreurs
	{
		printf("Erreur lors de la creation d'une fenetre : %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	// Création du renderer :
	renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer
	if (renderer == NULL) // Gestion des erreurs
	{
		printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
		return EXIT_FAILURE;
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); //Couleur 
	
	cases[0].x = cases[0].y = 0;
	cases[0].w = cases[0].h = 100;
	for (int i = 1; i != 32; i++)
	{
		
		cases[i].x = cases[i - 1].x + 200;
		cases[i].y = cases[i - 1].y;
		if (i % 4 == 0) //retour à la ligne
		{
			cases[i].x = (i % 8 == 0) ? 0 : 100;
			cases[i].y = cases[i - 1].y + 100;
		}
		cases[i].w = cases[i].h = 100; //taille d'une case : 100 x 100
	}


	if (SDL_RenderFillRects(renderer, cases, 32) < 0)//Remplissage des cases blanches
	{
		printf("Erreur lors des remplissages de rectangles: %s", SDL_GetError());
		return EXIT_FAILURE;

	}


	SDL_RenderPresent(renderer);
}


int randomGeneratorBomb()
{
	int randomnumber;
	randomnumber = rand() % 8;
	return(randomnumber);
}

void createTable(char t[taille])
{
	for (int i = 0; i < taille; i++)
	{
		int randomBomb = randomGeneratorBomb();
		if (randomBomb == 1)
		{
			t[i] = '*';
		}
		else
		{
			t[i] = 'X';
		}
	}
	
}



void createBombMask(char tmask[taille]) {
	for (int i = 0; i < taille; i++)
	{
		tmask[i] = '.';
	}
}


void afficherTable(char tableau[taille])
{
	int y = 10;
	printf(" 0  1  2  3  4  5  6  7  8  9 \n\n");
	for (int i = 0; i < taille; i++)
	{
		printf(" %c ", tableau[i]);
		if (((i + 1) % 10) == 0)
		{
			printf("\n");
		}

	}
}


void bombautour(char table[taille])
{
	for (int i = 0; i < taille; ++i)
	{
		int count = 0;
		if (table[i] == 'X')
		{

			// compter le nombre de bombe adjacente
			if (table[i] == '*')
			{
				count = ++count;
			}

			if (i != 0)
			{
				if (table[i - 1] == '*')
				{
					count = ++count;
				}
				if (table[i - 10] == '*')
				{
					count = ++count;
				}
			}

			if (i != taille - 1)
			{
				if (table[i + 1] == '*')
				{
					count = ++count;
				}
				if (table[i + 10] == '*')
				{
					count = ++count;
				}
			}
			// converion count en char ASCI	I
			table[i] = (char)(count + 48);
		}

	}
}

void safeZone(char tmask[taille], char t[taille])
{
	int random = rand() % 20;
	for (int i = 0; i < 8; i++)

	{
		if (t[i] == '0')
		{
			tmask[i + 1] = t[i + 1];
			tmask[i + -1] = t[i + -1];
			tmask[i + 10] = t[i + 10];
			tmask[i + -10] = t[i + -10];

		}
	}
}

int main()
{
	srand(time(NULL));
	printf("   Bienvenue au demineur ! \n\n\n");
	char t[taille];
	SDL_Rect cases[taille];
	char tmask[taille];
	createTable(t);
	createBombMask(tmask);
	afficherTable(tmask);
	afficherJeux(cases);
	bombautour(t);
	safeZone(tmask, t);
	int start = 0;
	int choiseCase = 0;
	while (start == 0 ) {
		int errorCase = 0;
		

		
	
		while (errorCase == 0)
		{
			if (SDL_MOUSEBUTTONUP) {
				SDL_Log("click aaa");
			}

			
           

			printf("Choisie le numero de ta case :");

			scanf_s("%d", &choiseCase);

			if (choiseCase > taille)
			{
				printf("Nombre incorrect essaye encore !\n\n");

			}
			else if (choiseCase < 0)
			{
				printf("Nombre incorrect essaye encore !\n\n");

			}
			else {
				errorCase = 1;
			}

		}
		tmask[choiseCase] = t[choiseCase];

		printf("\n Tu as joue la case:  %d \n \n", choiseCase);
		afficherTable(tmask);
		if (tmask[choiseCase] == '*')
		{
			printf("\n Tu as trouve une bombe, perdu :c");
			break;
		}
		else
		{
			printf("\n \n");
		}
	}
}
