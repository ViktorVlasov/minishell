/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 00:03:46 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/31 00:27:41 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		free_listof_redirects(t_rdata **lst)
{
	t_rdata	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		if ((*lst)->file_name)
			free((*lst)->file_name);
		if ((*lst)->redir_type)
			free((*lst)->redir_type);
		if ((*lst)->red_fd >= 0)
			close((*lst)->red_fd);
		tmp = *lst;
		*lst = tmp->next;
		free(tmp);
	}
	*lst = NULL;
}

void		ft_redadd_back(t_rdata **lst, t_rdata *new)
{
	t_rdata	*lst_back;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		lst_back = *lst;
		while (lst_back->next)
			lst_back = lst_back->next;
		lst_back->next = new;
	}
	else
		*lst = new;
}

t_rdata		*ft_init_red(void)
{
	t_rdata	*new;

	new = (t_rdata*)malloc(sizeof(t_rdata));
	if (new == NULL)
		return (NULL);
	new->file_name = NULL;
	new->next = NULL;
	new->redir_type = NULL;
	new->red_fd = -2;
	return (new);
}
