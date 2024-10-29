/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:23:06 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 11:49:04 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds the node ’new’ at the beginning of the list.
 * @param lst The address of a pointer to the first link of
 a list.
 @param new The address of a pointer to the node to be
added to the list.
 * */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
void	print_list(t_list *head)
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
	t_list *lst;
	t_list *current;
	t_list *temp;
	t_list *new;

	lst = NULL;
	new = ft_lstnew("Hello");
	ft_lstadd_front(&lst, new);

	new = ft_lstnew("World");
	ft_lstadd_front(&lst, new);

	print_list(lst);

	current = lst;
	while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	return (0);
} */