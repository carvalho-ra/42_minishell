/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mount_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:36:00 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/08/21 15:24:21 by rcarvalh         ###   ########.fr       */
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
