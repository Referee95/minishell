/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:49:09 by ykhalil-          #+#    #+#             */
/*   Updated: 2023/07/13 13:28:42 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtins(char **str, t_env *cur)
{
	if (!ft_strcmp(str[0], "echo") || !ft_strcmp(str[0], "/bin/echo"))
		c_echo(str);
	else if (!ft_strcmp(str[0], "pwd") || !ft_strcmp(str[0], "/bin/pwd"))
		c_pwd();
	else if (!ft_strcmp(str[0], "cd") || !ft_strcmp(str[0], "/usr/bin"))
		c_cd(str);
	else if (!ft_strcmp(str[0], "export"))
		c_export(cur, str);
	else if (!ft_strcmp(str[0], "unset"))
		c_unset(cur, str);
	else if (!ft_strcmp(str[0], "exit"))
		c_exit(str);
	else if (!ft_strcmp(str[0], "env"))
		c_env (str);
	else if (!ft_strcmp(str[0], "clear"))
		printf("\033[2J\033[1;1H");
	ft_free(str);
	return (0);
}

void	executer_helper(t_scmd *cmd, char **str, t_env *cur)
{
	if (setup_redirections(cmd->redirs, cur))
		exit(1);
	if (*str == NULL)
		exit(0);
	if (cmd->fd)
		dup2(cmd->fd, 0);
}

void	ft_executer(t_scmd *cmd, t_env *cur, char **str)
{
	char	**str_env;
	char	*new_path;

	executer_helper(cmd, str, cur);
	str_env = env_to_str(cur);
	new_path = get_path(str, cur);
	if (str[0] && execve(new_path, str, str_env) == -1)
	{
		if (ft_strchr(str[0], '/'))
		{
			if (access(str[0], R_OK) != 0)
			{
				print_error("minishell: ", str[0],
					": No such file or directory\n");
				exit(127);
			}
		}
		print_error("minishell: ", str[0], ": command not found\n");
		exit(127);
	}
	free(new_path);
}

int	execute_simple(t_scmd *cmd, t_env *cur)
{
	int		pid;
	int		st;
	char	**str;

	str = setup_cmd_arguments(cmd->words, cur);
	if (str == NULL)
	{
		ft_free(str);
		return (0);
	}
	if (*str && is_builtin(str))
		return (ft_builtin(cmd, cur, str));
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_executer(cmd, cur, str);
	}
	wait(&st);
	ft_free(str);
	return (st);
}

int	execute_cmp(t_ccmd *cmd, t_env *env, int j, int i)
{
	int		p1[2];
	int		p2[2];
	pid_t	pid;
	t_scmd	**head;

	head = cmd->compound_command;
	c_pipe(p1, p2);
	while (++i < cmd->num_scmds)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			ft_pipe(i, p1, p2, cmd->num_scmds);
			execute_cmd(head[i], env);
		}
		create_pipe(i, p1, p2);
	}
	close_p(p1, p2);
	while (++j < cmd->num_scmds)
		wait(&i);
	return (i);
}
