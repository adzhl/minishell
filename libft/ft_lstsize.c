/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:08:43 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 11:32:48 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of nodes in a list.
 * @param lst The beginning of the list.
 * @return The length of the list
 *  */
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/* int	main(void)
{
	int d1 = 1;
	int d2 = 2;
	int d3 = 3;
	int d4 = 4;

	t_list *head = ft_lstnew(&d1);
	head->next = ft_lstnew(&d2);
	head->next->next = ft_lstnew(&d3);
	head->next->next->next = ft_lstnew(&d4);

	int size = ft_lstsize(head);

	printf("The size of the linked list is: %d\n", size);

	t_list *current = head;
	t_list *next_node;
	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	return (0);
} */