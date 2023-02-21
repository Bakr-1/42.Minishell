/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:09:37 by mealjnei          #+#    #+#             */
/*   Updated: 2023/01/15 00:41:50 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			char_index(char *str, char c);
static int	check_only_key(char *key);
int			find_env_ri(char **env_pointer, char *key);
static void	print_env_qouted(char **env);
void		ft_sort_print_env(void);

int	char_index(char *str, char c)
{
	char	*str2;
	int		ret;

	str2 = ft_strchr(str, c);
	if (!str2)
		return (-1);
	else
		ret = (int)(str2 - str);
	return (ret);
}

static int	check_only_key(char *key)
{
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (g_gm.env_v2[++i])
		if (!ft_strcmp(g_gm.env_v2[i], key))
			return (i);
	return (-1);
}

/*
This function is used to find the index of a specific environment variable
within an array of environment variables. The function takes two arguments,
an array of environment variables (env_pointer) and a key (key) which is
the name of the environment variable to be found.
It iterates over the env_pointer array, and for each element, it uses the 
char_index function to find the index of the '=' character in that element, 
which separates the variable name from the value.
Then, it creates a substring of the current element, starting from index 0 
to the index of the '=' found earlier.
Then it checks if the substring is equal to the key passed to the function, 
if so, it returns the current index of the env_pointer array.
If the key is not found in the env_pointer, 
it calls another function check_only_key, which probably checks if the key 
exists in the environment variables or not.
It returns -1 if the key is not found.
*/
int	find_env_ri(char **env_pointer, char *key)
{
	int		index;
	char	*sub_env;
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (env_pointer[++i])
	{
		index = char_index(env_pointer[i], '=');
		if (index == -1)
			index = ft_strlen(env_pointer[i]);
		else
		{
			sub_env = ft_substr(env_pointer[i], 0, index);
			if (sub_env != NULL && ft_streq(key, sub_env))
			{
				free(sub_env);
				return (i);
			}
			free (sub_env);
		}
	}
	return (check_only_key(key));
}

/*
Printing the environment variables passed to it,
in a specific format. Specifically, it is using
ft_fprintf to print out the "declare -x" string,
followed by the environment variables, one at a time.
If the environment variable contains an '=' character,
it is adding a quotation mark before the value of the variable,
and after the value of the variable. 
The function is iterating over the environment variables array 
and at each iteration it is printing out the environment variable 
and adding the quotation mark if it contains the '=' character. 
The final output will be in the form of:
"declare -x VARIABLE_NAME="VARIABLE_VALUE"".
*/
static void	print_env_qouted(char **env)
{
	size_t	i;
	size_t	j;
	char	equ;

	i = -1;
	while (env[++i])
	{
		equ = 1;
		j = -1;
		ft_fprintf(1, "declare -x ");
		while (env[i][++j])
		{
			ft_fprintf(1, "%c", env[i][j]);
			if (env[i][j] == '=' && equ)
			{
				ft_fprintf(1, "\"");
				equ--;
			}
		}
		if (equ == 0)
			ft_fprintf(1, "\"");
		ft_fprintf(1, "\n");
	}
}

/*
simple implementation of bubble sort to sort the env
The outer while loop iterates through the array, 
and the inner while loop compares adjacent elements, 
swapping them if they are out of order. 
The specific comparison function used is ft_strcmp, 
which compares two strings and returns a value indicating
their lexicographic ordering.
*/
void	ft_sort_print_env(void)
{
	int		i;
	int		j;
	char	**dup;

	dup = ft_strdoubledub(g_gm.env_v2);
	i = 0;
	while (dup[i])
	{
		j = i + 1;
		while (dup[j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
				ft_swap((void **)&dup[i], (void **)&dup[j]);
			j++;
		}
		i++;
	}
	print_env_qouted(dup);
	ft_undo_alloc(dup);
	free(dup);
}
