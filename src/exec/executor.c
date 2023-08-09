/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:15 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/08 18:09:39 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//function that gets all the paths from the env
//and splits them into an array of strings
//returns an array of strings with the paths
char	**ft_get_all_paths(t_token *current)
{
	char	*path;
	char	**paths;
	t_env	*aux;

	path = NULL;
	paths = NULL;
	aux = current->shell->env;
	while (aux)
	{
		if (aux->str && ft_strncmp(aux->str, "PATH", 4) == 0)
		{
			path = ft_substr(aux->str, 5, ft_strlen(aux->str) - 5);
			paths = ft_split(path, ':');
			free(path);
			path = NULL;
			return (paths);
		}
		aux = aux->next;
	}
	return (NULL);
}

//function that adds "/cmd" to the end of each string
//returns an array of strings with the full paths
char	**ft_add_cmd(t_token *current, char **paths)
{
	char	*aux;
	char	*slash_cmd;
	int		i;

	i = 0;
	if (!paths)
		return (NULL);
	if (!current->cmd[0][0])
		return (NULL);
	slash_cmd = ft_strjoin("/", current->cmd[0]);
	aux = NULL;
	while (paths[i])
	{
		aux = ft_strjoin(paths[i], slash_cmd);
		free(paths[i]);
		paths[i] = NULL;
		paths[i] = ft_strdup(aux);
		free(aux);
		aux = NULL;
		i++;
	}
	free(slash_cmd);
	slash_cmd = NULL;
	return (paths);
}

//function that searches for the file
//returns the string with the full path of the file
char	*ft_search_cmd(char **paths)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK) == 0)
		{
			ret = ft_strdup(paths[i]);
			i = 0;
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (ret);
		}
		i++;
	}
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	return (NULL);
}

// function that checks if the command is valid
// returns 0 if it is, -1 if it isn't
int	ft_check_cmd(t_token *current)
{
	char	*cmd;
	char	**args;

	cmd = NULL;
	ft_env_to_str(current->shell);
	if (!current->cmd[0][0])
		return (0);
	if (current->cmd[0][0] == '/')
		cmd = ft_strdup(current->cmd[0]);
	else
		cmd = ft_search_cmd(ft_add_cmd(current, ft_get_all_paths(current)));
	args = current->cmd;
	if (!cmd)
	{
		printf("%s : command not found\n", args[0]);
		g_error_code = 127;
		ft_free_ptrs(&cmd, NULL);
		return (-1);
	}
	else
		ft_execve(current, cmd);
	return (0);
}

// function that executes the command
// returns 0 if it is executable, -1 on execve error
int	ft_execve(t_token *current, char *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, current->cmd, current->shell->env_strs) == -1)
		{
			printf("execve error\n");
			g_error_code = 127;
			ft_free_ptrs(&cmd, NULL);
			exit(1);
		}
	}
	else
	{
		g_error_code = 0;
		wait(NULL);
		ft_free_ptrs(&cmd, NULL);
	}
	return (0);
}
