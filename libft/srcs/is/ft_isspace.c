/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 03:01:13 by aalseri           #+#    #+#             */
/*   Updated: 2022/06/26 14:40:12 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isspace(int i)
{
	return (i == '\t' || i == '\f' || i == '\r' \
	|| i == ' ' || i == '\n' || i == '\v');
}
