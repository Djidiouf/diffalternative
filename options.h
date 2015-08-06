#include <ctype.h>
#define YDISPLAY 32 //lenght maximum of every line

/*
HERE WE HAVE ALL OPTION FUNCTIONS OF OUR PROGRAMM
*/
//int opt_s (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
char* str_to_lower(const char* chaine);
char* str_onespace (const char* chaine);
char* str_onetab (const char* chaine);
char* str_ignore_blank(char * chaine);
void opt_help ();
int opt_s (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
int opt_q (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
void opt_y (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2);
char* str_tabtospace (const char* chaine);

/********************************************************
FUNCTION str_to_lower OPTION -i
*********************************************************/
char* str_to_lower(const char* chaine)
{
	char* string = NULL;
	if (chaine != NULL)
	{
		//we allocate a string of same size of we had in chaine
		string = malloc ((strlen (chaine) + 1) * sizeof (*string));

		int i;
		if (string != NULL)
		{
			//for each character, we lower it and rewrite it in our string
			for (i=0;chaine[i];i++)
			{
				string[i] = tolower(chaine[i]);
			}
        string[i] = '\0';
		}
	}
	return string;
}
/********************************************************
ENDOF: FUNCTION str_to_lower OPTION -i
*********************************************************/


/********************************************************
FUNCTION str_onespace OPTION -b
*********************************************************/
char* str_onespace (const char* chaine)
{
    char* onespace = NULL;

    if (chaine != NULL)
    {
        //allocation of the same size of memory of 'chaine'
        onespace = malloc ((strlen (chaine) + 1) * sizeof (*onespace));
        if (onespace != NULL)
        {
            int i;
            int j;
            int space = 0; //number of space

            //for each character of our string
            for (i=0,j=0;chaine[i];i++)
            {
                //we test if every char is a space, if it is a space, we test the
                //value of 'space' which indicates if the previous char was a space too
                //if it wasn't a space, we put 1 in 'space'
                if (chaine[i] == ' ') // if the car is a space
                {
                    if (space == 0)
                    {
                        onespace[j] = chaine[i];
                        space = 1;
                        j++;
                        //if space = 0, we copy this one and set space = 1
                        //so if space = 1, we just skip the copy of i in j
                    }
                }
                else //if the car is not a space, we jsute copy it
                {
                    onespace[j] = chaine[i];
                    space = 0;
                    j++;
                }
            }

            onespace[j] = '\0'; //last char of our string must be a \0
        }
        else //test our malloc
        {
            fprintf (stderr, "Allocation impossible\n");
            exit (EXIT_FAILURE);
        }
    }
    return onespace; //we return the string tweaked
}
/********************************************************
ENDOF: FUNCTION str_onespace OPTION -b
*********************************************************/


/********************************************************
FUNCTION str_onetab OPTION -E
*********************************************************/
char* str_onetab (const char* chaine)
{
    char* onetab = NULL;

    if (chaine != NULL)
    {
        onetab = malloc ((strlen (chaine) + 1) * sizeof (*onetab));
        if (onetab != NULL)
        {
            int i;
            int j;
            int tabulation = 0;

            for (i=0,j=0;chaine[i];i++)
            {
                if (chaine[i] == '\t')
                {
                    if (tabulation == 0)
                    {
                        onetab[j] = chaine[i];
                        tabulation = 1;
                        j++;
                    }
                }
                else
                {
                    onetab[j] = chaine[i];
                    tabulation = 0;
                    j++;
                }
            }
            onetab[j] = '\0';
        }
        else //if our malloc is NULL, it's an error
        {
            fprintf (stderr, "Allocation impossible\n");
            exit (EXIT_FAILURE);
        }
    }
    return onetab;
}
/********************************************************
ENDOF: FUNCTION str_onetab OPTION -E
*********************************************************/


/********************************************************
FUNCTION str_ignore_blank OPTION -w
*********************************************************/

char* str_ignore_blank(char * chaine)
{
    char * result = NULL;

    if (chaine != NULL)
    {
        int length;
        length = strlen(chaine);
        result = malloc((length + 1) * sizeof(char));
        if (result != NULL)
        {
            int i;
            int j = 0;
            for(i = 0; i != length; i++)
            {
                if (chaine[i] != ' ' && chaine[i] != '\t')
                {
                    result[j] = chaine[i];
                    j++;
                }
            }
            result[j] = '\0';
            free(chaine);
        }
    }
    return result;
}
/********************************************************
ENDOF: FUNCTION str_ignore_blank OPTION -w
*********************************************************/


/********************************************************
FUNCTION opt_help OPTION --help
*********************************************************/
void opt_help ()
{
    printf("Options available:\n");
    printf("  -b  --ignore-space-change \tIgnore changes in the amount of white space.\n");
    printf("  -i  --ignore-case \t\tIgnore case differences in file contents.\n");
    printf("  -E  --ignore-tab-expansion \tIgnore changes due to tab expansion.\n");
    printf("  -N  --new-file \t\tTreat absent files as empty.\n");
    printf("  -v  --version \t\tOutput version info.\n");
    printf("  -w  --ignore-all-space \tIgnore all white space.\n");
    printf("  -t  --expand-tabs \t\tExpand tabs to spaces in output.\n");
    printf("  -q  --brief \t\t\tOutput only whether files differ.\n");
    printf("  -y  --side-by-side \t\tOutput in two columns.\n");
    printf("  -s  --report-identical-files \tReport when two files are the same.\n");
    printf("  --help \t\t\tOutput this help.\n");
}
/********************************************************
ENDOF: FUNCTION opt_help OPTION --help
*********************************************************/


/********************************************************
FUNCTION opt_q OPTION -q
*********************************************************/
int opt_q (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2)
{
	int briefresult = 0;
	// i is the index of the line we're processing in chaine_tab1.
	int i;
	// j is the index of the line we're processing in chaine_tab2.
	int j = 0;

	//Process each line of chaine_tab1 and do our job
	for (i=0; i<nb1; i++)
	{
		//Indicates if a matching line was found in chaine_tab2 (true = 1)
		int found = 0;
		//Indicates the number of lines we've skipped in chaine_tab2 before finding the matching line.
		int skipped = 0;

		//we process each line of chaine_tab2 (starting from the j-th one)
		//until we either find a matching line or the end of file
		while (j<nb2 && found == 0)
		{
			// Compare both lines
			if(strcmp(chaine_tab1[i], chaine_tab2[j]) == 0)
			{
				found = 1;
			}
			else
			{
			    skipped++;
			}
			j++;
		}

		//Now process the result:
		if (found == 1)
		{
			//Print lines we skipped (from j-skipped to j)
			int a;
			for (a=j-skipped;a<j;a++)
			{
				briefresult = 1;
			}
		}
		else
		{
			//Only print the line from chaine_tab1, and rollback the
			//index j because we'll have to read those lines again.
			j = j-skipped;
			briefresult = 1;
		}
	}

	//Time to print all lines of chaine_tab2 if file2 have more
	//line than file1: these are all new.
	while (j < nb2)
    {
        j++;
        briefresult = 1;
    }

    return briefresult;

}
/********************************************************
ENDOF: FUNCTION opt_q OPTION -q
*********************************************************/


/********************************************************
FUNCTION opt_s OPTION -s
*********************************************************/
int opt_s (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2)
{
	int same = 0;
	// i is the index of the line we're processing in chaine_tab1.
	int i;
	// j is the index of the line we're processing in chaine_tab2.
	int j = 0;

	//Process each line of chaine_tab1 and do our job
	for (i=0; i<nb1; i++)
	{
		//Indicates if a matching line was found in chaine_tab2 (true = 1)
		int found = 0;
		//Indicates the number of lines we've skipped in chaine_tab2 before finding the matching line.
		int skipped = 0;

		//we process each line of chaine_tab2 (starting from the j-th one)
		//until we either find a matching line or the end of file
		while (j<nb2 && found == 0)
		{
			// Compare both lines
			if(strcmp(chaine_tab1[i], chaine_tab2[j]) == 0)
			{
				found = 1;
			}
			else
			{
			    skipped++;
			}
			j++;
		}

		//Now process the result:
		if (found == 1)
		{
			//Print lines we skipped (from j-skipped to j)
			int a;
			for (a=j-skipped;a<j;a++)
			{
				same = 1;
			}
		}
		else
		{
			//Only print the line from chaine_tab1, and rollback the
			//index j because we'll have to read those lines again.
			j = j-skipped;
			same = 1;
		}
	}

	//Time to print all lines of chaine_tab2 if file2 have more
	//line than file1: these are all new.
	while (j < nb2)
    {
        j++;
        same = 1;
    }

    return same;

}
/********************************************************
ENDOF: FUNCTION opt_s OPTION -s
*********************************************************/


/********************************************************
FUNCTION opt_y OPTION -y
*********************************************************/
void opt_y (char** chaine_tab1, int nb1, char** chaine_tab2, int nb2)
{
    char * buffer = NULL;
	buffer = (char*)malloc(YDISPLAY+1*sizeof(char));
    if (buffer == NULL)
    {
        fprintf(stderr,"Allocation impossible\n");
        exit(EXIT_FAILURE);
    }

	// i is the index of the line we're processing in chaine_tab1.
	int i;
	// j is the index of the line we're processing in chaine_tab2.
	int j = 0;

	//Process each line of chaine_tab1 and do our job
	for (i=0; i<nb1; i++)
	{
		//Indicates if a matching line was found in chaine_tab2 (true = 1)
		int found = 0;
		//Indicates the number of lines we've skipped in chaine_tab2 before finding the matching line.
		int skipped = 0;

		//we process each line of chaine_tab2 (starting from the j-th one)
		//until we either find a matching line or the end of file
		while (j<nb2 && found == 0)
		{
			// Compare both lines
			if(strcmp(chaine_tab1[i], chaine_tab2[j]) == 0)
			{
				found = 1;
			}
			else
			{
			    skipped++;
			}
			j++;
		}

		//Now process the result:
		if (found == 1)
		{
			//Print lines we skipped (from j-skipped to j)
			int a;
			for (a=j-skipped;a<j;a++)
			{
				strncpy (buffer, chaine_tab2[a-1], YDISPLAY);
				printf("\t\t\t\t> %s\n", buffer);
			}

			//Print the matched line
			strncpy (buffer, chaine_tab1[i], YDISPLAY);
            if (strlen(buffer) < YDISPLAY)
			{
			    int b;
			    for (b=strlen(buffer);b < YDISPLAY;b++)
			    {
			        buffer[b] = ' ';
			    }
			    buffer[b]='\0';
			}
			printf("%s= %s\n", buffer, buffer);
		}
		else
		{
			//Only print the line from chaine_tab1, and rollback the
			//index j because we'll have to read those lines again.
			strncpy (buffer, chaine_tab1[i], YDISPLAY);
			if (strlen(buffer) < YDISPLAY)
			{
			    int b;
			    for (b=strlen(buffer);b < YDISPLAY;b++)
			    {
			        buffer[b] = ' ';
			    }
			    buffer[b]='\0';
			}
			printf("%s<\n", buffer);
			j = j-skipped;
		}
	}

	//Time to print all lines of chaine_tab2 if file2 have more
	//line than file1: these are all new.
	while (j < nb2)
    {
        strncpy (buffer, chaine_tab2[j], YDISPLAY);
        if (strlen(buffer) < YDISPLAY)
        {
            int b;
            for (b=strlen(buffer);b < YDISPLAY;b++)
            {
                buffer[b] = ' ';
            }
            buffer[b]='\0';
        }
        printf("\t\t\t\t> %s\n", buffer);
        j++;
    }

    free(buffer);
}
/********************************************************
ENDOF: FUNCTION opt_y OPTION -y
*********************************************************/


/********************************************************
FUNCTION str_tabtospace OPTION -t
*********************************************************/
char* str_tabtospace (const char* chaine)
{
    int i;
    int k; //number of tabulations
    for (i=0,k=0;chaine[i];i++)
    {
        if (chaine[i] == '\t')
        {
            k++;
        }
    }

    char* tabtospace = NULL;
    if (chaine != NULL)
    {
        tabtospace = malloc ((strlen (chaine) + 1 + k*3) * sizeof (*tabtospace));
        if (tabtospace != NULL)
        {
            int j;

            for (i=0,j=0;chaine[i];i++)
            {
                if (chaine[i] == '\t')
                {
                    tabtospace[j] = ' ';
                    tabtospace[j+1] = ' ';
                    tabtospace[j+2] = ' ';
                    tabtospace[j+3] = ' ';
                    j=j+4;
                }
                else
                {
                    tabtospace[j] = chaine[i];
                    j++;
                }
            }
            tabtospace[j] = '\0';
        }
        else //if our malloc is NULL, it's an error
        {
            fprintf (stderr, "Allocation impossible\n");
            exit (EXIT_FAILURE);
        }
    }
    return tabtospace;
}
/********************************************************
ENDOF: FUNCTION str_tabtospace OPTION -t
*********************************************************/
