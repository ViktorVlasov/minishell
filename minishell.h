/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:02 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/12 23:05:15 by ddraco           ###   ########.fr       */
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
    int             err_status;
}                   t_data;

char        **parser(char *line, t_data *vars);
int			get_next_line(int fd, char **line);
char        **semicolon(char *line);
char        **ft_realloc_2arr(char **arr, size_t prev_size ,size_t size);
int		    get_amount_line(char **lines);
void	    *ft_realloc(void *ptr, int size, int newsize);
char        **add_elem_in_arrayStr(char **src, char *elem);
char        **delete_elem_in_arrayStr(char **src, char *elem, int boolFindPart);
char        *find_elem_in_arrayStr(char **src, char *elem, int boolFindPart);
char        *get_value_from_var(char **envp, char *name_var);
char        **ft_strdup_2arr(char **arr);
void	    ft_free_array(char ***ar);
int         in_screening(char *line, int symb_id);
char        *add_char(char *str, char symb);
char        *variable_handler(char *str, char *dst, int *iterator, t_data *vars);
char        *one_comma_worker(int *i, char *buffer, char *str);
char        *two_comma_worker(int *i, char *buffer, char *str, t_data *vars);
/* 
* Commands
*/

void        ft_echo(char **args);
void        ft_pwd();
void        ft_env(char **envp);
int         ft_export(t_data *data);
int         ft_cd(t_data *data);
int         ft_exit(t_data *data);

#endif