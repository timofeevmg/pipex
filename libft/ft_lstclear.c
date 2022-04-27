/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:15:04 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:15:16 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*old;

	if (!lst)
		return ;
	while (*lst)
	{
		old = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = old;
	}
	*lst = NULL;
}
