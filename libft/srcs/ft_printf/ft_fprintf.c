/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:40:45 by aalseri           #+#    #+#             */
/*   Updated: 2022/12/03 22:04:54 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	ft_fputchar(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

size_t	ft_fputstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		str = "(null)";
	}
	while (str[i])
		ft_fputchar(str[i++], fd);
	return (i);
}

size_t	ft_fredirect(const char *str, va_list ptr, int fd)
{
	size_t	len;

	len = 0;
	if (*str == 'd')
		len += ft_fputnbr(va_arg(ptr, int), fd);
	else if (*str == 'c')
		len += ft_fputchar(va_arg(ptr, int), fd);
	else if (*str == 'u')
		len += ft_fputnbr_un(va_arg(ptr, unsigned int), fd);
	else if (*str == 's')
		len += ft_fputstr(va_arg(ptr, char *), fd);
	else if (*str == 'i')
		len += ft_fputnbr(va_arg(ptr, int), fd);
	else if (*str == '%')
		len += ft_fputchar('%', fd);
	else if (*str == 'x' || *str == 'X')
		len += ft_fputhexa(va_arg(ptr, unsigned int), *str, fd);
	else if (*str == 'p')
		len += ft_fputpointer(va_arg(ptr, unsigned long long), fd);
	return (len);
}

int	ft_fprintf(int fd, const char *str, ...)
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
			len += ft_fredirect(&str[i + 1], ptr, fd);
			i++;
		}
		else
			len += write(fd, &str[i], 1);
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
