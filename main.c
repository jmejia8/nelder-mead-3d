#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randomFloat(int seed)
{
	srand(time(NULL) + seed);
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
		case 'b':
			simplex->val[0] = val;
			simplex->best[0] = x;
			simplex->best[1] = y;
			break;
		case 'g':
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

void print_simplex(Simplex* simplex){
	printf("=============================================\n");
	printf("f(%f, %f) = %f\n", simplex->best[0], simplex->best[1], simplex->val[0]);
	printf("f(%f, %f) = %f\n", simplex->good[0], simplex->good[1], simplex->val[1]);
	printf("f(%f, %f) = %f\n",simplex->wrost[0], simplex->wrost[1],simplex->val[2]);
}

void init_simplex(Simplex* simplex, int values){
	int i, b, g, w;
	
	float val[3];
	float vertices[3][2];

	if (values){
		for (i = 0; i < 3; ++i) {
			vertices[i][0] = randomFloat(i);
			vertices[i][1] = vertices[i][0] / (i + 2);
			val[i] = fun(vertices[i][0], vertices[i][1]);
		}
	}else{
		for (i = 0; i < 3; ++i) {
			val[i] = simplex->val[i];
			if (i == 0){
				vertices[i][0] = simplex->best[0];
				vertices[i][1] = simplex->best[1];
			} else if (i == 1){
				vertices[i][0] = simplex->good[0];
				vertices[i][1] = simplex->good[1];
			} else {
				vertices[i][0] = simplex->wrost[0];
				vertices[i][1] = simplex->wrost[1];
			}
		}
	}

	// coloca el mejor, el bueno y el peor valor
	if (val[0] < val[1] && val[0] < val[2]) {
		b = 0;
		if (val[1] < val[2]){ g = 1; w = 2; } else { g = 2; w = 1; }

	} else if (val[1] < val[0] && val[1] <= val[2]) {
		b = 1;
		if (val[0] < val[2]){ g = 0; w = 2; } else { g = 2; w = 0; }

	} else {
		b = 2;
		if (val[0] < val[1]){ g = 0; w = 1; } else { g = 1; w = 0; }
	}


	set_values(val[b], vertices[b][0], vertices[b][1], simplex, 'b');
	set_values(val[g], vertices[g][0], vertices[g][1], simplex, 'g');
	set_values(val[w], vertices[w][0], vertices[w][1], simplex, 'w');

}

void nelder_mead(Simplex* simplex, int max_iter){
	float R[2], R_val, M[2], M_val;
	int i;

	for (int i = 0; i < max_iter; ++i) {
		R[0] = simplex->best[0] + simplex->good[0] - simplex->wrost[0];
		R[1] = simplex->best[1] + simplex->good[1] - simplex->wrost[1];
		R_val = fun(R[0], R[1]);

		M[0] = (simplex->best[0] + simplex->good[0])/2;
		M[1] = (simplex->best[1] + simplex->good[1])/2;

		if (R_val < simplex->val[1]) {
			if (simplex->val[0] < R_val)
				set_values(R_val, R[0], R[1], simplex, 'w');
			else{
				float E[2], E_val;
				E[0] = 2*R[0] - M[0];
				E[1] = 2*R[1] - M[1];
				E_val = fun(E[0], E[1]);

				if (E_val < simplex->val[0])
					set_values(E_val, E[0], E[1], simplex, 'w');
				else
					set_values(R_val, R[0], R[1], simplex, 'w');
			}
		} else {
			if (R_val < simplex->val[2])
				set_values(R_val, R[0], R[1], simplex, 'w');
			else {
				float C[2], C_val;
				C[0] = (R[0] + M[0]) * 0.5;
				C[1] = (R[1] + M[1]) * 0.5;
				C_val = fun(C[0], C[1]);
				
				if (C_val < simplex->val[2])
					set_values(C_val, C[0], C[1], simplex, 'w');
				else{
					float S[2], S_val;
					S[0] = (simplex->wrost[0] + simplex->good[0]) * 0.5;
					S[1] = (simplex->wrost[1] + simplex->good[1]) * 0.5;
					S_val = fun(S[0], S[1]);
					set_values(S_val, S[0], S[1], simplex, 'w');
					set_values(S_val, M[0], M[1], simplex, 'g');
				}
			}
		}

		init_simplex(simplex, 0);
		// print_simplex(simplex);

	}
}

int main(int argc, char const *argv[])
{
	Simplex* simplex = (Simplex*) malloc(sizeof(Simplex));

	init_simplex(simplex, 1);

	print_simplex(simplex);
	nelder_mead(simplex, 100);
	print_simplex(simplex);

	
	
	return 0;
}