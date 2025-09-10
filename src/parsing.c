/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:37:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/09/10 18:42:31 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

// typedef enum e_token_type
// {
// 	TOKEN_WORD,            // 0 - Arguments, commandes, fichiers
// 	TOKEN_PIPE,            // 1 - |
// 	TOKEN_REDIRECT_IN,     // 2 - <
// 	TOKEN_REDIRECT_OUT,    // 3 - >
// 	TOKEN_REDIRECT_APPEND, // 4 - >>
// 	TOKEN_HEREDOC,         // 5 - <<
//  TOKEN_EOF,             // 6 - EOF
// }						t_token_type;

// typedef struct s_token
// {
// 	t_token_type	type;
// 	char			*value;
// 	struct s_token	*next;
// 	struct s_token	*prev;
// }						t_token;

// typedef struct s_redirect
// {
// 	t_token_type	type;
// 	char			*filename;
// 	//int				fd;
// 	struct s_token	*next;
// 	struct s_token	*prev;
// }						t_redirect;

// typedef struct s_ju_command
// {
// 	char			**argv;
// 	t_redirect		*redirection;
// 	struct s_token	*next;
// 	struct s_token	*prev;
// }						t_ju_command;

int	ft_is_file(t_token *token)
{
	if (token->type == 0 && access(token->value, F_OK) == 0)
		return (1);
	return (0);
}

// int	ft_init_file(t_token *token)
// {
// 	t_redirect	*file;

// 	file = malloc(sizeof(t_redirect));
// 	if (!file)
// 		return (0);
// 	if (ft_is_file(token->value) > 0)
// 	{
// 		if (token->prev == NULL && token->next == NULL)
// 		{
// 			ft_printf("%s: Command not found", token->value);
// 			exit_with_message_and_free(NULL, token, 127);
// 		}
// 		else if (token->prev == TOKEN_WORD)
// 		{

// 		}
// 		ft_lstadd_redirect_back(file, ft_lstnew_redirect(token->value));
// 		return (1);
// 	}
// 	free(file);
// 	return (0);
// }

void	ft_init_word(t_token *token)
{
	t_ju_command	*command;
	int				i;

	command = malloc(sizeof(t_ju_command));
	i = 0;
	if (!command)
		return ;
	while (token->value[i])
	{
		i++;
	}
}

void	ft_check_next_token(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == TOKEN_HEREDOC)
		{
			if (token->next->type >= 1 && token->next->type <= 5)
			{
				ft_printf("syntax error near unexpected token '%s'\n",
					token->next->value);
				// exit_with_message_and_free(NULL, token, 2);
			}
			else
				token->next->type = TOKEN_EOF;
		}
		else if (token->type == TOKEN_PIPE)
		{
			if (token->next == NULL)
				ft_printf("TEST A SUPPRIMER !!! renvoie le prompt en attendant\n");
					// renvoie le prompt et attend une commande
			else if (token->prev->type != TOKEN_WORD)
			{
				ft_printf("syntax error near unexpected token '%s'\n",
					token->value);
				// exit_with_message_and_free(NULL, token, 2);
			}
		}
		else if (token->type == TOKEN_REDIRECT_IN)
		{
			// est ce qu'on initialise ici la struc redir ou est ce qu'on le fait séparément
			if (token->next == NULL)
			{
				ft_printf("syntax error near unexpected token 'newline'\n");
				// exit_with_message_and_free("syntax error near unexpected token 'newline'\n", token, 2);
			}
			else if (token->next->type != TOKEN_WORD)
			{
				ft_printf("syntax error near unexpected token '%s'\n",
					token->next->value);
				// exit_with_message_and_free(NULL, token, 2);
			}
			// si le fichier qui suit n'existe pas, parsing ou exec ?
		}
		else if (token->type == TOKEN_REDIRECT_OUT)
		{
			if (token->next == NULL)
			{
				ft_printf("syntax error near unexpected token 'newline'\n");
				// exit_with_message_and_free("syntax error near unexpected token 'newline'\n", token, 2);
			}
			else if (token->next->type != TOKEN_WORD)
			{
				ft_printf("syntax error near unexpected token '%s'\n",
					token->next->value);
				// exit_with_message_and_free(NULL, token, 2);
			}
		}
		else if (token->type == TOKEN_REDIRECT_APPEND)
		{
			if (token->next == NULL)
			{
				ft_printf("syntax error near unexpected token 'newline'\n");
				// exit_with_message_and_free("syntax error near unexpected token 'newline'\n", token, 2);
			}
			else if (token->next->type != TOKEN_WORD)
			{
				ft_printf("syntax error near unexpected token '%s'\n",
					token->next->value);
				// exit_with_message_and_free(NULL, token, 2);
			}
		}
		token = token->next;
	}
}

// j'ai ajoute un token newline (qui correspondrait a NULL) pour l'erreur de syntaxe du a newline
// apres le pipe on peut avoir | > outfile --> exit (0) et creation de outfile sans rien dedans donc verifier ce qu'on peut avoir avant ou apres un pipe

t_redirect	*ft_lstnew_redirect(char *filename)
{
	t_redirect	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->type = 0;
	// new->fd = open(filename);			
	// selon redirection, pipex init infile ou outfile ?
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// void	ft_lstadd_redirect_back(t_redirect **lst, t_redirect *new)
// {
// 	t_redirect	*last;

// 	if (!lst || !new)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = *lst;
// 	while (last->next != NULL)
// 		last = last->next;
// 	new->prev = last;
// 	last->next = new;
// }

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

// a gerer : pour l'instant si || pas un operateur donc return 0 pour ope, mais pas pris comme un mot car s'arrete des que rencontre un |
// donc prevoir un message d'erreur si ||