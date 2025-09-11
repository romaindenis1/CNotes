#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  //WINDOWS: _mkdir, LINNUX (eventually) <sys/stat.h> and mkdir()
#include "notes.h"
#include "ui.h"
#include <errno.h> 
void getNoteDetails(Note *note) {
    printf("Nom du fichier: ");
    fgets(note->filename, MAX_FILENAME, stdin);
    note->filename[strcspn(note->filename, "\n")] = '\0';

    strcpy(note->extension, ".txt");
    strcat(note->filename, note->extension);

    printf("Contenu de la note: ");
    fgets(note->content, MAX_CONTENT, stdin);
    note->content[strcspn(note->content, "\n")] = '\0';
}
void addNote() {
    Note note;
    char folder[50];
    clearInputBuffer();
    printf("Nom du dossier: ");
    fgets(folder, sizeof(folder), stdin);
    folder[strcspn(folder, "\n")] = '\0';

    if (strlen(folder) == 0) {
        strcpy(folder, ".");
    }

    if (_mkdir(folder) != 0) {
        if (errno != EEXIST) {
            perror("Erreur lors de la creation du dossier");
            return;
        }
    }

    getNoteDetails(&note);

    saveNoteToFile(&note, folder);
    pause();
}

void saveNoteToFile(Note *note, const char *folder) {
    char fullPath[MAX_PATH];

    if (strcmp(folder, ".") == 0) {
        snprintf(fullPath, sizeof(fullPath), "%s", note->filename);
    } else {
        snprintf(fullPath, sizeof(fullPath), "%s\\%s", folder, note->filename);
    }

    FILE *fptr = fopen(fullPath, "w");
    if (fptr == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        pause();
        return;
    }

    if (fprintf(fptr, "%s", note->content) < 0) {
        perror("Erreur lors de l'ecriture du fichier");
    }

    fclose(fptr);
}


void listNotes() {
    system("for /r %i in (*) do @echo %i | findstr /v \"\\\\.git\\\\\"");
    //LINUX smt like system("find . -type f | grep -v \".git\"");
    pause();
}

void deleteNote() {
    Note note;
    clearInputBuffer();
    printf("Nom du fichier a supprimer: ");
    fgets(note.filename, MAX_FILENAME, stdin);
    note.filename[strcspn(note.filename, "\n")] = '\0';

    strcat(note.filename, ".txt");

    if (remove(note.filename) == 0)
        printf("Fichier supprime.\n");
    else
        printf("Erreur: fichier introuvable.\n");

    pause();
}

void searchNotes() {
    printf("Fonction de recherche non implémentée.\n");
    pause();
}
