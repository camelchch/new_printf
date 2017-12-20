/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/20 11:34:44 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static	void	cast_nu_o(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = itoa_base(va_arg(args, size_t), 10, 8);
	else if (data->cast == none || data->cast == hh)
		data->ori = itoa_base(va_arg(args, unsigned int), 10, 8);
	else if (data->cast == l)
		data->ori = itoa_base(va_arg(args,unsigned long), 10, 8);
	else if (data->cast == ll)
		data->ori = itoa_base(va_arg(args, unsigned long long), 10, 8);
	else if (data->cast == j)
		data->ori = itoa_base(va_arg(args, uintmax_t), 10, 8);
}

void	con_o(va_list args, t_data *data, char *format, int size)
{
	cast_nu_o(args, data, format, size);
	set_flags(data, format, size);
	set_print_oxu_hash(data, "0");
}

void	con_O(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	data->ori = ft_itoa_max(va_arg(args,unsigned long));
	set_flags(data, format, size);
	set_print_oxu_hash(data, "0");
}
