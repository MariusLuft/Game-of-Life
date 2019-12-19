#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
// Bionikanimation "Life"

void printorganism(char(*arr)[22], int anz) {						//druckt organismus
	int i, j;
	for (j = 1; j<anz - 1; j++) {
		for (i = 1; i < anz - 1; i++) {
			printf("%c ", arr[j][i]);
		}
		printf("\n");
	}
}

void loadsterne(int(*arr1)[22], int anz, char(*arr2)[22]) {			//lädt Organismus vom Zahlenarray
	int i, j;
	for (j = 1; j < anz - 1; j++) {
		for (i = 1; i < anz - 1; i++) {
			if (arr1[j][i] == 0)
				arr2[j][i] = ' ';
			if (arr1[j][i] == 1)
				arr2[j][i] = '*';
		}
	}
}

void calcnextgen(int(*arr)[22], int anz) {					//Berechnet Organismus in nächster Generation
	int i, j, nachbarnlebend = 0;
	for (j = 1; j < anz - 1; j++) {
		for (i = 1; i < anz - 1; i++) {
			if (arr[j - 1][i - 1] == 1)
				nachbarnlebend++;
			if (arr[j][i - 1] == 1)
				nachbarnlebend++;
			if (arr[j + 1][i - 1] == 1)
				nachbarnlebend++;
			if (arr[j - 1][i] == 1)
				nachbarnlebend++;
			if (arr[j + 1][i] == 1)
				nachbarnlebend++;
			if (arr[j - 1][i + 1] == 1)
				nachbarnlebend++;
			if (arr[j][i + 1] == 1)
				nachbarnlebend++;
			if (arr[j + 1][i + 1] == 1)
				nachbarnlebend++;

			switch (nachbarnlebend) {
			case 0: arr[j][i] = 0;
				break;
			case 1: arr[j][i] = 0;
				break;
			case 3: arr[j][i] = 1;
				break;
			case 4: arr[j][i] = 0;
				break;
			case 5: arr[j][i] = 0;
				break;
			case 6: arr[j][i] = 0;
				break;
			case 7: arr[j][i] = 0;
				break;
			case 8: arr[j][i] = 0;
				break;
			}
			nachbarnlebend = 0;
		}
	}
}

void getstartpos(int (*arr1)[22], int max, char *name) {			//lädt startposition aus datei
	int i,j;		//Dateien müssen sich im selben Verzeichnis wie Programm befinden!
	int zeichen;
	FILE *fp;
	if ((fp = fopen(name, "rt")) == 0) 
		printf("Problem beim oeffnen!\n");
	
	for (j = 0; j < max; j++) {
		for (i = 0; i < max; i++){
			fscanf(fp, "%d", &zeichen);
			arr1[j][i] = zeichen;
		}
	}
	fclose(fp);
	}

void zufpos(int(*arr)[22], int anz, float lebendeuser) {          
	srand(time(NULL)); int lebendopt;
	lebendopt = (lebendeuser/100)*(anz*anz);
	int i, j,lebende=0,random=0,fehlend=0;
	for (j = 0; j < anz; j++) {						//erstellt Startposition zufällig und zählt lebende Zellen
		for (i = 0; i < anz; i++) {
			random = rand() % 2;
			arr[j][i] = random;
			if (random == 1)
				lebende++;
		}
	}

	if (lebende < lebendopt) {
		fehlend = lebendopt - lebende;           //passt lebende zellen an Wunsch des Nutzers an
		do {
			int x = rand() % 23; int y = rand() % 23;
			if (arr[x][y] == 0) {
				arr[x][y] = 1;
				fehlend--;
			}
		} while (fehlend >= 0);
	}

	if (lebende > lebendopt) {
		fehlend = lebende - lebendopt;
		do {
			int x = rand() % 23; int y = rand() % 23;
			if (arr[x][y] == 1) {
				arr[x][y] = 0;
				fehlend--;
			}
		} while (fehlend != 0);
	}
}

int main() {
	char sterne[22][22], *datei; int anz = 22, antwort1=0, menu=0, antwort2=0;  
	int rechner[22][22],name; float lebendeuser;
	printf("*********************Willkommen bei der Bionikanimation Life**************************\n					|||MENU|||\n\nSpielen mit Startposition aus Datei			1\nSpielen mit zufaelliger Startposition			2\nSpiel beenden						3\n**************************************************************************************\n");
	scanf("%d", &menu);
	switch (menu) {
	case 3: puts("Schoenen Tag noch");
		exit(0);																					//MENU
		break;
	case 2: puts("Wie viel Prozent des Startfeldes soll lebendig sein?");
		scanf("%f", &lebendeuser);
		zufpos(rechner, anz, lebendeuser);
		break;
	case 1: puts("Welche Datei soll als Startzustand geladen werden?\nDatei1			1\nDatei2			2\nDatei3			3");
		scanf("%d",&name);
		switch (name) {
		case 1: datei = "Datei1.txt";
			break;
		case 2: datei = "Datei2.txt";
			break;
		case 3: datei = "Datei3.txt";
			break;
		}
		getstartpos(rechner, anz, datei);
		break;
	}
	puts("Soll das Programm fluessig oder schrittweise ausgefuehrt werden?\nfluessig=0\nschrittweise=1");				
	scanf("%d",&antwort1);
	system("cls");
	while (1) {																						
			loadsterne(rechner, anz, sterne);
			printorganism(sterne, anz);
			calcnextgen(rechner, anz);
			if (antwort1 == 1) {
				printf("Moechten sie fortfahren?\nja = 0\nnein = 1\n");							//schrittweise: mit abfrage
				scanf("%d", &antwort2);
				if (antwort2 == 1)
					exit (0);
			}
			Sleep(500);
			system("cls");
	}
	
	return 0;
}



