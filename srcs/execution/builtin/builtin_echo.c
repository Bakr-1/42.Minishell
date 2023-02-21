/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:05:49 by mealjnei          #+#    #+#             */
/*   Updated: 2023/01/15 00:51:38 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_flag(char **args, int *flag, int *i);
int			ft_echo(char **args);

/*
The function takes three arguments:

args: an array of strings representing the command-line arguments
flag: a pointer to an integer, which will be modified based on the arguments 
passed
i: a pointer to an integer, which keeps track of the current position in the 
args array

It starts by iterating over the args array starting from the current position,
as indicated by the value of i.
It checks if the current argument starts with '-', if so it enters inner loop,
where it iterates over the characters of the current argument.
It checks if the current character is 'n', if so it increments j.
If the inner loop completes and the last character checked is 'n', then it sets
the value of flag to 0.
If the inner loop completes and the last character checked is not 'n', 
it breaks out of both the loop.
Finally, it increments the value of i, so that the next argument 
is processed in the next iteration of the outer loop.

The function is probably used to check for the presence of the "-n" 
flag in the  command line arguments passed to the echo command, and the flag 
variable is used to indicate whether or not the newline character should be 
printed at the end of the output.
*/
void	echo_flag(char **args, int *flag, int *i)
{
	int	j;

	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] && args[*i][j] == 'n')
			j++;
		if (!args[*i][j] && args[*i][j - 1] == 'n')
			*flag = 0;
		else
			break ;
		*i = *i + 1;
	}
}

/*
This is a function in C programming language called "ft_echo" that takes in 
an array of strings called "args". The function starts by initializing 
variables "flag" and "i" to 1 and 1, respectively. Then, it calls a function 
"echo_flag" passing in the "args" array, and the addresses of "flag" and "i"
 variables.
The function then creates a child process using "fork_cmd_pipe" function and 
sets the global variable "g_gm.pid" to the pid returned by the function.
It then checks if the child process id is 0, indicating that the current 
process is the child process. If it is, the function then iterates through 
the "args" array starting from the index "i", printing each element with a 
space between them. If the "flag" variable is set, it also prints a newline 
character.
The function then calls "free_the_child" function passing in "NULL" and exits 
the child process. If the current process is not the child process, it then 
waits for the child process to complete using "my_wait" function and returns 0
*/
int	ft_echo(char **args)
{
	int	flag;
	int	i;

	flag = 1;
	i = 1;
	echo_flag(args, &flag, &i);
	g_gm.pid = fork_cmd_pipe();
	g_gm.status = 0;
	if (g_gm.pid == 0)
	{
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
		if (flag)
			printf("\n");
		free_the_child(NULL);
		exit(EXIT_SUCCESS);
	}
	my_wait();
	return (0);
}
