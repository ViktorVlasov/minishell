/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:32:33 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/05 22:59:37 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **add_elem_in_arrayStr(char **src, char *elem)
{
    char **res;
    int i;
    
    i = 0;
    if (!src)
        return (NULL);
    if (!elem)
        return (src);
    while (src[i])
        i++;
    if (!(res = (char**)malloc(sizeof(char*) * (i + 2))))
        return (NULL);
    res[i + 1] = NULL;
    i = 0;
    while (src[i])
    {
        res[i] = src[i];
        i++;
    }
    if (!(res[i] = ft_strdup(elem)))
        return NULL;
    i++;
    res[i] = NULL;
    free(src);
    return (res);
}

char **delete_elem_in_arrayStr(char **src, char *elem)
{
    char **res;
    int i;
    int k;
    
    i = 0;
    if (!src)
        return (NULL);
    if (!elem)
        return (src);
    while (src[i])
        i++;
    if (!(res = (char**)malloc(sizeof(char*) * i)))
        return (NULL);
    i = 0;
    k = 0;
    while (src[i])
    {
        if (ft_strncmp(src[i], elem, ft_strlen(elem)) != 0)
            res[k++] = src[i++];
        else
            free(src[i++]);
    }
    res[k] = NULL;
    free(src);
    return (res);
}


/*
** boolFindPart = 1 - string from src includes elem
** boolFindPart = 0 - string from src equals elem
*/
char *find_elem_in_arrayStr(char **src, char *elem, int boolFindPart)
{
    int i;
    
    i = 0;
    if (!src)
        return (NULL);
    if (!elem)
        return (NULL);
    while (src[i])
    {
        if ((boolFindPart == 0) && (ft_strcmp(src[i], elem) == 0))
            return (src[i]);
        if ((boolFindPart == 1) && (ft_strncmp(src[i], elem, ft_strlen(elem)) == 0))
            return (src[i]);
        i++;
    }
    return (NULL);
}

/*
** example value of name_var - "HOME="
*/
char *get_value_from_var(char **envp, char *name_var)
{
    int i;
    char *result;
    
    i = 0;
    if (!envp)
        return (NULL);
    if (!name_var)
        return (NULL);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name_var, ft_strlen(name_var)) == 0)
        {
            result = envp[i] + ft_strlen(name_var);
            return (result);
        }
        i++;
    }
    return (NULL);
}