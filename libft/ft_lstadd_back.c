/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:52:56 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 11:10:29 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds the node ’new’ at the end of the list.
 * 
 * @param lst The address of a pointer to the first link of
a list.
 * @param new The address of a pointer to the node to be
added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

/* void	print_list(t_list *head)
{
	t_list	*current;

	current = head;
	printf("Linked List: ");
	while (current != NULL)
	{
		printf("%s ", (char *)current->content);
		current = current->next;
	}
	printf("\n");
}

int	main(void)
{
	t_list *head = NULL;

	char *str1 = ft_strdup("Hello");
	char *str2 = ft_strdup("World");
	char *str3 = ft_strdup("Linked");

	ft_lstadd_back(&head, ft_lstnew(str1));
	ft_lstadd_back(&head, ft_lstnew(str2));
	ft_lstadd_back(&head, ft_lstnew(str3));

	print_list(head);

	t_list *current = head;
	while (current != NULL)
	{
		t_list *next = current->next;
		free(current);
		current = next;
	}

	return (0);
} */