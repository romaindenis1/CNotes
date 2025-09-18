#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>  //WINDOWS: _mkdir, LINNUX (eventually) <sys/stat.h> and mkdir()
#include "notes.h"
#include "ui.h"
#include <errno.h> 
#include <windows.h>

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
    char tag[100];
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

    //ask for tag
    
    printf("Entrez un tag: ");
    fgets(tag, sizeof(tag), stdin);
    tag[strcspn(tag, "\n")] = '\0';

    if (strlen(tag) > 0) {
        char fullPath[MAX_PATH];
        if (strcmp(folder, ".") == 0) {
            snprintf(fullPath, sizeof(fullPath), "%s", note.filename);
        } else {
            snprintf(fullPath, sizeof(fullPath), "%s\\%s", folder, note.filename);
        }
        FILE *fptr = fopen(fullPath, "a");
        if (fptr) {
            fprintf(fptr, "\n#tag:%s#", tag);
            fclose(fptr);
        }
    }
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
    char searchQuery[100];
    char tagToFind[120];

    clearInputBuffer();
    printf("Entrez le tag a rechercher: ");
    fgets(searchQuery, sizeof(searchQuery), stdin);
    searchQuery[strcspn(searchQuery, "\n")] = '\0';

    snprintf(tagToFind, sizeof(tagToFind), "#tag:%s#", searchQuery);

    printf("Fichiers contenant le tag %s :\n", tagToFind);
    searchNotesRecursive(".", tagToFind);

    pause();
}


void searchNotesRecursive(const char *folder, const char *tagToFind) {
    char searchPath[MAX_PATH];
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    FILE *fp;
    char line[1024];
    int found;

    //search for files
    snprintf(searchPath, sizeof(searchPath), "%s\\*.txt", folder);
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            char filePath[MAX_PATH];
            snprintf(filePath, sizeof(filePath), "%s\\%s", folder, findFileData.cFileName);
            found = 0;
            fp = fopen(filePath, "r");
            if (fp) {
                while (fgets(line, sizeof(line), fp)) {
                    if (strstr(line, tagToFind)) {
                        found = 1;
                        break;
                    }
                }
                fclose(fp);
            }
            if (found) {
                printf(" - %s\n", filePath);
            }
        } while (FindNextFile(hFind, &findFileData));
        FindClose(hFind);
    }

    //search for subfolders
    snprintf(searchPath, sizeof(searchPath), "%s\\*", folder);
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                strcmp(findFileData.cFileName, ".") != 0 &&
                strcmp(findFileData.cFileName, "..") != 0) {
                char subFolder[MAX_PATH];
                snprintf(subFolder, sizeof(subFolder), "%s\\%s", folder, findFileData.cFileName);
                searchNotesRecursive(subFolder, tagToFind);
            }
        } while (FindNextFile(hFind, &findFileData));
        FindClose(hFind);
    }
}

