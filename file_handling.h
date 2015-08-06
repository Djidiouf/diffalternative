#define MAX 100000 //size maximum of every line

/*
HERE WE HAVE ALL FILE HANDLING FUNCTIONS
*/
int nombre_ligne(char* src);
char** file_to_tab(char* src, int nb);

/********************************************************
FUNCTION nombre_ligne
it returns the number of lines of a file put in argument
*********************************************************/
int nombre_ligne(char* src)
{
    FILE* fichier = NULL;
    fichier = fopen(src,"r");

    char chaine[MAX] = "";
    int nbligne = 0;

    if (fichier != NULL)
    {
        while (fgets(chaine, MAX, fichier) != NULL)
        {
            nbligne++;
        }
    }

    fclose(fichier);
    return nbligne;
}
/********************************************************
ENDOF: FUNCTION nombre_ligne
*********************************************************/


/********************************************************
FUNCTION file_to_tab
put all content of a file in a tab
*********************************************************/
char** file_to_tab(char* src, int nb)
{
    //allocation in memory of chaine_tab
    char** chaine_tab = NULL;
    chaine_tab = (char**)malloc(nb*sizeof(char*));
    if (chaine_tab == NULL)
    {
        fprintf(stderr,"Allocation impossible\n");
        exit(EXIT_FAILURE);
    }

    //Open src1 which is a file in this draft
    FILE* fichier = NULL;
    fichier = fopen(src,"r");

    //allocation of every line in memory
    if (fichier != NULL)
    {
        char buffer[MAX];
        char *chaine = buffer;
        int i;
        for (i=0;i<nb;i++)
        {
            chaine = fgets(chaine, MAX, fichier); //each line is read
            if (chaine == NULL)
            {
                fprintf(stderr,"Erreur lors de la lecture de la ligne\n");
                exit(EXIT_FAILURE);
            }
            chaine_tab[i] = NULL;
            chaine_tab[i] = (char*)malloc((strlen(chaine))*sizeof(char)+1);

            //malloc return the address of the first octet allocated
            //it returns NULL if there was no allocation, so we test it
            if (chaine_tab[i] == NULL)
            {
                fprintf(stderr,"Allocation impossible\n");
                exit(EXIT_FAILURE);
            }

            strcpy(chaine_tab[i],chaine); //copy of chaine in our table[i]

            //we must change the last character if we want the last line to
            //be considered in the same way of the others in our comparisons
            if (chaine_tab[i][strlen(chaine)-1] == '\n')
            {
                chaine_tab[i][strlen(chaine)-1]='\0';
            }
        }
    }
    fclose(fichier);
    return chaine_tab;
}
/********************************************************
ENDOF: FUNCTION file_to_tab
*********************************************************/
