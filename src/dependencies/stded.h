#include <string.h>

char *strrev(char *string)
{
    if (string && *string)
    {
        char *b = string, *e = string + strlen(string) - 1;
        while (b < e)
        {
            char t = *b;
            *b++ = *e;
            *e-- = t;
        }
    }
    return string;
}

char encrypt_string2(char *string)
{

    char *ptr = string;

    int i = 0;

    while (string[i] != '\0')
    {

        *ptr = *ptr + 1;

        ptr++;

        i++;
    }

    strrev(string);
}

char decrypt_string2(char *string)
{

    char *ptr = string;

    int i = 0;

    strrev(string);

    while (string[i] != '\0')
    {

        *ptr = *ptr - 1;

        ptr++;

        i++;
    }
}

char encrypt_string(char *string)
{
    char *ptr = string;

    // strcpy(ptr2, string);

    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == '!' || string[i] == '~' || string[i] == '"' || string[i] == '}')
        {
            *ptr = *ptr + 0;
            i++;
            ptr++;
        }

        else
        {
            if (i % 17 == 1)
            {
                string[i] = '{';
                i++;
                ptr++;
            }

            else if (i % 11 == 2)
            {
                *ptr = *ptr - 2;
                i++;
                ptr++;
            }

            else if (i % 10 == 0)
            {
                *ptr = *ptr - 2;
                i++;
                ptr++;
            }

            else if (i % 9 == 0)
            {
                *ptr = *ptr - 2;
                i++;
                ptr++;
            }

            else if (i % 8 == 0)
            {
                string[i] = ';';
                i++;
                ptr++;
            }

            else if (i % 7 == 0)
            {
                *ptr = *ptr - 2;
                i++;
                ptr++;
            }

            else if (i % 6 == 0)
            {
                *ptr = *ptr - 2;
                i++;
                ptr++;
            }

            else if (i % 4 == 0)
            {
                *ptr = *ptr - 2;
                i++;
                ptr++;
            }

            else if (i % 3 == 0)
            {
                *ptr = *ptr - 2;
                i++;
                ptr++;
            }

            else if (i % 3 == 0)
            {
                string[i] = '0';
                i++;
                ptr++;
            }

            else if (i % 2 == 0)
            {
                *ptr = *ptr + 2;
                i++;
                ptr++;
            }
            else
            {

                *ptr = *ptr + 1;
                i++;
                ptr++;
            }
        }
    }
    strrev(string);

    char string2[500];

    strcpy(string2, string);

    char *ptr2 = string2;

    i = 0;
    while (string2[i] != '\0')
    {
        if (string2[i] == '!' || string2[i] == '~' || string2[i] == '"' || string2[i] == '}')
        {
            *ptr2 = *ptr2 + 0;
            i++;
            ptr2++;
        }

        else
        {
            if (i % 5 == 0)
            {
                string2[i]='?';
                i++;
                ptr2++;
            }

            else if (i % 3 == 0)
            {
                *ptr2 = *ptr - 2;
                i++;
                ptr2++;
            }

            else if (i % 2 == 0)
            {
                *ptr2 = *ptr2 + 2;
                i++;
                ptr2++;
            }
            else
            {

                *ptr2 = *ptr2 + 1;
                i++;
                ptr2++;
            }
        }
    }

    strcat(string, string2);

    strrev(string);

    char string3[500];

    strcpy(string3, string2);

    char *ptr3 = string3;

    i = 0;
    while (string3[i] != '\0')
    {
        if (string3[i] == '!' || string3[i] == '~' || string3[i] == '"' || string3[i] == '}')
        {
            *ptr3 = *ptr3 + 0;
            i++;
            ptr3++;
        }

        else
        {
            if (i % 15 == 2)
            {
                *ptr3 = *ptr3 - 2;
                i++;
                ptr3++;
            }

            else if (i % 6 == 0)
            {
                *ptr3 = *ptr3 - 1;
                i++;
                ptr3++;
            }

            else if (i % 5 == 0)
            {
                *ptr3 = *ptr3 - 1;
                i++;
                ptr3++;
            }

            else if (i % 4 == 0)
            {
                *ptr3 = *ptr3 - 1;
                i++;
                ptr3++;
            }

            else if (i % 3 == 0)
            {
                *ptr3 = *ptr3 - 1;
                i++;
                ptr3++;
            }

            else if (i % 2 == 0)
            {
                *ptr3 = *ptr3 + 1;
                i++;
                ptr3++;
            }
            else
            {
                *ptr3 = *ptr3 + 2;
                i++;
                ptr3++;
            }
        }
    }

    strcat(string, string3);

    strrev(string);
}