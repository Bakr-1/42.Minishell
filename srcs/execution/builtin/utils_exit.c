/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:12:03 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 00:27:38 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	atoi_long_exit(char *str, int *flag)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		if (result > LLONG_MAX)
		{
			*flag = 1;
			return (255);
		}
		str++;
	}
	return (sign * result);
}
