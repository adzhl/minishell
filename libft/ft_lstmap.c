/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:23:46 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:01:49 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates the list ’lst’ and applies the function’f’ on the content 
 * of each node. Creates a new list resulting of the successive applications 
 * of the function ’f’. The ’del’ function is used to delete the content of a 
 * node if needed.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on
 * the list.
 * @param del The address of the function used to delete
 * the content of a node if needed.
 * @return The new list.
 NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, del);
			del(new_content);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/* void	del_content(void *content)
{
	free(content);
}

void	*ft_strtoupper(void *str)
{
	char	*upper_str;

	upper_str = ft_strdup(str);
	for (char *p = upper_str; *p; p++)
	{
		*p = ft_toupper(*p);
	}
	return (upper_str);
}


int	main(void) {
	t_list *node1 = malloc(sizeof(t_list));
	char *str1 = ft_strdup("hello");
	node1->content = str1;
	node1->next = NULL;

	t_list *node2 = malloc(sizeof(t_list));
	char *str2 = ft_strdup("world");
	node2->content = str2;
	node2->next = NULL;

	node1->next = node2;

	printf("Original list:\n");
	t_list *current = node1;
	while (current != NULL) {
		printf("%s ", (char *)current->content);
		current = current->next;
	}
	printf("\n");

	t_list *new_list = ft_lstmap(node1, ft_strtoupper, del_content);

	printf("New list (uppercase):\n");
	current = new_list;
	while (current != NULL) {
		printf("%s ", (char *)current->content);
		current = current->next;
	}
	printf("\n");

	current = node1;
	while (current != NULL) {
		t_list *next_node = current->next;
		free(current->content);
		free(current);
		current = next_node;
	}

	current = new_list;
	while (current != NULL) {
		t_list *next_node = current->next;
		free(current->content);
		free(current);
		current = next_node;
	}

	return (0);
} */