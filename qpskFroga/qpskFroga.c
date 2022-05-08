// qpskFroga.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//



#include <iostream>
#include <cstdlib>
#include <fstream>

#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)

# define PI   3.14159

using namespace std;

int* erreserbatuMem(int tam);
float* erreserbatuFloat(int tam);
void linspace(float* res, float min, float max, int step);
void sortuCar(float* t, float* res, int fc, float tb, int fs, int auk);
void nrzCoding(float* data, int luz);
float** erreserbaMat(int lerroKop, int zutKop);
void ones(float* m, int elemkop, float val);
void lerroBete(float** m, float* a, float* b, int zutkop, int lerro);
void matrizeakGehitu(float** m, float** m1, float** m2, int lerrokop, int zutkop);
void matrizeahasieratu(float** m, int lerrokop, int zutkop);
void askatuMatrizea(float** m, int lerrokop);
void csvFitxategia(char* fitxizen, float** mat, int lerrokop, int zutkop);
void twodarray2csv(float** m, char* filename, int lerrokop, int zutkop);

int main()
{
	int fs = 48000, fc = 3000, vs = 750, n = 8;

	float tb = ((float)1 / (float)vs), tc = ((float)1/(float)fc), ts = ((float)1/(float)fs), t1 = 0, t2=tb;

	float *m = erreserbatuFloat(8);
	
	for (int i = 0; i < 8; i++) {
		m[i] = (float)round((rand()%2));
		printf("%f\n", m[i]);
	}

	
	float *t = erreserbatuFloat(fs);
	float* c1 = erreserbatuFloat(fs);
	float* c2 = erreserbatuFloat(fs);

	linspace(t, 0, tc, fs);


	sortuCar(t, c1, fc, tb, fs, 0); //cos
	sortuCar(t, c2, fc, tb, fs, 1); //sin

	nrzCoding(m, 8);

	float** odd = erreserbaMat(n, fs);
	float** even = erreserbaMat(n, fs);
	float** qpsk = erreserbaMat(n, fs);

	matrizeahasieratu(odd,n, fs);
	matrizeahasieratu(even, n, fs);
	matrizeahasieratu(qpsk, n, fs);


	float* ms = erreserbatuFloat(fs);


	for(int i =0 ; i<(n-1); i+=2){
		
		linspace(t, t1, t2, fs);

		//even...
		ones(ms, fs, m[i]);
		lerroBete(odd, c1, ms, fs, i);
		
		//odd...
		ones(ms, fs, m[i + 1]);
		lerroBete(even, c2, ms, fs, i);

		matrizeakGehitu(qpsk, odd, even, n, fs);

		t1 = t1 + (tb + ts);
		t2 = t2 + (tb + ts);
	}
	

	free(t);
	free(c1);
	free(c2);
	free(ms);
	free(m);

	askatuMatrizea(odd, n);
	askatuMatrizea(even, n);

	char fitxizen[12] = "csvFitx.txt";

	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < fs; j++) {
			printf("%f ", qpsk[i][j]);
		}
		cout << '\n';
	}*/

	//twodarray2csv(qpsk, fitxizen, n, fs);

	csvFitxategia(fitxizen, qpsk, n, fs);

	askatuMatrizea(qpsk, n);

	/*for (int i = 0; i < 8; i++) {

	}

									
	


	cout << '\n';

	for (int i = 0; i < fs; i++) {

		printf("%f \n", c1[i]);

	}

	

	
	
	
	cout << '\n';

	for (int i = 0; i < fs; i++)
		printf("%f \n", t[i]);
	*a/
	

	free(m);
	//free(t);
	free(c1);
	free(c2);

	*/

}


int* erreserbatuMem(int tam) {

	int* a;

	a = (int*)malloc(tam * sizeof(int));

	return a;

}

float* erreserbatuFloat(int tam) {

	float* a;

	a = (float*)malloc(tam * sizeof(float));

	return a;

}

void linspace(float* res, float min, float max, int step) {

	float aux = ((max - min) / (step - 1));

	res[0] = min;

	for (int i = 1; i < (step); i++) {

		res[i] = res[i-1] + aux;
		
		if (i == (step - 1))
			res[i] = max;

	}


}

void sortuCar(float* t, float* res, int fc, float tb, int fs, int auk) {

	if(auk == 0){

		for (int i = 0; i < fs; i++) {

			res[i] = (float)(sqrt((float)2 / tb) * cos((double)((float)2 * PI * (float)fc * t[i])));

		}
	}
	else {

		for (int i = 0; i < fs; i++) {

			res[i] = (float)(sqrt((float)2 / tb) * sin((float)2 * PI * (float)fc * t[i]));

		}

	}

}

float** erreserbaMat(int lerroKop, int zutKop) {

	float** m;

	m = (float**)malloc(lerroKop * sizeof(float*));
	for (int i = 0; i < lerroKop; i++)
		m[i] = (float*)malloc(zutKop * sizeof(float));
	return m;

}

void nrzCoding(float* data, int luz) {

	for (int i = 0; i < luz; i++) {

		if (data[i] == (float)0){
			data[i] = (float) -1;
		}

	}

}

void ones(float* m, int elemkop, float val) {

	for (int i = 0; i < elemkop; i++)
		m[i] = val;

}

void lerroBete(float** m, float* a, float*b, int zutkop, int lerro){

	for (int i = 0; i < zutkop; i++) {

		m[lerro][i] = a[i]*b[i];

	}

}

void matrizeahasieratu(float** m, int lerrokop, int zutkop) {
	
	for (int i = 0; i < lerrokop; i++) {
		for (int j = 0; j < zutkop; j++)
			m[i][j] = (float)0;

	}

}

void matrizeakGehitu(float** m, float** m1, float** m2, int lerrokop, int zutkop) {

	for (int i = 0; i < lerrokop; i++) {

		for (int j = 0; j < zutkop; j++)
			m[i][j] = m1[i][j] + m2[i][j];

	}



}

void askatuMatrizea(float** m, int lerrokop) {

	for (int i = 0; i < lerrokop; i++)
		free(m[i]);
	free(m);

}

void csvFitxategia(char* fitxizen, float** mat, int lerrokop, int zutkop) {

	char k = ' ';
	//float* buffer = erreserbatuFloat(zutkop);
	FILE* pf;
	pf = fopen(fitxizen, "wb");

	if(pf!=(FILE*)NULL){

		for (int i = 0; i < lerrokop; i++) {
			for (int j = 0; j < zutkop; j++){
				fprintf(pf, "%f,", mat[i][j]);//fwrite(&mat[i][j], sizeof(float), 1, pf);
				if (i != (lerrokop - 1) && j != (zutkop - 1))
					fprintf(pf, "%f", mat[i][j]);//fwrite(&k, sizeof(char), 1, pf);
			}
		}

		fclose(pf);

	}




}

void twodarray2csv(float**m, char* filename, int lerrokop, int zutkop)
{
	std::ofstream myfile;
	myfile.open(filename);

	for (int i = 0; i < lerrokop; ++i)
	{
		for (int j = 0; j < zutkop; ++j)
			if (j < (zutkop - 1)) {
				myfile << m[i][j] << ",";
			}
			else if (j == (zut - 1)) {
				myfile << m[i][j] << "\n";
			}
	}
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
