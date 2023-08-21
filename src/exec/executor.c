/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnascime <cnascime@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:36:15 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/21 00:39:01 by cnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_dir(char *path)
{
	DIR	*dir;

	printf("\t\tChecando se %s é um diretório.\n", path);
	if (!path)
	{
		printf("\t\tPath = NULL.\n");
		return (-1);
	}
	dir = opendir(path);
	if (dir)
	{
		printf("\t\t%s é um diretório. Fechando e retornando.\n", path);
		closedir(dir);
		return (1);
	}
	printf("\t\t%s não é um diretório.\n", path);
	return (0);
}

//verifica se existe e se é executável
int	ft_is_executable(char *str)
{
	printf("\t\tstr: %s\n", str);
	if (!str)
		return (-1);
	if (access(str, F_OK) != -1) // se o arquivo existir
	{
		printf("\t\tArquivo existe\n");
		if (ft_is_dir(str) == 0 && access(str, X_OK) == 0) // se não for um diretório
			return (2); // siga em frente, continue a checagem fora daqui
		else // se for um diretório
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			if (access(str, X_OK) == -1) // mas não tiver executável
				ft_putstr_fd(": permissão negada\n", 2);
			else
				ft_putstr_fd(" é um diretório\n", 2);
			g_error_code = 126;
			return (-1);
		}
	}
	else
		printf("\t\tArquivo não existe!\n");
	return (1);
}

// se for diretório mensagem de erro de diretorio

//montagem e verificação


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
//verificar de novo ao sair dessa funcao

//126 permissão
//127 


// function that checks if the command is valid
// returns 0 if it is, -1 if it isn't
int	ft_check_cmd(t_token *current)
{
	char	*cmd;
	char	**args;

	cmd = NULL;
	if (ft_is_executable(current->cmd[0]) == -1)
		return (1);
	else if (current->cmd[0][0] == '.' || current->cmd[0][0] == '/')
		cmd = ft_strdup(current->cmd[0]);
	ft_env_to_str(current->shell);
	if (cmd)
		printf("\t\tcmd1: %s\n", cmd);
	if (!cmd)
		cmd = ft_search_cmd(ft_add_cmd(current, ft_get_all_paths(current)));
	if (cmd)
		printf("\t\tcmd2: %s\n", cmd);
	args = current->cmd;
	if (!cmd)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": comando não encontrado\n", STDERR_FILENO);
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
	pid_t	pid;
	int		child_exit_code;

	pid = fork();
	child_exit_code = 0;
	if (pid == -1)
	{
		printf("fork error\n");
		return (-1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(cmd, current->cmd, current->shell->env_strs) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": Arquivo ou diretório inexistente\n", STDERR_FILENO);
			//ft_putstr_fd(strerror(errno), STDERR_FILENO);
			g_error_code = 127;
			exit(errno);
		}
	}
	else
	{
		waitpid(pid, &child_exit_code, 0);
		if (WIFEXITED(child_exit_code))
		{
			g_error_code = WEXITSTATUS(child_exit_code);
			ft_free_ptrs(&cmd, NULL);
		}
		if (WIFSIGNALED(child_exit_code))
		{
			g_error_code = 128 + WTERMSIG(child_exit_code);
			ft_free_ptrs(&cmd, NULL);
		}
	}
	return (0);
}
