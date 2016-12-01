#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randomFloat()
{
	srand(time(NULL));
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

typedef struct _Simplex
{
	// vertices values
	float val[3];

	// vertices
	float best[2];
	float good[2];
	float wrost[2];
} Simplex;

float fun(float x, float y){
	return x*x + y*y;
}

void set_values(float val, float x, float y, Simplex* simplex, char vertex){
	switch (vertex){
		case 'B':
			simplex->val[0] = val;
			simplex->best[0] = x;
			simplex->best[1] = y;
			break;
		case 'G':
			simplex->val[1] = val;
			simplex->good[0] = x;
			simplex->good[1] = y;
			break;
		default:
			simplex->val[2] = val;
			simplex->wrost[0] = x;
			simplex->wrost[1] = y;
	}
}

void init_simplex(Simplex* simplex){
	int i;
	
	float val[3];
	float vertices[3][2];
	
	for (i = 0; i < 3; ++i) {
		vertices[i][0] = randomFloat();
		vertices[i][1] = randomFloat();
		val[i] = fun(vertices[i][0], vertices[i][1]);
	}

	if (val[0] < val[1] && val[0] < val[2]) {
		simplex->val[0] = val[0];
		simplex->best
	}



}

int main(int argc, char const *argv[])
{
	Simplex* simplex = (Simplex*) malloc(sizeof(Simplex));

	simplex->val[0] = 0;
	simplex->best[0] = 0;
	simplex->best[0] = 0;

	
	
	return 0;
}