#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct s_info
{
	int bg_width;
	int bg_height;
	char bg_char;
	char rect_type;
	float x_rect;
	float y_rect;
	float rect_width;
	float rect_height;
	float rect_char;
} t_info;

char **create_matrix(int width, int height, char bg_char)
{
	int i_y = 0;
	char **matrix;

	matrix = (char **)calloc(height + 1, sizeof(char*));
	
	while (i_y < height)
	{
		matrix[i_y] = (char *)calloc(width + 1, sizeof(char));
		memset(matrix[i_y], bg_char, width);
		i_y++;
	}
	return (matrix);
}

void get_bg(FILE *fp, t_info *info)
{
	fscanf(fp, "%d %d %c\n", info->bg_width, info->bg_height, info->bg_char);
}

void get_rects(FILE *fp, t_info *info, char **matrix)
{
	while (fscanf(fp, "%c %f %f %f %f %c\n", info->rect_type, info->x_rect, info->y_rect, info->rect_width, info->rect_height, info->rect_char) != EOF)
		draw_rect(matrix, info);
}

int in_rect();
int is_border();

void draw_rect(char **matrix, t_info *info)
{
	int i_x = 0;
	int i_y = 0;

	while (i_y < 0)
}

int main (int argc, char *argv[])
{
	FILE *fp;
	t_info info;
	char **matrix;

	if (argc != 2)
		write(1, "Error: argument\n", 17);
	char *filename = argv[1];
	fp = fopen(filename, "r");
	get_bg(fp, &info);
	matrix = create_matrix(info.bg_width, info.bg_height, info.bg_char);
	get_rects(fp, &info, matrix);

}