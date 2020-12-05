/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:42:37 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/05 19:09:30 by efumiko          ###   ########.fr       */
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

void change_oldpwd(t_data *data, char *old_pwd)
{   
    char *tmp;
     
    if (find_elem_in_arrayStr(data->envp, "OLDPWD=", 1))
        data->envp = delete_elem_in_arrayStr(data->envp, "OLDPWD=");
    tmp = old_pwd;
    old_pwd = ft_strjoin("OLDPWD=", old_pwd);
    data->envp = add_elem_in_arrayStr(data->envp, old_pwd);
    free(tmp);
    free(old_pwd);
}

void change_pwd(t_data *data)
{
    char *pwd;
    char *tmp;

    pwd = getcwd(NULL, 0);
    if (find_elem_in_arrayStr(data->envp, "PWD=", 1))
        data->envp = delete_elem_in_arrayStr(data->envp, "PWD=");
    tmp = pwd;
    pwd = ft_strjoin("PWD=", pwd);
    data->envp = add_elem_in_arrayStr(data->envp, pwd);
    free(pwd);
    free(tmp);
}

static int		path_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (errno);
}

int without_arguments_handler(t_data *data, char *old_pwd)
{
    char *home_path;

    home_path = get_value_from_var(data->args, "HOME=");
    if (!home_path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (errno); //return -1
	}
    if (ft_strlen(home_path) == 0)
        change_oldpwd(data, old_pwd);
    else if (chdir(home_path) == 0)
    {
        change_oldpwd(data, old_pwd);
        change_pwd(data);  
    }
    else
        path_error(home_path);
    return (0);
}

int minus_handler(t_data *data)
{
    
}

int tilda_handler(t_data *data)
{
    
}

int ft_cd(t_data *data)
{
    char *old_pwd;
    char *home;

    old_pwd = getcwd(NULL, 0);
    if (!data->args[1])
    {
        without_arguments_handler(data, old_pwd);
    }
    if (ft_strcmp(data->args[1], "-\0"))
        return minus_handler(data);
    else if (ft_strcmp(data->args[1], "~\0"))
        return tilda_handler(data);
    else
    {
        if (chdir(data->args[1]) == 0)
        {
            change_oldpwd(data, old_pwd);
            change_pwd(data);
        }
        else
            return (path_error(data->args[1]));
        return (0);
    }
}