/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

const int pointLocationx = SCREEN_WIDTH - (SCREEN_WIDTH * 0.2);
const int pointLocationy = SCREEN_HEIGHT / 2;

struct matrix
{
	int x;
	int y;
} typedef matrix_t;

matrix_t grid[8][8];

void init_grid_vals(SDL_Renderer *s)
{
	int max_x = SCREEN_WIDTH - (SCREEN_WIDTH * 0.127);
	int max_y = SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.17);
	int min_x = SCREEN_WIDTH - max_x;
	int min_y = SCREEN_HEIGHT - max_y;

	int size_x = max_x - min_x;
	int size_y = max_y - min_y;
	int pos_x = 0;
	int pos_y = 0;
	int cell_x = size_x / 8;
	int cell_y = size_y / 8;
	int i = 0, j = 0;

	/*SDL_RenderDrawPoint(s, min_x, min_y);
	SDL_RenderDrawPoint(s,max_x, min_y);
	SDL_RenderDrawPoint(s, min_x, max_y);
	SDL_RenderDrawPoint(s, max_x, max_y);

	SDL_RenderDrawLine(s, min_x, min_y, max_x, min_y);
	SDL_RenderDrawLine(s, min_x, max_y, max_x , max_y);
	SDL_RenderDrawLine(s, min_x, min_y, min_x, max_y);
	SDL_RenderDrawLine(s, max_x, min_y, max_x, max_y);*/

	pos_y = min_y;
	for (i = 0; i < 8; i++)
	{
		pos_x = cell_x;
		for (j = 0; j < 8; j++)
		{
			pos_x += cell_x;
			grid[i][j].x = pos_x;
			grid[i][j].y = pos_y;
		}
		pos_y += cell_y;
	}

	// Set the color to what was before
	//SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
}

void print_matrix(SDL_Renderer *s)
{
	int i = 0, j = 0;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 7; j++)
		{
			SDL_RenderDrawLine(s, grid[i][j].x, grid[i][j].y, grid[i][j+1].x, grid[i][j].y);
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
		}
	}

	i = 0;
	j = 0;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 8; j++)
		{
			SDL_RenderDrawLine(s, grid[i][j].x, grid[i][j].y, grid[i][j].x, grid[i+1][j].y);
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
		}
	}
}

void isometric_wea(void)
{
	int i = 0, j = 0;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			grid[i][j].x = 0.7 * grid[i][j].x - 0.7 * grid[i][j].y;
			grid[i][j].y = (1 - 0.7) * grid[i][j].x + (1 - 0.7) * grid[i][j].y - 1;
		}
	}
}

int main(int argc, char *args[])
{
	//The window we'll be rendering to
	SDL_Window *window = NULL;

	//The surface contained by the window
	SDL_Surface *screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{

			SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			//Get window surface
			//screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x15, 0xE7, 0xFF ) );

			//Update the surface
			//SDL_UpdateWindowSurface( window );

			//Wait two seconds
			//SDL_Delay( 2000 );

			// We clear what we draw before
			SDL_SetRenderDrawColor(s, 59, 44, 107, 255);
			SDL_RenderClear(s);
			// Set our color for the draw functions
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
			// Now we can draw our point
			init_grid_vals(s);
			//isometric_wea();
			print_matrix(s);
			// Set the color to what was before
			// .. you could do some other drawing here
			// And now we present everything we draw after the clear.
			SDL_RenderPresent(s);
			SDL_Delay(20000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
