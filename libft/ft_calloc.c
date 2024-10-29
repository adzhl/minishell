/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:54:16 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/13 12:18:19 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The calloc() function contiguously allocates enough space for count
 objects that are size bytes of memory each and returns a pointer to the
 allocated memory.  The allocated memory is filled with bytes of value
 zero. 
 *  */
void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*p;

	if (size != 0 && count > UINT_MAX / size)
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(1));
	total = count * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}

/* int main() {
	// Allocate an array of 1 million integers
	size_t count = 1000000;
	int* arr = (int*)ft_calloc(count, sizeof(int));
	if (arr == NULL) {
		printf("Allocation failed\n");
		return (1);
	}

	// Check some values
	printf("First few elements: %d %d %d %d\n",
			arr[0], arr[1], arr[2], arr[3]);  // Should print zeros

	// Check last element
	printf("Last element: %d\n", arr[count - 1]);  // Also zero

	// Use the array
	arr[500000] = 42;
	printf("Middle element: %d\n", arr[500000]);  // Prints: 42

	free(arr);  // Use standard free
	return (0);
}
 */