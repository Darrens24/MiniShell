/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleleux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:40:28 by eleleux           #+#    #+#             */
/*   Updated: 2023/02/23 17:51:38 by eleleux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

si la tokenisation voit des || --> si la commande precedente a echoue, on effectue la commande 

necessite de regrouper les elements par bloc separes par les || et &&

int	or_command(t_shell *shell)
{
	if (g_err != 0)
	{
	}
}

int	and_command(t_shell *shell)
{

}
