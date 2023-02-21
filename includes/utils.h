/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:28:43 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 21:41:30 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// utils_1
size_t	ft_strlen2d(char **str);
char	**ft_strdoubledub(char **env);
void	_read(t_parse *parse);
void	rwhitespaces(t_parse *parse);
char	*epur_str(char *str);

// utils_2
void	init_parse(void);
t_co	*init_cc(t_co *c);
void	init_global(char **env);
void	init_cv(t_arrcmd *cmd, int i);
int		redirect_tt(int i);

// utils_3
int		abnormal_case(t_parse *parse);
void	set_c(int i);
char	*find_in_env(char **env, char *str, int flag);
void	set_for_read(void);
char	*ft_scjoin(char *str, char c);

// utils_4
int		env_check(char c);
char	*return_type(int i);
int		check_type(int c);

#endif