/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:05:45 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 15:14:15 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates the list ’lst’ and applies the function
 ’f’ on the content of each node. 
 @param lst  The address of a pointer to a node.
 @param f The address of the function used to iterate on
the list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* void to_uppercase(void *content)
{
    char *str = (char *)content;
    int i = 0;
    while (str[i])
    {
        str[i] = (char)ft_toupper(str[i]);
        i++;
    }
}

void print_content(void *content)
{
    printf("%s\n", (char *)content);
}

int main()
{
    t_list *head = NULL;
    t_list *new_node;
    char *str1 = ft_strdup("Hello");
    char *str2 = ft_strdup("World");
    char *str3 = ft_strdup("Foo");
    char *str4 = ft_strdup("Bar");

    new_node = malloc(sizeof(t_list));
    new_node->content = str1;
    new_node->next = NULL;
    head = new_node;

    new_node = malloc(sizeof(t_list));
    new_node->content = str2;
    new_node->next = NULL;
    head->next = new_node;

    new_node = malloc(sizeof(t_list));
    new_node->content = str3;
    new_node->next = NULL;
    head->next->next = new_node;

    new_node = malloc(sizeof(t_list));
    new_node->content = str4;
    new_node->next = NULL;
    head->next->next->next = new_node;

    printf("Linked list contents before ft_lstiter:\n");
    ft_lstiter(head, print_content);

    printf("\nLinked list contents after ft_lstiter with to_uppercase:\n");
    ft_lstiter(head, to_uppercase);
    ft_lstiter(head, print_content);

    t_list *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->content);
        free(tmp);
    }

    return 0;
}
 */