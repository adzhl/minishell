/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:43:45 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 11:39:05 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes and frees the given node and every successor of that node,
 using the function ’del’ and free(3).
 Finally, the pointer to the list must be set to
 NULL. 
 @param lst The address of a pointer to a node.
 @param del The address of the function used to delete
the content of the node.
 *  */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_node;
	t_list	*next_node;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	current_node = *lst;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		del(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*lst = NULL;
}

/* void	del_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *node1 = malloc(sizeof(t_list));
	char *str1 = ft_strdup("Hello");
	node1->content = str1;
	node1->next = NULL;

	t_list *node2 = malloc(sizeof(t_list));
	char *str2 = ft_strdup("World");
	node2->content = str2;
	node2->next = NULL;

	node1->next = node2;

	printf("Before freeing:\n");
	printf("Node1 content: %s\n", (char *)node1->content);
	printf("Node2 content: %s\n", (char *)node2->content);

	ft_lstclear(node1, del_content);

	printf("\nAfter freeing node1:\n");
	printf("Node2 content: %s\n", (char *)node2->content);

	ft_lstclear(node2, del_content);

	printf("\nAfter freeing node2, the list is empty.\n");

	return (0);
} */