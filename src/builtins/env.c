/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarvalh <rcarvalh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:21:48 by rcarvalh          #+#    #+#             */
/*   Updated: 2023/07/19 21:21:49 by rcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_builtin_env(t_shell *shell)
{
	t_token *aux;

	aux = shell->new_env;
	while (aux)
	{
		printf("%s\n", aux->str);
		aux = aux->next;
	}
}