/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   race_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:38:30 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/06 17:38:33 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(void)
{
	pid_t process_id;

	process_id = fork();
	if (process_id == 0)
	{
		for (int i = 0; i < 100; i++)
			write(1, "0", 1);
	}
	else
	{
		// wait(NULL);
		for (int i = 0; i < 100; i++)
			write(1, "1", 1);
	}
	return (0);
}