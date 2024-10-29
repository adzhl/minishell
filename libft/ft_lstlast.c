/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:29:28 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 11:35:40 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief the last node of the list. 
 * @param lst The beginning of the list.
 * @return Last node of the list
 * */
t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/* int	main(void)
{
	t_list *head = NULL;
	char *str1 = ft_strdup("Hello");
	char *str2 = ft_strdup("World");
	char *str3 = ft_strdup("Linked");

	ft_lstadd_back(&head, ft_lstnew(str1));
	ft_lstadd_back(&head, ft_lstnew(str2));
	ft_lstadd_back(&head, ft_lstnew(str3));

	t_list *last_node = ft_lstlast(head);
	if (last_node)
		printf("Last node content: %s\n", (char *)last_node->content);
	else
		printf("The list is empty.\n");

	t_list *current = head;
	while (current != NULL)
	{
		t_list *next = current->next;
		free(current->content);
		free(current);
		current = next;
	}

	return (0);
} */