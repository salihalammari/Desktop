#include "minishell.h"

int check_quote_s1(char *str)
{
    int i;
    int d1;
    int o1;

    i = 0;
    d1 = 0;
    o1 = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            d1++;
        if (str[i] == '\'')
            o1++;
        i++;
    }
    if ((d1 && o1) || (d1 % 2 != 0) || (o1 % 2 != 0))
    {
        printf("minishell: %s not a valid identifier\n", str);
        return (0);
    }
    else
        return (1);
}

int check_quotes(char *str1, char *str2)
{
    int i;
    int d1;
    int o1;
    int d2;
    int o2;

    i = 0;
    d1 = 0;
    o1 = 0;
    while (str1[i])
    {
        if (str1[i] == '\"')
            d1++;
        if (str1[i] == '\'')
            o1++;
        i++;
    }
    i = 0;
    d2 = 0;
    o2 = 0;
    while (str2[i])
    {
        if (str2[i] == '\"')
            d2++;
        if (str2[i] == '\'')
            o2++;
        i++;
    }
    if ((str1[0] == '\'' || str1[0] == '\"') || ((d1 % 2 == 0 && d1 > 2) \
    && (d2 % 2 == 0 && d2 > 2)) || (d2 % 2 != 0 && d1 % 2 != 0) \
    || (o1 % 2 == 0 && o2 % 2 != 0 && o1 != 0) || (o1 % 2 != 0 && o2 % 2 == 0 && o2 != 0)\
     || (d1 && o1))
    {
        printf("%s=%s: not a valid identifier\n", str1, str2);
        return (0);
    }
    else
        return (1);
}

char    *take_off_quotes(char *list)
{
    int i;
    int j;
    char    a;

    i = 0;
    if (!list)
        return (0);
    i = 0;
    if (list[0] != '\'' && list[0] != '\"')
    {
        while (list[i])
        {
            if (list[i] == '\'' || list[i] == '\"')
            {
                j = i;
                while (list[j + 1])
                {
                    list[j] = list[j + 1];
                    j++;
                }
                list[j] = '\0';
            }
            i++;
        }
    }
    i = 0;
    if (list[0] == '\'')
    {
        while (list[i])
        {
            if (list[i] == '\'')
            {
                j = i;
                while (list[j + 1])
                {
                    a = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = a;
                    j++;
                }
                list[j] = '\0';
            }
            i++;
        }
        return (list);
    }
    if (list[0] == '\"')
    {
        i = 0;
        while (list[i])
        {
            if (list[i] == '\"')
            {
                j = i;
                while (list[j + 1])
                {
                    a = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = a;
                    j++;
                }
                list[j] = '\0';
            }
            i++;
        }
    }
    i = 0;
    while (list[i])
    {
        if ((list[i] == '\'' || list[i] == '\"') && list[i + 1] == '\0')
        {
            list[i] = '\0';
            break ;
        }
        i++;
    }
    return (list);
}
