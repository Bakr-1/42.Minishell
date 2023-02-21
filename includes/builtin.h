/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:27:10 by mealjnei          #+#    #+#             */
/*   Updated: 2023/01/15 12:21:39 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/*
 * Builtin functions
 */

// exec_builtin.c
int			check_builtin(char **tokens);
int			exec_builtin(t_exec *exec, char **tokens);

//ft_unset.c
void		ft_unset(char **token);

//builtin_echo.c
int			ft_echo(char **args);

//builtin_cd.c
int			ft_cd(char **token);

//builtin_exit.c
void		ft_exit(char **args);

//exit_utils.c
long long	atoi_long_exit(char *str, int *flag);

//builtin_export.c
void		ft_export(char **tokens);
void		bing_bong_in_env(char *arg);

//utils_export_1.c
void		set_new_env(char *arg);
void		add_to_env(char *arg);

//utils_export_2.c
void		ft_sort_print_env(void);
int			char_index(char *str, char c);
int			find_env_ri(char **env_pointer, char *key);

#endif