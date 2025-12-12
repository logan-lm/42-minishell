/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:02:54 by pberne            #+#    #+#             */
/*   Updated: 2025/12/06 20:07:07 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRUCTS_H
# define LIBFT_STRUCTS_H

typedef struct s_atof_data
{
	double			nb;
	int				i;
	double			sign;
	double			divider;
	int				is_decimal;
}					t_atof_data;

typedef union u_vnumber
{
	unsigned int	ui;
	int				i;
	float			f;
	double			d;
	long			l;
	unsigned long	ul;
}					t_vnumber;

/// VECTOR INT

typedef struct s_v2i
{
	int				x;
	int				y;
}					t_v2i;

typedef struct s_v3i
{
	int				x;
	int				y;
	int				z;
}					t_v3i;

t_v2i				ft_v2i(int x, int y);
t_v2i				*ft_v2ip(int x, int y);
t_v3i				ft_v3i(int x, int y, int z);
t_v3i				*ft_v3ip(int x, int y, int z);

/// VECTOR FLOAT

typedef struct s_v2f
{
	float			x;
	float			y;
}					t_v2f;

typedef struct s_v3f
{
	float			x;
	float			y;
	float			z;
}					t_v3f;

t_v2f				ft_v2f(float x, float y);
t_v2f				*ft_v2fp(float x, float y);
t_v3f				ft_v3f(float x, float y, float z);
t_v3f				*ft_v3fp(float x, float y, float z);
t_v3f				ft_v3f_add(t_v3f v1, t_v3f v2);
t_v3f				ft_v3f_sub(t_v3f v1, t_v3f v2);
t_v3f				ft_v3f_mult(t_v3f v1, t_v3f v2);
t_v3f				ft_v3f_scale(t_v3f v1, float f);

// Vector unsigned long

typedef struct s_v2ul
{
	unsigned long	x;
	unsigned long	y;
}					t_v2ul;

typedef struct s_v3ul
{
	unsigned long	x;
	unsigned long	y;
	unsigned long	z;
}					t_v3ul;

t_v2ul				ft_v2ul(unsigned long x, unsigned long y);
t_v2ul				*ft_v2ulp(unsigned long x, unsigned long y);
t_v3ul				ft_v3ul(unsigned long x, unsigned long y, unsigned long z);
t_v3ul				*ft_v3ulp(unsigned long x, unsigned long y,
						unsigned long z);

#endif