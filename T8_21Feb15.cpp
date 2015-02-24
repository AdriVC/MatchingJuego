//Tarea 8 21 Feb 15
// Juego Matching Palabras
//Adriana Vega 11351101
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void ImprimirGuia(char***, int);
void ImprimirJuego(char**,char**, int);
void Posiciones(int*, int);
void Ordenamiento(char**, int, char***);
bool compare(char*, char*);

int main(int argc, char* argv[]){
	srand(time(0));
	int numero_palabras,numero_parejas=0;
	cout << "\nBIENVENIDO A EMPAREJAR PALABRAS:\nIngrese cuantas palabras principales tendra: ";
	cin >> numero_palabras;
	cout << "\nComienze a ingresar las soluciones en formato\n#:palabra\n\tr:pareja\n(nota: si no tiene pareja, coloque un guion \"-\")\n" << endl;
	char*** guia = new char**[numero_palabras];
	char* palabra;
	for (int i = 0; i < numero_palabras; ++i){
		guia[i] = new char*[2];
		cout << i+1 << ": ";
		palabra = new char[140];
		cin >> palabra;
		guia[i][0] = palabra;
		cout << "\tr: ";
		palabra = new char[140];
		cin >> palabra;
		if(palabra[0]!='-'){
			numero_parejas++;
		}
		guia[i][1] = palabra;
	}
	//mprimirGuia(guia,numero_palabras);

	char** juego_palabras = new char*[numero_palabras];
	int* shuffle_palabras = new int[numero_palabras];
	Posiciones(shuffle_palabras,numero_palabras);
	for (int i = 0; i < numero_palabras; ++i){
		juego_palabras[i] = guia[shuffle_palabras[i]][0];
	}
	
	char** juego_parejas = new char*[numero_palabras];
	Ordenamiento(juego_parejas,numero_palabras,guia);

	int resp1, resp2, aciertos;
	bool opcion= true;
	do{
		ImprimirJuego(juego_palabras,juego_parejas,numero_palabras);
		cout << "\n1- Ingrese una combinacion\n0- Salir\nQue desea hacer? ";
		cin >> opcion;
		if(opcion){
			cout << "\nIngrese una combinacion:\nNum Palabra: ";
			cin >> resp1;	
			cout << "Num Pareja: ";
			cin >> resp2;
			for (int i = 0; i < numero_palabras; ++i){
				if(compare(juego_palabras[resp1-1],guia[i][0]) && compare(juego_parejas[resp2-1],guia[i][1])){
					aciertos++;
					cout << "\n\tha acertado!" << endl;
				}
			}
		}
	}while(opcion);
	cout << "Su porcentaje de aciertos es " << setprecision(2) << (aciertos*100/numero_parejas) << "\%" << endl;

	for (int i = 0; i < numero_palabras; ++i){
		delete[] guia[i];
	}
	delete[] guia;
	cout << "ADIOS!\n" << endl;
	return 0;
}

void ImprimirGuia(char*** matriz, int num){
	cout << endl << "\tPALABRA:" << "\t\tPAREJA:" << endl;
	for (int i = 0; i < num; ++i){
		cout << "\t" << i+1 << ": " << matriz[i][0] << "\t\t" << i+1 << ": " << matriz[i][1] << endl;
	}
	cout << endl;
}

void ImprimirJuego(char** palabras, char** parejas, int num){
	cout << endl << "\tPALABRA:" << "\t\tPAREJA:" << endl;
	for (int i = 0; i < num; ++i){
		cout << "\t" << i+1 << ": " << palabras[i] << "\t\t";
		if(parejas[i][0] != '-') 
			cout << i+1 << ": " << parejas[i] << endl;
		else
			cout << endl;
	}
	cout << endl;
}

void Posiciones(int* arreglo, int tamano){
	int random, j=0;
	bool taken;
	while(j < tamano){
		taken = false;
		random = rand()%tamano;
		for (int i = 0; i < j; ++i){
			if(arreglo[i] == random)
				taken = true;
		}
		if(!taken){
			arreglo[j] = random;
			++j;
		}
	}
}

void Ordenamiento(char** lista, int tamano, char*** matriz){
	int j=0,k=0;
	for (int i = 0; i < tamano; ++i){
		if(matriz[i][1][0] != '-'){
			lista[j] = matriz[i][1];
			j++;
		} else{
			lista[tamano-1-k] = matriz[i][1];
			k++;
		}
	}
}

bool compare(char* one, char* two){
	bool todo = true;
	int i=0;
	while(one[i] != '\0' || two[i] != '\0'){
		if(one[i] != two[i])
			todo = false;
		i++;
	}
	return todo;
}

