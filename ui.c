#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

void printMenu() {
    printf("Welcome to notes app\n");
    printf("1) Add a note\n");
    printf("2) List notes\n");
    printf("3) Search note\n");
    printf("4) Delete a note\n");
    printf("5) Quit\n");
}

int getUserChoice() {
    int choice;
    printf("Que voulez vous faire? ");
    scanf("%d", &choice);
    return choice;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    printf("\nAppuyez sur une touche pour continuer...");
    getchar();
}
