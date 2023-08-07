/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:15 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/06 12:29:21 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//escrever uma função que transforme a t_env em char **env
//para passar para o execve
int	ft_env_to_str(t_shell *shell)
{
	t_env	*aux;
	int		i;

	i = 0;
	aux = shell->env;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	shell->env_strs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shell->env_strs)
		return (1);
	i = 0;
	aux = shell->env;
	while (aux)
	{
		shell->env_strs[i++] = ft_strdup(aux->str);
		aux = aux->next;
	}
	shell->env_strs[i] = NULL;
	return (0);
}

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
	if (current->cmd[0][0] == '/')
		return (current->cmd);
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
	while (paths[i])
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
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}

// função que executa o comando
int	ft_execve(t_token *current)
{
	char	*cmd;
	char	**args;
	int		pid;

	ft_env_to_str(current->shell);
	if(current->cmd[0][0] == '/')
		cmd = ft_strdup(current->cmd[0]);
	else
		cmd = ft_search_cmd(ft_add_cmd(current, ft_get_all_paths(current)));
	args = current->cmd;
	if (!cmd)
	{
		printf("%s : command not found\n", args[0]);
		return (-1);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execve(cmd, args, current->shell->env_strs);
		else
		{
			wait(NULL);
			ft_free_ptrs(cmd, NULL);
		}
	}
	return (0);
}
// perror() imprime uma mensagem de erro padrão