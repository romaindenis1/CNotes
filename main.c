#include <stdio.h>
#include <stdlib.h>
#include "notes.h"
#include "ui.h"

int main() {
    int choice;

    while (1) {
        clearScreen();
        printMenu();
        choice = getUserChoice();

        switch (choice) {
            case 1:
                addNote();
                break;
            case 2:
                listNotes();
                break;
            case 3:
                searchNotes();
                break;
            case 4:
                deleteNote();
                break;
            case 5:
                return 0;
            default:
                printf("Choix invalide.\n");
                return 0;
        }
    }
}
