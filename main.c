#include <stdio.h>

int main ()
{
    printf("Welcome to notes app\n");
    printf("1) Add a note\n");
    printf("2) List notes\n");
    printf("3) Search note\n");
    printf("4) Delete a note\n");
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

            break;
        case 4:
            deleteNote();
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

    strcpy(rmFileStruct.extension, ".txt");

    printf("Comment s'apelle cette note? ");    
    //%s pour string
    scanf("%s", &filename);
    
    strcat(addFileStruct.filename, addFileStruct.extension);
    fptr = fopen(addFileStruct.filename, "w");

    printf("Que voulez vous ecrire dans cette note? "); 
    scanf("%49s", addFileStruct.content);

    fprintf(fptr, addFileStruct.content);

    fclose(fptr);
    system("cls");
    main();
}
void listNotes()
{

}
void searchNotes()
{

}
void deleteNote()
{
    struct file rmFileStruct;

    strcpy(rmFileStruct.extension, ".txt");

    strcat(rmFileStruct.filename, rmFileStruct.extension);
    printf("Comment s'apelle le fichier? ");    

    //%s pour string
    scanf("%49s", rmFileStruct.filename);
    remove(rmFileStruct.filename);

    system("cls");
    main();
}