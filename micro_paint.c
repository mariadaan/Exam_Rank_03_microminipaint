#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int	printnum(char *name, int num);
int	printchar(char *name, char c);
int	printfloat(char *name, float num);

typedef struct s_info
{
	int		bg_width;
	int		bg_height;
	char	bg_char;

	float	x_empty; // the horizontal position of the top left corner of the rectangle
	float	y_empty; // the vertical position of the top left corner of the rectangle
	float	width_empty; // >0
	float	height_empty; // >0
	char	r_borderrect;

	float	x_filled; // the horizontal position of the top left corner of the rectangle
	float	Y_filled; // the vertical position of the top left corner of the rectangle
	float	width_filled; // >0
	float	height_filled; // >0
	char	r_filledrect;


} t_info;

void print_2D(char **array, int height)
{
	for (int i = 0; i < height; i++)
	{
		printf("%s\n", array[i]);
	}
}

void print_file(FILE *fp)
{
	char s;
	while((s=fgetc(fp))!=EOF)
	{
		printf("%c",s);
	}
}

int parse_input(FILE *fp, t_info *info)
{
	char specifier;

	fscanf(fp, "%d %d %c", &info->bg_width, &info->bg_height, &info->bg_char);
	fscanf(fp, "\n%c ", &specifier);
	if (specifier == 'r')
	{
		fscanf(fp, "%f %f %f %f %c", &info->x_empty, &info->y_empty, &info->width_empty, &info->height_empty, &info->r_borderrect);
	}
	
	return (0);
}

void print_square(int width, int height, char c)
{
	int i_y = 0;

	while (i_y < height)
	{
		int i_x = 0;
		while (i_x < width)
		{
			write(1, &c, 1);
			i_x++;
		}
		write(1, "\n", 1);
		i_y++;
	}
}

char **create_matrix(int width, int height, char c)
{
	char **matrix;
	char *row;

	matrix = calloc(height, sizeof(char *));
	int i_y = 0;
	while (i_y < height)
	{
		row = calloc(width, sizeof(char));
		int i_x = 0;
		while (i_x < width)
		{
			row[i_x] = c;
			i_x++;
		}
		matrix[i_y] = row;
		i_y++;
	}
	return matrix;
}

int main(int argc, char *argv[])
{
	t_info info;
	FILE * fp;
	char **painting;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (0);
	}
	char *filename = argv[1];
	fp = fopen(filename, "r");
	// print_file(fp);
	parse_input(fp, &info);
	painting = create_matrix(info.bg_width, info.bg_height, info.bg_char);
	print_2D(painting, info.bg_height);
	printfloat("info.x_empty", info.x_empty);
	printfloat("info.width_empty", info.width_empty);

	// print_square(info.bg_width, info.bg_height, info.bg_char);
	// printnum("\nwidth", info.bg_width);
	// printnum("\nbg_height", info.bg_height);
	// printchar("\nbg_char", info.bg_char);


}