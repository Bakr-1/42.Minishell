/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:19 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 11:36:20 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_wait(void);
char	**return_path(void);
char	*path_pipex(char *t_cmd);
int		err_in_out(t_pa *pars2);
int		check_exit_message(t_pa *pars2, char *path);

/*
This is a function called "my_wait" that waits for child processes
to complete. The function uses the "waitpid" function to wait for 
any child process with a specified process ID (-1 in this case) to 
change state. The "waitpid" function returns the process ID of the 
completed child process, and the status of the child process is
stored in the "status" variable.
The function then checks if the child process terminated normally 
using the "WIFEXITED" macro, and if so, the global variable "g_gm.status"
is set to the exit status of the child process using the "WEXITSTATUS" macro.
If the child process was terminated by a signal, the function uses 
the "WIFSIGNALED" macro to check for this and the "WTERMSIG" macro to 
get the signal number that caused the termination, and sets "g_gm.status"
to 128 plus the signal number.
This loop continues until all child processes have completed.
*/
void	my_wait(void)
{
	int		status;
	int		pid;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_gm.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			pid = WTERMSIG(status);
			g_gm.status = 128 + pid;
		}
	}
}

char	**return_path(void)
{
	char	*tmp;
	char	**path;

	g_gm.error = 0;
	tmp = find_in_env(g_gm.env, "PATH", 1);
	if (tmp == NULL)
	{
		g_gm.error = 1;
		return (NULL);
	}
	path = ft_split(tmp, ':');
	free(tmp);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*path_pipex(char *t_cmd)
{
	int		i;
	char	*s;
	char	**path;

	i = 0;
	s = NULL;
	path = return_path();
	if (!path)
		return (NULL);
	while (path[i] != NULL)
	{
		s = ft_strjoin(path[i], t_cmd);
		if (access(s, R_OK) == 0)
		{
			ft_undo_alloc(path);
			free(path);
			return (s);
		}
		free(s);
		s = NULL;
		i++;
	}
	ft_undo_alloc(path);
	free(path);
	return (NULL);
}

int	err_in_out(t_pa *pars2)
{
	if (g_gm.error)
	{
		g_gm.status = 127;
		return (ft_fprintf(2, "minishell: %s: No such file or directory\n" \
			, pars2->tokens[0]));
	}
	else if (ft_strncmp(pars2->tokens[0], "./", 2))
	{
		g_gm.status = 126;
		return (ft_fprintf(2, "minishell: %s: command not found\n" \
			, pars2->tokens[0]));
	}
	return (0);
}

/*
This is a function called "check_exit_message" that takes in two parameters:
"pars2" and "path". The function starts by opening a directory using the 
"opendir" function and passing in the first token of "pars2" array. If the
directory is successfully opened, it prints an error message 
"minishell: [pars2->tokens[0]]: is a directory", closes the directory using
the "closedir" function, calls "free_the_child" function passing in "path",
and returns 126.

If the directory is not opened, it uses the "stat" function to get information 
about the file or directory specified by "pars2->tokens[0]" and store it in 
the "state" structure. If the "stat" function returns 0, indicating that the 
file/directory exists, it checks if the file has execute permissions for the 
user using the "S_IXUSR" flag. If it does, it calls "free_the_child" function 
passing in "path" and returns 0. If the file does not have execute permissions,
it prints an error message "minishell: [pars2->tokens[0]]: Permission denied" 
and returns 126 after calling "free_the_child" function passing in "path".

If the "stat" function returns non-zero value, it means that the file or
directory does not exist. In this case, the function prints an error message 
"minishell: [pars2->tokens[0]]: No such file or directory" and returns 126 
after calling "free_the_child" function passing in "path".

In summary, this function is checking if the file or directory specified in 
the first token of "pars2" array is a valid file or directory with execute 
permissions or not, and returns appropriate error message and exit status.

"S_IXUSR" is a macro that is used to check the execute permissions of a file 
for the user in the Linux/Unix operating systems. It is defined in the 
"sys/stat.h" header file. When used in a bitwise AND operation with the 
"st_mode" field of the "stat" structure, it returns a non-zero value if 
the file has execute permissions for the user, otherwise it returns 0.

In the context of the code you provided, the function is using "S_IXUSR" 
to check if the file specified by "pars2->tokens[0]" has execute permissions
for the user. If it does, the function returns 0 indicating that the file 
is valid and can be executed. If it does not, the function returns an error 
message and an exit status of 126 indicating that the file cannot be executed
due to lack of execute permissions.
*/
int	check_exit_message(t_pa *pars2, char *path)
{
	struct stat	state;
	DIR			*dir;

	dir = opendir(pars2->tokens[0]);
	if (dir)
		return (ft_fprintf(2, "minishell: %s: is a directory\n", \
			pars2->tokens[0]), closedir(dir), \
			free_the_child(path), 126);
	if (stat(pars2->tokens[0], &state) == 0)
	{
		if (state.st_mode & S_IXUSR)
			return (free_the_child(path), 0);
		else
			return (ft_fprintf(2, "minishell: %s: Permission denied\n", \
				pars2->tokens[0]), free_the_child(path), 126);
	}
	if (!dir)
		ft_fprintf(2, "minishell: %s: No such file or directory\n", \
			pars2->tokens[0]);
	return (free_the_child(path), 126);
}
