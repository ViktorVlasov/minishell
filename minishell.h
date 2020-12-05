/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:02 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/05 19:24:09 by ddraco           ###   ########.fr       */
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
char        **ft_big_strdup(char **arr, size_t size, int flag);
int		    get_amount_line(char **lines);
void	    *ft_realloc(void *ptr, int size, int newsize);

/* 
* Commands
*/

void        ft_echo(char **args);
void        ft_pwd();
void ft_env(char **envp);

#endif