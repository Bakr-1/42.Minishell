/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:41:30 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/02 16:25:41 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

size_t	ft_fputhexa(unsigned long long n, char c, int fd);
size_t	ft_fputpointer(unsigned long long p, int fd);
size_t	ft_fputnbr(int nb, int fd);
size_t	ft_fputnbr_un(unsigned int nb, int fd);
size_t	ft_fputchar(int c, int fd);
size_t	ft_fputstr(char *str, int fd);
size_t	ft_fredirect(const char *str, va_list ptr, int fd);
int		ft_fprintf(int fd, const char *str, ...);
int		ft_printf(const char *str, ...);

#endif
