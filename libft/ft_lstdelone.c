/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:18:01 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 11:49:18 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief as a parameter a node and frees the memory of
 * the node’s content using the function ’del’ given
 * as a parameter and free the node. The memory of
 * ’next’ must not be freed.
 * @param lst The node to free.
 * @param del The address of the function used to delete
 * the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
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

	ft_lstdelone(node1, del_content);

	printf("\nAfter freeing node1:\n");
	printf("Node2 content: %s\n", (char *)node2->content);

	ft_lstdelone(node2, del_content);

	printf("\nAfter freeing node2, the list is empty.\n");

	return (0);
} */