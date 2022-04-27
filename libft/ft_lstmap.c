/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epilar <epilar@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:15:09 by epilar            #+#    #+#             */
/*   Updated: 2022/04/27 14:15:14 by epilar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*new_e;

	if (!lst || !f)
		return (NULL);
	new_l = NULL;
	while (lst)
	{
		new_e = ft_lstnew(f(lst->content));
		if (new_e == NULL)
		{
			ft_lstclear(&new_l, del);
			return (NULL);
		}
		ft_lstadd_back(&new_l, new_e);
		lst = lst->next;
	}
	return (new_l);
}
