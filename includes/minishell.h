/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:01:23 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 12:14:02 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mini_lib.h"

// minishell.c

char		*print_prompt(void);
int			main(int ac, char **av, char **env);

extern struct s_gm	g_gm;

#endif
