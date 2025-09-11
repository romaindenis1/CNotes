#include <stdio.h>

int main ()
{
    printf("Welcome to notes app\n");
    printf("1) Add a note\n");
    printf("2) List notes\n");
    printf("3) Search note\n");
    printf("4) Delete a note\n");
    printf("5) Quit\n");
    printf("Que voulez vous faire? ");

    int userInput;
    //d pour double
    scanf("%d", &userInput);
    switch (userInput)
    {
        case 1:
            addNote();
            break;
        case 2: 
            listNotes();
            break;
        case 3:
        case 4:
            deleteNote();
            break;
        case 5:
            exit(0);
            break;
    }
    return 0;
}
struct file {
    char filename[50];
    char extension[5];
    char content[255];
};
void addNote()
{
    
    // FOR MAKING FOLDERS LATER ON
    // TODO
    // mkdir("test");
    struct file addFileStruct;
    FILE *fptr;

    char folderName[50];
    char folderPath[100];
    char fullPath[150];

    strcpy(addFileStruct.extension, ".txt");

    //Flush newline
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Get folder name
    printf("Dans quel dossier voulez-vous enregistrer la note ? ");
    fgets(folderName, sizeof(folderName), stdin);
    folderName[strcspn(folderName, "\n")] = '\0';

    sprintf(folderPath, "%s", folderName);
    _mkdir(folderPath);

    // Get note filename
    printf("Comment s'appelle cette note ? ");
    fgets(addFileStruct.filename, sizeof(addFileStruct.filename), stdin);
    addFileStruct.filename[strcspn(addFileStruct.filename, "\n")] = '\0';
    strcat(addFileStruct.filename, addFileStruct.extension);

    // Build full path
    sprintf(fullPath, "%s/%s", folderPath, addFileStruct.filename);

    // Get content
    printf("Que voulez-vous ecrire dans cette note ? ");
    fgets(addFileStruct.content, sizeof(addFileStruct.content), stdin);
    addFileStruct.content[strcspn(addFileStruct.content, "\n")] = '\0';

    fptr = fopen(fullPath, "w");
    fprintf(fptr, "%s", addFileStruct.content);
    fclose(fptr);

    reset();
}
void listNotes()
{
    system("dir /b");
    //need enter confirm here
    main();
    return 0;
}
void searchNotes()
{

}
void deleteNote()
{
    struct file rmFileStruct;

    strcpy(rmFileStruct.extension, ".txt");

    
    printf("Comment s'apelle le fichier? ");    

    //%s pour string
    scanf("%49s", rmFileStruct.filename);
    strcat(rmFileStruct.filename, rmFileStruct.extension);
    remove(rmFileStruct.filename);

    reset();
}
void reset()
{
    system("cls");
    main();
}