/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:37:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/09 17:35:30 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

int	count_words(t_token *token)
{
	int	count;
	t_token	*curr;

	count = 0;
	curr = token;
	while (curr && curr->type != TOKEN_PIPE)
	{
		while (curr && (curr->type >= TOKEN_REDIRECT_IN && curr->type <= TOKEN_REDIRECT_APPEND))
			curr = curr->next;
		while (curr && curr->type == TOKEN_WORD)
		{
			if (curr->prev == NULL || curr->prev->type == TOKEN_WORD || curr->prev->type == TOKEN_PIPE || curr->prev->type == TOKEN_EOF)
				count++;
			curr = curr->next;
		}
	}
	return (count);
}

t_commands	*ft_lstnew_command(int words)
{
	t_commands	*new;

	new = ft_malloc(sizeof(*new), 0);
	if (!new)
		return (NULL);
	new->argv = ft_malloc((words + 1) * sizeof(char *), 0);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_cmd_back(t_commands **lst, t_commands *new)
{
	t_commands	*last;

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
	last->next = new;
}

t_token	*ft_add_redir(t_token *token, t_commands *node)
{
	while (token && (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT || token->type == TOKEN_REDIRECT_APPEND))
	{
		if (token->type == TOKEN_REDIRECT_IN)
			ft_lstadd_infiles_back(&node->infiles, ft_lstnew_redirect_in(token->next->value));
		else if (token->type == TOKEN_REDIRECT_OUT)
			ft_lstadd_outfiles_back(&node->outfiles, ft_lstnew_redirect_out(token->next->value, FILE_REDIRECT_OUT));
		else if (token->type == TOKEN_REDIRECT_APPEND)
			ft_lstadd_outfiles_back(&node->outfiles, ft_lstnew_redirect_out(token->next->value, FILE_REDIRECT_APPEND));
		token = token->next->next;
	}
	return(token);
}

// t_token	*ft_add_cmd_in_node(t_token *token, t_commands *command, t_commands *node)
// {
// 	int	i;

// 	i = 0;
// 	while (token && token->type == TOKEN_WORD)
// 			{
// 				node->argv[i] = ft_strdup(token->value);
// 				i++;
// 				token = token->next;
// 			}
// 			node->argv[i] = NULL;
// 			ft_lstadd_cmd_back(&command, node);
// 	return (token);
// }

t_commands	*ft_init_cmd(t_token *token)
{
	t_commands *command;
	int i;
	int	cmd_count;
	t_commands *node;
	t_token	*tmp_token;

	cmd_count = 0;
	command = NULL;
	tmp_token = token;
	while (token)
	{
		cmd_count = count_words(token);  
		node = ft_lstnew_command(cmd_count);
		tmp_token = ft_add_redir(token, node);
		if (tmp_token->type == TOKEN_WORD)
		{
			i = 0;
			while (tmp_token && tmp_token->type == TOKEN_WORD)
			{
				node->argv[i] = ft_strdup(tmp_token->value);
				i++;
				tmp_token = tmp_token->next;
			}
			node->argv[i] = NULL;
			ft_lstadd_cmd_back(&command, node);
		}
		token = ft_add_redir(tmp_token, node);
		if(token)
			token = token->next;
	}
	return(command);
}

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