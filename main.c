#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"
#include "options.h"

/*
Diff en C maison
*/



/***********************************************************
MAIN
***********************************************************/
int main(int argc, char** argv)
{
    //check the number of argument, less than 2 is impossible
    if (argc < 2)
    {
        printf("Not enough arguments.");
        return 1;
    }


    /*****************************************************
    Initialisation OPTIONS
    ******************************************************/
    int option_i = 0;
    int option_b = 0;
    int option_E = 0;
    int option_v = 0;
    int option_h = 0;
    int option_w = 0;
    int option_N = 0;
    int option_t = 0;

    //these options must call its functions after string behavior options
    int option_s = 0;
    int option_q = 0;
    int option_y = 0;


	//How many options do we have?
	int k;
	int cpt = 0; //total number of options
	for(k=1;k<argc;k++)
	{
			if(strcmp(argv[k], "-i") == 0 || strcmp(argv[k], "--ignore-case") == 0)
			{
				option_i = 1;
				cpt++;
			}
			if(strcmp(argv[k], "-b") == 0 || strcmp(argv[k], "--ignore-space-change") == 0)
			{
				option_b = 1;
				cpt++;
			}
			if(strcmp(argv[k], "-E") == 0 || strcmp(argv[k], "--ignore-tab-expansion") == 0)
			{
				option_E = 1;
				cpt++;
			}
			if(strcmp(argv[k], "-v") == 0  || strcmp(argv[k], "--version") == 0)
			{
				option_v = 1; //useless because of return 0;
				printf("%s: Version 2012.01.13.1727\n\n",argv[0]);
				printf("Written by Antoine Lang-Cavelier\n");
				return 0; //end of the programm now
			}
			if(strcmp(argv[k], "--help") == 0)
			{
				option_h = 1; //useless because of return 0;
                printf("Syntax:\n");
                printf("%s [OPTIONS] fichier1 fichier2\n\n",argv[0]);
				opt_help(); //we have a function to display the help
				return 0; //end of the programm now
			}
			if(strcmp(argv[k], "-w") == 0 || strcmp(argv[k], "--ignore-all-space") == 0)
			{
				option_w = 1;
				cpt++;
			}
			if(strcmp(argv[k], "-N") == 0 || strcmp(argv[k], "--new-file") == 0)
			{
				option_N = 1;
				cpt++;
				if (argv[2] == NULL)
				{
				    printf("%s: No differences between 2 empty files.\n",argv[0]);
				    return 0;
				}
			}
            if(strcmp(argv[k], "-t") == 0 || strcmp(argv[k], "--expand-tabs") == 0)
			{
				option_t = 1;
				cpt++;
			}
            if(strcmp(argv[k], "-s") == 0 || strcmp(argv[k], "--report-identical-files") == 0)
			{
				option_s = 1;
				cpt++;
			}
			if(strcmp(argv[k], "-q") == 0  || strcmp(argv[k], "--brief") == 0)
			{
				option_q = 1;
				cpt++;
			}
            if(strcmp(argv[k], "-y") == 0  || strcmp(argv[k], "--side-by-side") == 0)
			{
				option_y = 1;
				cpt++;
			}
	}
	//we increase our arguments by the number of different options selected
	//because after that, we will use argv[1] and argv[2]
	argv[1] = argv[cpt+1]; //first file
	argv[2] = argv[cpt+2]; //second file
    /*****************************************************
    ENDOF: Initialisation OPTIONS
    ******************************************************/

    if (option_N == 0 && argv[2] == NULL)
    {
        printf("%s: Missing operand after '%s'.\n",argv[0],argv[1]);
        printf("%s: Try `%s --help' for more information.\n",argv[0],argv[0]);
        return 0;
    }

    //we rename our two arguments to avoid type issues (char* vs char**)
    char* src1 = argv[1];
    char* src2 = argv[2];


    /*****************************************************
    ALGO DIFF;
    ******************************************************/
    //call of our function nombre_ligne();
    int nb1 = nombre_ligne(src1); //ask total lines of src1 and put it in nb1
    int nb2 = nombre_ligne(src2); //ask total lines of src2 and put it in nb2

    //beginning of the comparison loop in order to print the diff

    //call of our function file_to_tab();
    char** chaine_tab1 = file_to_tab(src1, nb1); //put our file1 in a tab of string
    char** chaine_tab2 = file_to_tab(src2, nb2); //put our file2 in a tab of string


	/*****************
    Option -i
    not case sensitive
    *****************/
	if (option_i == 1)
	{
	    int i;
	    for (i=0; i<nb1; i++)
	    {
	        chaine_tab1[i] = str_to_lower(chaine_tab1[i]);
	    }
	    int j;
	    for (j=0; j<nb2; j++)
	    {
	        chaine_tab2[j] = str_to_lower(chaine_tab2[j]);
	    }
	}
    /*****************
    ENDOF: Option -i
    *****************/


	/*****************
    Option -b
    no multi space
    *****************/
	if (option_b == 1)
	{
	    int i;
	    for (i=0; i<nb1; i++)
	    {
	        chaine_tab1[i] = str_onespace(chaine_tab1[i]);
	    }
	    int j;
	    for (j=0; j<nb2; j++)
	    {
	        chaine_tab2[j] = str_onespace(chaine_tab2[j]);
	    }
	}
    /*****************
    ENDOF: Option -b
    *****************/


	/*****************
    Option -E
    no multi tab
    *****************/
	if (option_E == 1)
	{
	    int i;
	    for (i=0; i<nb1; i++)
	    {
	        chaine_tab1[i] = str_onetab(chaine_tab1[i]);
	    }
	    int j;
	    for (j=0; j<nb2; j++)
	    {
	        chaine_tab2[j] = str_onetab(chaine_tab2[j]);
	    }
	}
    /*****************
    ENDOF: Option -E
    *****************/


	/*****************
    Option -w
    skip blank characters
    *****************/
	if (option_w == 1)
	{
	    int i;
	    for (i=0; i<nb1; i++)
	    {
	        chaine_tab1[i] = str_ignore_blank(chaine_tab1[i]);
	    }
	    int j;
	    for (j=0; j<nb2; j++)
	    {
	        chaine_tab2[j] = str_ignore_blank(chaine_tab2[j]);
	    }
	}
    /*****************
    ENDOF: Option -w
    *****************/


	/*****************
    Option -t
    change tab in space
    *****************/
	if (option_t == 1)
	{
	    int i;
	    for (i=0; i<nb1; i++)
	    {
	        chaine_tab1[i] = str_tabtospace(chaine_tab1[i]);
	    }
	    int j;
	    for (j=0; j<nb2; j++)
	    {
	        chaine_tab2[j] = str_tabtospace(chaine_tab2[j]);
	    }
	}
    /*****************
    ENDOF: Option -t
    *****************/


	/*****************
    Option -s
    report-identical-files
    *****************/
	if (option_s == 1)
	{
	    if (opt_s(chaine_tab1, nb1, chaine_tab2, nb2) == 0)
	    {
	        printf("Files %s and %s are identical.",src1,src2);

            free(chaine_tab1);
            free(chaine_tab2);
	        return 0;
	    }
	}
    /*****************
    ENDOF: Option -s
    *****************/


	/*****************
    Option -q
    brief diff
    MUST BE AFTER STRING BEHAVIOR OPTIONS
    *****************/
	if (option_q == 1)
	{
	    if (opt_q(chaine_tab1, nb1, chaine_tab2, nb2) != 0)
	    {
	        printf("Files %s and %s differ.", src1, src2);
	    }

        free(chaine_tab1);
        free(chaine_tab2);
	    return 0;
	}
    /*****************
    ENDOF: Option -q
    *****************/


	/*****************
    Option -y
    side by side diff
    MUST BE AFTER STRING BEHAVIOR OPTIONS
    *****************/
	if (option_y == 1)
	{
	    printf("Side by side diff of %s with %s:\n\n",src1,src2);
	    opt_y(chaine_tab1, nb1, chaine_tab2, nb2);

        free(chaine_tab1);
        free(chaine_tab2);
	    return 0;
	}
    /*****************
    ENDOF: Option -y
    *****************/


	printf("Diff of %s with %s:\n\n",src1,src2);

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
				printf("> %s\n", chaine_tab2[a-1]);
			}
            //Print the matched line
			printf("= %s\n", chaine_tab1[i]);



		}
		else
		{
			//Only print the line from chaine_tab1, and rollback the
			//index j because we'll have to read those lines again.
			printf("< %s\n", chaine_tab1[i]);
			j = j-skipped;

		}
	}


	//Time to print all lines of chaine_tab2 if file2 have more
	//line than file1: these are all new.
	while (j < nb2)
    {
        printf("> %s\n", chaine_tab2[j]);
        j++;
    }

    //deallocation of our mallocs
    free(chaine_tab1);
    free(chaine_tab2);
    /*****************************************************
    ENDOF: ALGO DIFF;
    ******************************************************/

    return 0;
}
/***********************************************************
ENDOF: MAIN
***********************************************************/
