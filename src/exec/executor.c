/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:15 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/07 04:01:13 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// escrever uma função que pegue o caminho completo dos PATHS
// na nossa env e retorn um array de strings com os paths
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
	printf("no PATH found\n");
	return (NULL);
}

// função que adiciona "/cmd" ao final de cada string
// retornar um array de strings com os paths completos
char	**ft_add_cmd(t_token *current, char **paths)
{
	char	*aux;
	char	*slash_cmd;
	int		i;

	i = 0;
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

// função que procura pelo arquivo
//retorna o path funcional se existir
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
		ft_free_ptrs(&cmd, NULL);
		return (-1);
	}
	else
		ft_execve(current, cmd);
	return (0);
}

int	ft_execve(t_token *current, char *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, current->cmd, current->shell->env_strs) == -1)
		{
			printf("execve error\n");
			ft_free_ptrs(&cmd, NULL);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
		ft_free_ptrs(&cmd, NULL);
	}
	return (0);
}
