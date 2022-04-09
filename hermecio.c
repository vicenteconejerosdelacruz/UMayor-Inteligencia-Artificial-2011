/*
Fast Artificial Neural Network Library (fann)
Copyright (C) 2003 Steffen Nissen (lukesky@diku.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>

#include "fann.h"

int FANN_API test_callback(struct fann *ann, struct fann_train_data *train,
	unsigned int max_epochs, unsigned int epochs_between_reports, 
	float desired_error, unsigned int epochs)
{
	printf("Epochs     %8d. MSE: %.5f. Desired-MSE: %.5f\n", epochs, fann_get_MSE(ann), desired_error);
	return 0;
}

#define	N			3
#define PORTE_MAPA	((N)*(N))
#define NUM_SALIDAS	4
#define NUM_OCULTAS ((PORTE_MAPA + NUM_SALIDAS)>>1)

void entrena()
{
    const unsigned int num_input = PORTE_MAPA;
    const unsigned int num_output = NUM_SALIDAS;
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = NUM_OCULTAS;
    const float desired_error = (const float) 0.001;
    const unsigned int max_epochs = 500000;
    const unsigned int epochs_between_reports = 1000;
    struct fann *ann = fann_create_standard(num_layers, num_input,num_neurons_hidden, num_output);
    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
    fann_train_on_file(ann, "vale.data", max_epochs,epochs_between_reports, desired_error);
    fann_save(ann, "vale_float.net");
    fann_destroy(ann);
}

const char* salidas[]=
{
	"arriba",
	"abajo",
	"izquierda",
	"derecha"
};

const char* get_direccion(fann_type *direcciones)
{
	unsigned int	i;
	int direccion	= 0;
	float value		= -1000.0f;
	
	for(i=0;i<4;i++)
	{
		if(direcciones[i]>value)
		{
			value = direcciones[i];
			direccion = i;
		}
	}
	return salidas[direccion];
}

void prueba()
{
    fann_type *calc_out;
    fann_type input[PORTE_MAPA];
	unsigned int i,j;
    struct fann *ann = fann_create_from_file("vale_float.net");
	
	for(i=0;i<PORTE_MAPA;i++)
	{
		printf("%u:",i);
		scanf("%f",&input[i]);
	}

	printf("\n");

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%.0f\t",input[i*N + j]);
		}
		printf("\n");
	}

    calc_out = fann_run(ann, input);

	printf("ir a la %s",get_direccion(calc_out));

    fann_destroy(ann);
    return 0;
}

int main()
{
	//entrena();
	prueba();

	getchar();

	return 0;
}
