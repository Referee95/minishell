/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:46:16 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/12 19:23:15 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_pwd(void)
{
	char	pwd[1337];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}

void	c_cd(char **str)
{
	if (str[1] == NULL)
		chdir(getenv("HOME"));
	else if (chdir(str[1]) != 0)
		print_error("minishell: ", str[1], ": No such file or directory\n");
}

int	c_env(char **str)
{
	t_env	*head;

	head = g_glo.env;
	if (str[1])
	{
		printf("env: %s: No such file or directory\n", str[1]);
		return (1);
	}
	while (head)
	{
		if (head->value != NULL)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (0);
}

void	c_unset(t_env *envlist, char **str)
{
	int		i;
	t_env	*head;

	head = envlist;
	i = 0;
	while (str[++i])
	{
		while (str[i] && ft_handler_unset(str[i]))
		{
			printf("minishell: %s: `%s': not a valid identifier\n", str[0],
				str[i]);
			i++;
		}
		if (str[i] == '\0')
			break ;
		ft_remove(str[i]);
	}
}

void	c_exit(char **str)
{
	int	i;

	i = len_arr(str);
	if (i == 1)
	{
		printf("exit\n");
		exit(g_glo.exit_st);
	}
	if (i == 2 && !arg_is_digit(str[1]))
	{
		printf("exit\n");
		exit(ft_atoi(str[1]));
	}
	else if (i >= 2)
	{
		if (i >= 2 && !arg_is_digit(str[1]))
			printf("%s\nminishell: %s: too many arguments\n", str[0], str[0]);
		else if (i >= 2 && arg_is_digit(str[1]))
		{
			printf("%s\nminishell: %s: %s: numeric argument required\n", str[0],
				str[0], str[1]);
			exit(255);
		}
	}
}
