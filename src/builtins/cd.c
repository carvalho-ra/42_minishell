/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:11:35 by cnascime          #+#    #+#             */
/*   Updated: 2023/08/01 11:02:07 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO
/*
[ ] deve ser feito com a nossa própria env
[ ] não está trocando de pasta
[ ] deve funcionar com o caminho relativo ../ ou ./
[ ] deve funcionar com o caminho absoluto /home/minishell/src
[ ] deve funcionar com "~"
*/

// Changes the current directory.
int	ft_builtin_cd(t_shell *shell)
{
	char	*path;

	path = shell->list->str;
	printf("\t\tPasta onde quero entrar: %s\n", path);
	if (shell->list->next == NULL
		|| (shell->list->next->str[0] == '~' && shell->list->next->str[1] == '\0'))
	{
		printf("Primeira etapa: Entrei aqui no ~\n");
		printf("\t1. OLDPWD: %s\t", ft_getenv("OLDPWD", shell->env_strs[0]));
		printf("\t1. pasta onde estou: %s\t", getcwd(NULL, 0));
		printf("\t1. path para onde quero ir ainda não foi definido\n");
		path = ft_getenv("HOME", shell->env_strs[0]);
		printf("Segunda etapa: path para onde quero ir = HOME\n");
		printf("\t2. OLDPWD: %s\t", ft_getenv("OLDPWD", shell->env_strs[0]));
		printf("\t2. pasta onde estou: %s\t", getcwd(NULL, 0));
		printf("\t2. path para onde quero ir: %s\n", path);
		ft_oldpwd(shell);
		printf("Terceira etapa: Troca do OLDPWD para pasta atual:\n");
		printf("\t3. OLDPWD: %s TEM DE SER IGUAL À", ft_getenv("OLDPWD", shell->env_strs[0]));
		printf("\t3. pasta onde estou: %s E DIFERENTE DA", getcwd(NULL, 0));
		printf("\t3. path para onde quero ir: %s\n", path);
		chdir(path);
		printf("Quarta etapa: Troca do diretório:\n");
		printf("\t4. OLDPWD: %s\t", ft_getenv("OLDPWD", shell->env_strs[0]));
		printf("\t4. pasta onde estou: %s\t", getcwd(NULL, 0));
		printf("\t4. path onde queria chegar (igual aos últimos acima): %s\n", path);
	}
	else if (shell->list->next->str[0] == '-' && shell->list->next->str[1] == '\0')
	{
		printf("Entrei aqui no -\n");
		printf("\t\tshell->list->next->str: %s\n", shell->list->next->str);
		if (ft_getenv("OLDPWD", shell->env_strs[0]) == NULL)
		{
			ft_putstr_fd("minishell: cd: nenhum diretório anterior\n", 2);
			return (2);
		}
		else
		{
			printf("Primeira etapa, pastas diferentes:\n");
			printf("\t1. OLDPWD: %s\t", ft_getenv("OLDPWD", shell->env_strs[0]));
			printf("\t1. pasta onde estou: %s\n", getcwd(NULL, 0));
			path = ft_getenv("OLDPWD", shell->env_strs[0]);
			printf("Segunda etapa, os dois estão iguais: o path para onde quero ir é o que estava no oldpwd\n");
			printf("\t2. OLDPWD: %s\t", ft_getenv("OLDPWD", shell->env_strs[0]));
			printf("\t2. path para onde quero ir: %s\n", path);
			ft_oldpwd(shell);
			printf("Terceira etapa, o oldpwd agora é o path atual, novamente diferentes\n");
			printf("\t3. OLDPWD (== CURRENT): %s\t", ft_getenv("OLDPWD", shell->env_strs[0]));
			printf("\t3. path para onde quero ir: %s\n", path);
			chdir(path);
			printf("Quarta etapa, troquei de pasta para path.\n");
			printf("\t4. OLDPWD: %s\t", ft_getenv("OLDPWD", shell->env_strs[0]));
			printf("\t4. variável path: %s\n", path);
			printf("\t4. pasta onde estou: %s\n", getcwd(NULL, 0));
		}
	}
	else
	{
		printf("Não entrei no ~ nem no -\n");
		ft_oldpwd(shell);
		chdir(path);
	}
	return (1);
	//!Deveria ser 0 se conseguiu trocar de diretório. Precisamos trocar.
}

// Adds the current directory to the environment variable as OLDPWD.
// First, we need to find the current directory.
// Then, we need to add it to the environment variable.
// Then, we need to update the environment variable.
// Finally, we need to free the memory.
//Para apagar o anterior, preciso de uma função que apague o nó da lista.
//Para isso, preciso de uma função que encontre o nó da lista.
//!Está colocando HOME como OLDPWD o tempo todo, até na inicialização, mesmo
//!dando unset antes de sair do programa.
void	ft_oldpwd(t_shell *shell)
{
	t_env	*env;
	char	*oldpwd;
	int		env_index;

	env = shell->env;
	oldpwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	printf("\t\tDepois do strjoin: %s\n", oldpwd);
	char	*tempfail = ft_getenv("OLDPWD", shell->env_strs[0]);
	printf("\t\tOLDPWD está na env_list? %s\n", tempfail);
	env_index = ft_is_key_duplicate(env, oldpwd, 2);
	printf("\t\tIndex %i\n", env_index);
	if (env_index > -1)
		ft_delete_env(env, env_index);
	ft_add_to_env_list(env, oldpwd, 2);
	char	*tempok = ft_getenv("OLDPWD", shell->env_strs[0]);
	printf("\t\tOLDPWD está na env_list? %s\n", tempok);
	free(oldpwd);
	return ;
}

// Recreates the function above, but with char* shell->env_strs[0] instead of a list.
void	ft_oldpwd_matrix(t_shell *shell)
{
	char	*oldpwd;
	int		env_index;

	oldpwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	env_index = ft_is_key_duplicate_matrix(shell->env_strs, "OLDPWD", 2);
	if (env_index > -1)
		ft_delete_env_from_matrix(shell, env_index);
	ft_add_to_env_matrix(shell->env_strs, oldpwd, 2);
	free(oldpwd);
	return ;
}
