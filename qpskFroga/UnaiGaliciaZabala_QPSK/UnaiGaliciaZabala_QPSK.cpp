/* UnaiGaliciaZabala.cpp
* Egilea: Unai Galicia Zabala
* Haisera data: 23/03/2022
* Amaiera data: 25/03/2022
* */

#include <iostream>
#include <stdio.h>
#include <math.h>
#pragma warning(disable : 4996)	//Visual Studion scanf erabili ahal izateko

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
void divide(float* a, float* b, float* c, int elemkop);
void eskatuPositibo(int* par, int auk);
void eskatuBitak(float* m, int n);


int main()
{
	int fs, fc, vs, n;

	printf("%% QPSK  MODULATZAILEA %%\n");

	printf("SARTU BALIO POSITIBOAK\n");

	do {
		eskatuPositibo(&fs, 1);
		eskatuPositibo(&fc, 2);
		eskatuPositibo(&vs, 3);
	} while (fs <= 0 || fc <= 0 || vs <= 0);

										//fs, fc, vs eta n lortu. Balio positiboak eta 0 baino handiagoak direnak onartu soilik

	do {
		printf("BIT KOPURUA BIKOITIA IZAN BEHAR DA\n");
		eskatuPositibo(&n, 4);
	} while ((n % 2) != 0);				//Bitak lortu. 0 eta 1 balioak onartu soilik

	float tb = ((float)1 / (float)(2*vs)), tc = ((float)1/(float)fc), ts = ((float)1/(float)fs), t1 = 0, t2=tb;
										//periodo ezberdinak definitu


	float *m = erreserbatuFloat(n);
	eskatuBitak(m, n);					//erabiltzaileari bitak eskatu
	
										//Arrayen memoria erreserba
	float *t = erreserbatuFloat(fs);		//Garraiatzaile seinaleen denbora basea
	float* c1 = erreserbatuFloat(fs);		//cos garraiatzailea
	float* c2 = erreserbatuFloat(fs);		//sin garraiatzailea


	linspace(t, 0, tc, fs);				//denbora basea sortu


	sortuCar(t, c1, fc, tb, fs, 0);		//cos sortu
	sortuCar(t, c2, fc, tb, fs, 1);		//sin sortu

	free(t);

	nrzCoding(m, n);					//NRZ kodeketa aplikatu
	
	
	int n1 = n / 2;						//datuak bitan banatuko dira, beraz luzera erdia
	float* bak = erreserbatuFloat(n1);	//Arrayak erreserbatu alde bakoiti
	float* bik = erreserbatuFloat(n1);	//eta bikoitiarentzat

	divide(m, bak, bik, n);				//Banatu NRZ arraya bitan

										//Matrizeen erreserba
	float** odd = erreserbaMat(n1, fs);		//Alde bakoitiaren bit bakoitza (n1 bit) cos garraiatzailearekin biderkatuta, fs zutabe alegia
	float** even = erreserbaMat(n1, fs);	//Alde bikoitiaren bit bakoitza (n1 bit) sin garraiatzailearekin biderkatuta, fs zutabe alegia
	float** qpsk = erreserbaMat(n1, fs);	//Alde bakoitia eta bikoitia batuta
	float** times = erreserbaMat(n1, fs);	//Denbora basea QPSK matrizearentzat

										//Matrizeak 0ra hasieratu
	matrizeahasieratu(odd, n1, fs);
	matrizeahasieratu(even, n1, fs);
	matrizeahasieratu(qpsk, n1, fs);
	matrizeahasieratu(times, n1, fs);

	float* ms = erreserbatuFloat(fs);	//Laguntza arraya


	for(int i = 0 ; i<n1; i++){			//Begizta array bakoiti eta bikoitien elementu guztiak garraiatzaileekin biderkatzeko eta haien artean gehitzeko, QPSK sortzeko alegia
		
		linspace(times[i], t1, t2, fs);	//QPSK emaitza sinbolo bakoitzaren denbora basea

		//even...
		ones(ms, fs, bak[i]);			//Bakoitien elementu bat fs aldiz errepikatu, ms-n gorde
		lerroBete(odd, c1, ms, fs, i);	//Errepikatutako bakoitien elementua cos garraiatzailearen balioekin biderkatu
		
		//odd...
		ones(ms, fs, bik[i]);			//Bikoitien elementu bat fs aldiz errepikatu, ms-n gorde
		lerroBete(even, c2, ms, fs, i); //Errepikatutako bikoitien elementua sin garraiatzailearen balioekin biderkatu

		matrizeakGehitu(qpsk, odd, even, n1, fs);	//Bakoitiak eta bikoitiak gehitu QPSK lortzeko

		t1 = t1 + (tb + ts);			//QPSKren denbora basea eguneratu
		t2 = t2 + (tb + ts);
	}
										//Memoriatik askatu arrayak
	
	free(c1);
	free(c2);
	free(ms);
	free(m);
										//Memoriatik askatu arrayak
	askatuMatrizea(odd, n1);
	askatuMatrizea(even, n1);

	char fitxizen[12] = "csvFitx.csv";
	char denborak[] = "times.csv";

										//CSV fitxategiak idatzi QPSK eta denbora balioentzat
	csvFitxategia(fitxizen, qpsk, n1, fs);
	csvFitxategia(denborak, times, n1, fs);
	
	askatuMatrizea(times, n1);
	askatuMatrizea(qpsk, n1);
	
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

			res[i] = (float)(sqrt((float)2 / tb) * sin((double)((float)2 * PI * (float)fc * t[i])));

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
	
	FILE* pf;
	pf = fopen(fitxizen, "wb");

	if (pf != (FILE*)NULL) {

		for (int i = 0; i < lerrokop; i++) {
			for (int j = 0; j < zutkop; j++) {

				if (j == (zutkop - 1))
					fprintf(pf, "%f\n", mat[i][j]);

				else if (i == (lerrokop - 1) && j == (zutkop - 1))
					fprintf(pf, "%f", mat[i][j]);	//fwrite(&k, sizeof(char), 1, pf);
				else
					fprintf(pf, "%f, ", mat[i][j]);	//fwrite(&mat[i][j], sizeof(float), 1, pf);
			}
		}

		fclose(pf);

	}
}

void divide(float* a, float* b, float* c, int elemkop) {

	int aux = 1, j=0, k=0;
		
	for (int i = 0; i < elemkop; i++) {
			
		if (aux == 1) {
			b[j] = a[i];
			j++;
		}
		else {
			c[k] = a[i];
			k++;
		}
		
		aux = aux * -1;

	}

}

void eskatuPositibo(int *par, int auk) {

		if (auk == 1)
			printf("Sartu laginketa maiztasuna: ");
		else if (auk == 2)
			printf("Sartu garraiatzailearen maiztasuna: ");
		else if (auk == 3)
			printf("Sartu sinbolo abiadura: ");
		else
			printf("Sartu bit kopurua: ");

		scanf("%d", par);
		cout << '\n';
		
	

}

void eskatuBitak(float *m, int n) {

	printf("Joan bitak banan bana sartzen\n");

	for (int i = 0; i < n; i++) {
		do{
			printf("%d. bita: ", (i + 1));
			
			scanf("%f", &m[i]);

		} while (m[i] > (float)1 && m[i] > (float)0);
	}


}