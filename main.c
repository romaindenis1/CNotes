#include <stdio.h>

int main ()
{
    printf("Welcome to notes app\n");
    printf("1) Add a note\n");
    printf("2) List notes\n");
    printf("3) Search note\n");
    printf("4) Delete a note\n");
    printf("Que voulez vous faire? ");

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

            break;
    }
    return 0;
}
void addNote()
{
    char filename[50];
    char extension[] = ".txt";
    char content[255];

    FILE *fptr;

    printf("Comment s'apelle cette note? ");    

    //%s pour string
    scanf("%s", &filename);
    
    strcat(filename, extension);
    fptr = fopen(filename, "w");

    printf("Que voulez vous ecrire dans cette note? "); 
    scanf("%s", &content);

    fprintf(fptr, content);

    fclose(fptr);
}
void listNotes()
{

}
void searchNotes()
{

}
void deleteNote()
{

    strcpy(rmFileStruct.extension, ".txt");

    strcat(rmFileStruct.filename, rmFileStruct.extension);
    printf("Comment s'apelle le fichier? ");    

    //%s pour string
    scanf("%49s", rmFileStruct.filename);
    remove(rmFileStruct.filename);

    system("cls");
    main();
}