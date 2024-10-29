/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:10:23 by abinti-a          #+#    #+#             */
/*   Updated: 2024/06/20 11:06:25 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	convert(const char *format, va_list args)
{
	int		len;

	len = 0;
	if (*format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (*format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (*format == 'p')
	{
		len += ft_putstr("0x");
		len += ft_puthex(va_arg(args, unsigned long), 'x');
	}
	else if (*format == 'd' || *format == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (*format == 'u')
		len += ft_putuns(va_arg(args, unsigned int));
	else if (*format == 'x')
		len += ft_puthex(va_arg(args, unsigned int), 'x');
	else if (*format == 'X')
		len += ft_puthex(va_arg(args, unsigned int), 'X');
	else if (*format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			len = len + convert(format, args);
		}
		else
			len = len + ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (len);
}

/* int main(void)
{
	int r1 = ft_printf("c = %c\n", 'a');
	ft_printf("%d characters\n", r1);
	ft_printf("\n");

	int r2 = ft_printf("s = %s\n", "This is a string");
	ft_printf("%d characters\n", r2);
	ft_printf("\n");

	int num = 42;
	int *ptr = &num;
	int r3 = ft_printf("p = %p\n", (void *)ptr);
	ft_printf("%d characters\n", r3);
	ft_printf("\n");

	int r4 = ft_printf("d = %d\n", -123);
	ft_printf("%d characters\n", r4);
	ft_printf("\n");

	int r5 = ft_printf("i = %i\n", -1037);
	ft_printf("%d characters\n", r5);
	ft_printf("\n");

	int r6 = ft_printf("u = %u\n", 1827);
	ft_printf("%d characters\n", r6);
	ft_printf("\n");

	int r7 = ft_printf("x = %x\n", 123451289);
	ft_printf("%d characters\n", r7);
	ft_printf("\n");

	int r8 = ft_printf("X = %X\n", 123451289);
	ft_printf("%d characters\n", r8);
	ft_printf("\n");

	int r9 = ft_printf("percent = %%\n");
	ft_printf("%d characters\n", r9);
	ft_printf("\n");

	return (0);
} */