/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:02 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/07 22:48:53 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 5
# include "libft/libft.h"
# include "errno.h" 

typedef struct      s_data
{
    char            **envp;
    char            **args;
}                   t_data;

char        **parser(char *line, t_data vars);
int			get_next_line(int fd, char **line);
char        **semicolon(char *line);
char        **ft_realloc_2arr(char **arr, size_t prev_size ,size_t size);
int		    get_amount_line(char **lines);
void	    *ft_realloc(void *ptr, int size, int newsize);
char        **add_elem_in_arrayStr(char **src, char *elem);
char        **delete_elem_in_arrayStr(char **src, char *elem);
char        *find_elem_in_arrayStr(char **src, char *elem, int boolFindPart);
char        *get_value_from_var(char **envp, char *name_var);
char        **ft_strdup_2arr(char **arr);
/* 
* Commands
*/

void        ft_echo(char **args);
void        ft_pwd();
void        ft_env(char **envp);
int         ft_export(char **envp);
int         ft_cd(t_data *data);

#endif