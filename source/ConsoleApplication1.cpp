#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <chrono> 

using namespace std;
using namespace std::chrono;	

typedef long long ll;
typedef vector<vector<ll>> matrizll;
typedef vector<ll> vectorll;

struct tarea_aea
{	
	ll filas, dimensiones;

	matrizll matrix_1;

	vectorll vec_filas;
	vectorll vec_dimensiones;

	tarea_aea(vectorll vec_filas, vectorll vec_dimensiones)
	{
		this->vec_filas = vec_filas;
		this->vec_dimensiones = vec_dimensiones;

		for (size_t i = 0; i < vec_filas.size(); i++)
		{
			for (size_t j = 0; j < vec_dimensiones.size(); j++)
			{
				generador(i, j);
			}
		}
	}

	void generador(ll i, ll j)
	{
		filas = vec_filas[i];
		dimensiones = vec_dimensiones[j];

		matrix_1.resize(filas);

		rellenarAleatorio(matrix_1);

		escribir();
	}

	void rellenarAleatorio(matrizll& m_vec)
	{
		ll n = m_vec.size();

		for (size_t i = 0; i < filas; i++)
		{
			m_vec[i].resize(dimensiones);
			for (size_t j = 0; j < dimensiones; j++)
			{
				m_vec[i][j] = rand() % 10;
			}
		}
	}

	void distEuc(vectorll a, vectorll b)
	{
		ll sumZ = 0;
		for (size_t i = 0; i < a.size(); i++)
			sumZ += pow(b[i] - a[i], 2);
		sqrt(sumZ);
	}
	
	void escribir()
	{
		ofstream archivo;
		string fileName = to_string(filas) + "__" + to_string(dimensiones);
		archivo.open(fileName + ".txt", ios::out);
		if (archivo.fail())
		{
			cout << "No se abrio el file";
			exit(1);
		}
		archivo << "filas: " << filas << endl;
		archivo << "dimensiones: " << dimensiones << endl;
		archivo << endl;
		//archivo << "i_VS_j -> DistanciaEuclidiana" << endl;

	/*	for (size_t i = 0; i < filas; i++)
		{
			for (size_t j = i + 1; j < filas; j++)
			{
				archivo << i << "_VS_" << j << " -> ";
				archivo << distEuc(matrix_1[i], matrix_1[j]) << endl;
			}
		}*/
		//////////////////////////////////////////
		

		auto start = high_resolution_clock::now();

		for (size_t i = 0; i < filas; i++)
		{
			for (size_t j = i + 1; j < filas; j++)
			{
				distEuc(matrix_1[i], matrix_1[j]);
			}
		}
		
		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<microseconds>(stop - start);

		archivo << "Tiempo tomado: " << duration.count() << " microsegundos" << endl;

		archivo.close();
	}
};


int main()
{
	srand(time(NULL));

	vectorll filas{ 10000, 20000, 15000, 25000 };
	vectorll dimensiones{ 4,6,8,10,12,18,20 };

	/*vectorll filas{ 10, 15, 20, 25 };
	vectorll dimensiones{ 4, 6 };*/

	tarea_aea task(filas, dimensiones);
	return 0;
}