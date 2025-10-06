/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:37:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/06 16:46:59 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

	void ft_check_next_token(t_token *token)
	{
		while (token != NULL)
		{
			if (token->type == TOKEN_HERESTRING)
				ft_check_next_token_herestring(token);
			else if (token->type == TOKEN_HEREDOC)
				ft_check_next_token_heredoc(token);
			else if (token->type == TOKEN_PIPE)
				ft_check_next_token_pipe(token);
			else if (token->type == TOKEN_REDIRECT_IN)
				ft_check_next_token_redir_in(token);
			else if (token->type == TOKEN_REDIRECT_OUT)
				ft_check_next_token_redir_out(token);
			else if (token->type == TOKEN_REDIRECT_APPEND)
				ft_check_next_token_redir_append(token);
			token = token->next;
		}
	}


	// apres le pipe on peut avoir | > outfile --> exit (0) et creation de outfile sans rien dedans donc verifier ce qu'on peut avoir avant ou apres un pipe

	// < / > / >> avant ou apres : fichier ou commande   elle peut aussi etre apres le fichier - si pas de commande, redirige vers le fichier mais ne fait rien, code sortie 0
	// << avant : idem que <
	// << apres : token_EOF
	// | avant et apres : commande,     si rien apres, renvoie le prompt en attente d'une commande

	// Fichier :
	//      si le fichier est un argument (ex cat fichier) :    avant = commande
	// apres = arguments ou operateur
	//      si le fichier est une redirection :                 avant = < ou > ou >>
	// apres = commande ou redirection
	//      si fichier seul :                                   "command not found" 127
	// prendre que la derniere redirection

	// Argument : avant = argument ou commande      // apres = argument, operateur, fichier

	// Commande : tout sauf mot inexistant

	// a gerer : pour l'instant si || pas un operateur donc return 0 pour ope, mais pas pris comme un mot car s'arrete des que rencontre un | ;
	// donc prevoir un message d'erreur si ||