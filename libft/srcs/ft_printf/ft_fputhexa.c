/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:44:06 by aalseri           #+#    #+#             */
/*   Updated: 2022/12/03 21:59:39 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	ft_fputhexa(unsigned long long n, char c, int fd)
{
	char	*base;
	size_t	len;

	len = 0;
	base = "0123456789ABCDEF";
	if (c == 'x')
		base = "0123456789abcdef";
	if (n > 15)
		len += ft_fputhexa(n / 16, c, fd);
	len += ft_fputchar(base[n % 16], fd);
	return (len);
}

size_t	ft_fputpointer(unsigned long long p, int fd)
{
	size_t	len;

	len = 2;
	write(fd, "0x", 2);
	if (p == 0)
	{
		write(fd, "0", 1);
		return (3);
	}
	len += ft_fputhexa(p, 'x', fd);
	return (len);
}

size_t	ft_fputnbr(int nb, int fd)
{
	long	i;
	size_t	len;

	len = 0;
	i = (long)nb;
	if (i < 0)
	{
		ft_fputchar('-', fd);
		i *= -1;
		len++;
	}
	if (i > 9)
	{
		len += ft_fputnbr(i / 10, fd);
		len += ft_fputchar(i % 10 + '0', fd);
	}
	else
		len += ft_fputchar(i + '0', fd);
	return (len);
}

size_t	ft_fputnbr_un(unsigned int nb, int fd)
{
	long	i;
	size_t	len;

	len = 0;
	i = (long)nb;
	if (i > 9)
	{
		len += ft_fputnbr_un(i / 10, fd);
		len += ft_fputchar(i % 10 + '0', fd);
	}
	else
		len += ft_fputchar(i + '0', fd);
	return (len);
}
