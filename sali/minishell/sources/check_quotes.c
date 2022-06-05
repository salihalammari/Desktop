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

static void    count_quotes(char *str1, int d, int o)
{
    int i;

    i = 0;
    while (str1[i])
    {
        if (str1[i] == '\"')
            d++;
        if (str1[i] == '\'')
            o++;
        i++;
    }
}

int check_quotes(char *str1, char *str2)
{
    int d1;
    int o1;
    int d2;
    int o2;

    d1 = 0;
    o1 = 0;
    count_quotes(str1, d1, o1);
    d2 = 0;
    o2 = 0;
    count_quotes(str2, d2, o2);
    if ((str1[0] == '\'' || str1[0] == '\"') || ((d1 % 2 == 0 && d1 > 2) \
        && (d2 % 2 == 0 && d2 > 2)) || (d2 % 2 != 0 && d1 % 2 != 0) \
        || (o1 % 2 == 0 && o2 % 2 != 0 && o1 != 0) \
        || (o1 % 2 != 0 && o2 % 2 == 0 && o2 != 0) || (d1 && o1))
    {
        printf("%s=%s: not a valid identifier\n", str1, str2);
        return (0);
    }
    else
        return (1);
}
