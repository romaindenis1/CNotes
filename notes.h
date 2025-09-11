#ifndef NOTES_H
#define NOTES_H

#define MAX_FILENAME 50
#define MAX_CONTENT 255
#define MAX_PATH 150

typedef struct {
    char filename[MAX_FILENAME];
    char extension[5];
    char content[MAX_CONTENT];
} Note;

void addNote();
void listNotes();
void deleteNote(); //does not work right now; nothing is deleted in folders yet
void searchNotes(); //soon

#endif
