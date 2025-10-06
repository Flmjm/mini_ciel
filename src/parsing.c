/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:37:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/06 14:17:32 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"


t_ju_command	*ft_lstnew_command(int words)
{
	t_ju_command	*new;

	new = ft_malloc(sizeof(*new), 0);
	if (!new)
		return (NULL);
	new->argv = ft_malloc((words + 1) * sizeof(char *), 0);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_cmd_back(t_ju_command **lst, t_ju_command *new)
{
	t_ju_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	new->prev = last;
	last->next = new;
}

int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == TOKEN_WORD)
		count++;
	return (count);
}

void	ft_init_word(t_token *token) 	// gérer l'ordre des commandes et fichiers 
{
	t_ju_command *command;
	int i;
	int	cmd_count;
	int	total_cmds;
	t_ju_command *node;

	command = ft_malloc(sizeof(t_ju_command), 0);
	i = 0;
	cmd_count = 0;
	total_cmds = count_words(token);
	if (!command)
		return ;
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			cmd_count = count_words(token);
			node = ft_lstnew_command(cmd_count);
			while (token && token->type == TOKEN_WORD)
			{
				command->argv[i] = ft_strdup(token->value);
				i++;
				token = token->next;
			}
			if (token->type == TOKEN_REDIRECT_OUT)
				command->redirection = ft_lstnew_redirect(token->next->value, FILE_REDIRECT_OUT);
			else if (token->type == TOKEN_REDIRECT_APPEND)
				command->redirection = ft_lstnew_redirect(token->next->value, FILE_REDIRECT_APPEND);
			command = command->next;
		}
			token = token->next;
		}
	}

	void ft_check_next_token(t_token * token)
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