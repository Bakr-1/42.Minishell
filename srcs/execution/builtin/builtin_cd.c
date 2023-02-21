/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:03:51 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 13:15:24 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*home_path(char *token);
static int	update_dir(char *token, int home);
static int	set_curr_dir(char *token, int home);
static int	set_path(char **token);
int			ft_cd(char **token);

/*
This is a function called "home_path" that takes in a string called "token".

The function starts by checking if the first two characters of the "token"
string are equal to "~/", using the "ft_strncmp" function.
If the two characters are equal, the function attempts to find the value of
the "HOME" environment variable by calling the "find_in_env" function passing
in "g_gm.env" and "HOME", and assigns it to the "home" variable.

If the value of "home" is not NULL, it creates a new string "path" by calling
the "ft_substr" function passing in "token", 1, and the length of "token".
It frees the memory allocated to "token", then creates a new string
by concatenating the value of "home" with the value of "path" using
the "ft_strjoin" function and assigns it to "token". And frees the memory
allocated to "home" and "path".

The function returns the "token" after expanding the tilde.
This function is used to expand the tilde (~) in the path passed as an argument
It replaces the tilde with the value of the "HOME" environment variable.
*/
static char	*home_path(char *token)
{
	char	*home;
	char	*path;

	if (!ft_strncmp(token, "~/", 2))
	{
		home = find_in_env(g_gm.env, "HOME", 1);
		if (home != NULL)
		{
			path = ft_substr(token, 1, ft_strlen(token));
			free(token);
			token = ft_strjoin(home, path);
			free(home);
			free(path);
			return (token);
		}
	}
	return (token);
}

/*
This is a function called "update_dir" that takes in two parameters:
"token", a string, and "home", an integer.

The function starts by calling the "getcwd" function, passing in "NULL"
and 0, which returns the current working directory as a string and assigns
it to the "pwd" variable.

Then it calls the "chdir" function passing in "token" to change the current
working directory to the path specified by "token".
If the chdir function returns 0 (success), it means that the current working
directory has been successfully changed. The function then proceeds to update
the "OLDPWD" and "PWD" environment variables.
It creates a new string "arg" by concatenating "OLDPWD=" with the value of
"pwd" using "ft_strjoinee" function, calls the "bing_bong_in_env" function
passing in "arg" and frees "arg".
It creates another new string "arg" by concatenating "PWD=" with the value
of "pwd" using "ft_strjoinee" function, calls the "bing_bong_in_env" function
passing in "arg" and frees "arg".

If the value of "home" is non-zero, the function frees the memory allocated
to "token".

The function returns 1 if the current working directory has been successfully
changed, otherwise it returns 0.
This function is used to update the current working directory and
the environment variables "OLDPWD" and "PWD" accordingly.
*/
/*
getcwd() used to get the current working directory.
it takes two argument the first argument is a pointer
to a buffer where the current working directory should be stored,
and the second arguemnt is the size of the buffer.
it returns a pointer of a string containing the
current working directory.

chdir() used to change the current working directory.
it only requires a single argument which specifies pointer to a
string containing the path of the directory that the
program should switch to.
*/
static int	update_dir(char *token, int home)
{
	char	*pwd;
	char	*arg;

	pwd = getcwd(NULL, 0);
	if (chdir(token) == 0)
	{
		if (pwd)
		{
			arg = ft_strjoinee("OLDPWD=", pwd, 0, 1);
			bing_bong_in_env(arg);
			free(arg);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			arg = ft_strjoinee("PWD=", pwd, 0, 1);
			bing_bong_in_env(arg);
			free(arg);
		}
		if (home)
			free(token);
		return (1);
	}
	free(pwd);
	return (0);
}

/*
This is a function called "set_curr_dir" that takes in two parameters:
"token", a string, and "home", an integer.

The function first calls the "update_dir" function passing in "token"
and "home", and returns the value returned by the function if it is
non-zero. If the function "update_dir" returns zero, It sets the global
variable "g_gm.status" to 1.

The function then uses the "stat" function to get information about
the file or directory specified by "token" and assign it to the "cur_dir"
struct. If stat returns -1, it means that the path specified by "token" is
invalid or the stat function failed to get information about the file.
In this case, the function prints an error message
"minishell: cd: %s: %s" where %s is the value of "token" and the error
message returned by "strerror(errno)"

If the stat function was able to get information about the file, it checks
if the file has execute permissions for the user by using the macro S_IXUSR
in a bitwise AND operation with the st_mode field of the stat struct.
If the file does not have execute permissions for the user, the function
prints the same error message.

If the value of "home" is non-zero, the function frees 
the memory allocated to "token".

This function is used to change the current working directory of
the shell to the path specified by "token". It uses the "stat" function to
check if the specified path is valid and has execute permissions for the user,
If not it will print error message and return 1, otherwise it will change
the current working directory.
*/
/*
stat() used to retrive  information about a file on a
Unix-Linux system.
the first argument is a pointer to a string containing
the path to the file or directory for which
information is needed, and the second argument is a pointer to a
struct stat where the information should be stored.
*/
static int	set_curr_dir(char *token, int home)
{
	struct stat	cur_dir;

	if (update_dir(token, home))
		return (1);
	g_gm.status = 1;
	if (stat(token, &cur_dir) == -1)
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", \
			token, strerror(errno));
	else if (!(cur_dir.st_mode & S_IXUSR))
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", \
			token, strerror(errno));
	else
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", \
			token, strerror(errno));
	if (home)
		free (token);
	return (1);
}

/*
This is a function called "set_path" that takes in an array of strings
called "token".

The function first checks if the value of "token[1]" is equal to "-",
if so, it attempts to find the value of the "OLDPWD" environment variable
by calling the "find_in_env" function passing in "g_gm.env" and "OLDPWD",
and assigns it to the "path" variable. If the value of "path" is not NULL,
it calls the "update_dir" function passing in "path" and 0, and frees
the memory allocated to "path".

Then, it attempts to find the value of the "PWD" environment variable
by calling the "find_in_env" function passing in "g_gm.env" and "PWD",
and assigns it to the "path" variable. If the value of "path" is not NULL,
it prints the value of "path" using the "ft_fprintf" function and frees
the memory allocated to "path".

If the value of "token[1]" is not equal to "-", the function calls
the "set_curr_dir" function passing in "token[1]" and 0, and returns
the value returned by the
*/
static int	set_path(char **token)
{
	char	*path;

	if (ft_streq(token[1], "-"))
	{
		path = find_in_env(g_gm.env, "OLDPWD", 1);
		if (path)
		{
			update_dir(path, 0);
			free(path);
		}
		path = find_in_env(g_gm.env, "PWD", 1);
		if (path)
		{
			ft_fprintf(STDOUT_FILENO, "%s\n", path);
			free(path);
		}
		return (1);
	}
	return (set_curr_dir(token[1], 0));
}

/*
it checks if the number of arguments passed in "token" is greater than 2,
if so, it sets the global variable "g_gm.status" to 1, and prints an
error message "minishell: cd: too many arguments" and return.

If there is no argument passed in "token" or the argument passed
is "~" or "--", the function attempts to find the value of the "HOME"
environment variable by calling the "find_in_env" function passing in
"g_gm.env" and "HOME", and assigns it to the "home" variable. If the
value of "home" is NULL, it sets the global variable "g_gm.status" to 1,
and prints an error message "minishell: cd: no HOME environment" and return.

If the value of "home" is not NULL, the function calls the "set_curr_dir"
function passing in "home" and 1 and returns the value returned by
the function.

If the argument passed is not "~" or "--", the function calls the
"home_path" function passing in "token[1]" to expand the tilde, then
calls the "set_path" function passing in "token" and returns the value
returned by the function.

This function is used to change the current working directory of the shell.
If no argument is passed or the argument is "~" or "--", it will change
the current working directory to the value of the "HOME" environment
variable. If an argument is passed, it will change the current working
directory to the path specified by the argument.
*/
int	ft_cd(char **token)
{
	char	*home;

	g_gm.status = 0;
	home = NULL;
	if (token && token[1] && token[2])
	{
		g_gm.status = 1;
		return (ft_fprintf(2, "minishell: cd:  too many arguments\n"));
	}
	if (!token[1] || ft_streq(token[1], "~") || ft_streq(token[1], "--"))
	{
		home = find_in_env(g_gm.env, "HOME", 1);
		if (!home)
		{
			g_gm.status = 1;
			return (ft_fprintf(2, "minishell: cd:  no HOME environment\n"));
		}
		return (set_curr_dir(home, 1));
	}
	token[1] = home_path(token[1]);
	return (set_path(token));
}
