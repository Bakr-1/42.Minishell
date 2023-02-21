/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:40:45 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/02 22:34:12 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	size_t	len;
	int		i;

	va_start(ptr, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_fredirect(&str[i + 1], ptr, STDOUT_FILENO);
			i++;
		}
		else
			len += write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
	va_end(ptr);
	return (len);
}

/* this would output any base
size_t	ft_putnbr_base(int nbr, int len, char *base)
{
	size_t	length;

	length = 0;
	if (nbr < len)
	{
		length += ft_putchar(base[nbr]);
	}
	else
	{
		length += ft_putnbr_base(nbr / len, len, base);
		length += ft_putchar(base[nbr % len]);
	}
	return (length);
}
*/
