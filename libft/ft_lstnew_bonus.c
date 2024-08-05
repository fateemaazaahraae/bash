/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:36:58 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/04 16:36:34 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstnew - Allocates and returns a new node.
 * @content: The content to create the node with.
 *
 * Return: The new node.
 */

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = ft_strdup(content);
	// printf("node->content %s\n", node->content);
	// node->out = NULL;
	// node->in = NULL;
	// node->limiter = NULL;
	node->next = NULL;
	return (node);
}
