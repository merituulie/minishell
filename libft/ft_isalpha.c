/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:37:51 by emeinert          #+#    #+#             */
/*   Updated: 2023/08/03 10:38:05 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int n)
{	
	int	answer;

	answer = 0;
	if ((n > 64 && n < 91) || (n > 96 && n < 123))
		answer = 1;
	else
		answer = 0;
	return (answer);
}
