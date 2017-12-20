/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 14:54:36 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/20 12:19:33 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define is_hash(x) ((x == '#')? 1 : 0)
#define is_zero(x) ((x == '0')? 1 : 0)
#define is_minus(x) ((x == '-')? 1 : 0)
#define is_plus(x) ((x == '+')? 1 : 0)
//#define is_width(x) x
//#define is_precison(x) x
#define is_end(x) ((x == '\0')? 1 : 0)

typedef enum	s_cast
{
	none = 1,
	hh,
	h,
	l,
	ll,
	j,
	z,
}		t_cast;

typedef	struct	s_data
{
	char	*ori;
	char	flags[10];
	int		width;
	int		precison;
	int		no_pre;
	int		len;
	int		blank;
	t_cast	cast;
}			t_data;

#define NB_CON	15

typedef struct s_fu
{
	char	c;

	void (*func)(va_list, t_data *, char *, int);
}				t_fu;

void	con_d(va_list args, t_data *data, char *foamat, int size);
void	con_D(va_list args, t_data *data, char *foamat, int size);
void	con_i(va_list args, t_data *data, char *foamat, int size);
void	con_c(va_list args, t_data *data, char *foamat, int size);
void	con_C(va_list args, t_data *data, char *foamat, int size);
void	con_s(va_list args, t_data *data, char *foamat, int size);
void	con_S(va_list args, t_data *data, char *foamat, int size);
void	con_o(va_list args, t_data *data, char *foamat, int size);
void	con_O(va_list args, t_data *data, char *foamat, int size);
void	con_u(va_list args, t_data *data, char *foamat, int size);
void	con_U(va_list args, t_data *data, char *foamat, int size);
void	con_p(va_list args, t_data *data, char *foamat, int size);
void	con_per(va_list args, t_data *data, char *foamat, int size);
void	con_x(va_list args, t_data *data, char *foamat, int size);
void	con_XX(va_list args, t_data *data, char *foamat, int size);
void	set_flags(t_data *fl, char *format, int size);
void	set_print_oxu_hash(t_data *data, char *pre_fix);
char	*ft_itoa_max(intmax_t n);
char	*ft_itoa_unmax(uintmax_t n);
char	*ft_itoa_short(short n);
char	*ft_itoa_signchar(char n);
char	*itoa_base(intmax_t nb, int from, int to);
char	*itoa_hex(uintmax_t nb, char x);
int		max_2(int x, int y);
int		max_3(int x, int y, int z);
int		nb_digit(char *str);
void	ft_putnstr(char *s, int nbr);
void	ft_putnwstr(wchar_t *s, int nbr);
void	ft_putnchar(char c, int nbr);
char	*ft_strnchr(const char *s, int c, int size);
int		ft_strnchr_double(const char *s, int c, int size);
void	ft_putwchar(wchar_t we);
void	ft_putnwchar(wchar_t *we, int nbr);
size_t	ft_wstrlen(wchar_t *we);
void	set_cast(t_data *data, char *foamat, int size);
int		ft_printf(const char *restrict format, ...);

#endif
