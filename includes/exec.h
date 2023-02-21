/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:28:41 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/18 15:20:17 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

//? execution.c
int		executing(void);
void	init_exec(t_exec *exec);

//utils_exec_1.c
int		check_exit_message(t_pa *pars2, char *path);
int		err_in_out(t_pa *pars2);
char	*path_pipex(char *t_cmd);
void	my_wait(void);

//? single_cmd_red.c
void	check_file_pre(t_pa *pars2);
void	single_command_red(void);
void	find_cpath(t_pa *pars2, t_exec *exec);

//? single_cmd.c
void	single_command(void);

//utils_single_cmd_1.c
void	errors_exec(t_pa *pars2, t_exec *exec);
void	failed_open(t_exec *exec, char *file);
void	set_redir(t_pa *pars2, t_exec *exec);

//? here_doc.c
char	*heredoc_env(char *str, int quoted);
char	*here_doc_join(char *file, int quoted);
int		here_doc_loop(t_redirection *red, t_exec *exec);
void	here_doc(t_redirection *red, t_exec *exec);
void	here_doc_exec(t_pa *pars2, t_exec *exec);

//utils_here_doc_1.c
int		creating_dump_file(t_exec *exec);
char	*invalied_env_hd(char *str, int i);
char	*env_hd(char *str, char *temp, int i);

//? multi_pipes.c
int		single_command_pipe(t_pa *pars2, t_exec *exec);
void	execute_pipe(int i);

//utils_pipes_1.c
void	dup2_pipe_fail(t_exec *exec, t_exec *e);
void	piping(int **fd, int n_cmds);
int		allocate_pipe(t_pa *pars2, t_exec *exec);

//utils_pipes_2.c
pid_t	fork_cmd_pipe(void);
void	free_the_child(char *path);

//utils_pipes_3.c
void	exec_free(t_pa *pars2, t_exec *exec);
void	free_pipes(int **fd, int i);
void	close_pipes(int **fd, int i);

//? exec_pipe_red.c
void	execute_pipe_redir(void);

//utils_pipe_red_1.c
void	set_redir_pipe(t_pa *pars2, t_exec *exec);

#endif