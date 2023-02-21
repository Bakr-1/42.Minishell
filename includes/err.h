/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:28:34 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/03 18:52:07 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "minishell.h"

void		*calloc_minishell(size_t size, size_t count);
void		close_all_fd(int fd);
void		print_nl(char *str, char *s);
t_arrcmd	*free_cmd(t_arrcmd *cmd, int i);
void		free_pars2(t_pa *pars2);
void		free_parse1(t_parse *parse);
void		free_parse2(t_parse *parse);
void		free_parse3(t_parse *parse);

#endif