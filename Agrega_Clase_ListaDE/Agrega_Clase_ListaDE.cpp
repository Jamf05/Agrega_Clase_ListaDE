// Agrega_Clase_ListaDE.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "iostream"

using namespace System;
using namespace std;

struct nodo
{
	int dato;
	nodo *ant;
	nodo *sig;
};

class Lde
{
private:
	nodo *inicial;
	nodo *buscarLista(int clave);
public:
	Lde();
	~Lde();
	void agregar();
	void eliminar(int &codigo);
	void desplegarLista();
};

Lde::Lde()
{
	inicial = NULL;
}

Lde::~Lde()
{
	nodo *apun = inicial;
	while (apun != NULL)
	{
		inicial = apun->sig;
		delete apun;
		apun = inicial;
	}
}

void Lde::desplegarLista()
{
	if (inicial == NULL)
	{
		cout << "La lista esta vacia" << endl;
	}
	else
	{
		nodo *apunt;
		apunt = inicial;
		while (apunt != NULL)
		{
			cout << apunt->dato << endl;
			apunt = apunt->sig;
		}
	}
}

nodo *Lde::buscarLista(int clave)
{
	nodo *anterior;
	anterior = NULL;
	if (clave <= inicial->dato) //Si es verdad significa que debe ir de primero
	{
		return anterior;
	}
	else
	{
		anterior = inicial;
		while ((anterior->sig != NULL) && (clave > anterior->sig->dato)) //Ya no es NULL si no inicial
		{
			//Aqui compara el valor de cada dato
			anterior = anterior->sig;
		}
		return anterior;
	}
}

void Lde::eliminar(int &codigo)
{
	nodo *apun;
	nodo *aux;
		apun = buscarLista(codigo);
		aux = inicial;
		if (apun == NULL) //Es por que es el primero el que voy a eliminar
		{
			if (aux->dato == codigo)
			{
				inicial = aux->sig;
				inicial->ant = NULL;
				delete aux;
			}
			else
			{
				cout << "El nodo a eliminar no existe" << endl;
			}
		}
		else
		{
			if (apun->sig!= NULL) // Si es verdadero es porque codigo es menor que el maximo codigo entre los nodos
			{                    // Y apun seguira apuntando al nodo que antecede al eliminar
				if (apun->sig->dato == codigo && apun->sig->sig != NULL) //Corrobora q no sea el ultimo
				{
					//aux nodo a eliminar
					aux = apun->sig;
					apun->sig = aux->sig;
					aux->sig->ant = apun;
					delete aux;
				}
				else //Eliminar el ultimo
				{
					aux = apun->sig;
					apun->sig = NULL;
					delete aux;
				}
			}
			else  //De lo contrario es porque codigo es mayor y apun sera igual al ultimo nodo
			{
				cout << "El nodo a eliminar no existe" << endl;
			}
		}
}

void Lde::agregar()
{
	nodo *nuevo, *anterior;
	char resp;
	do
	{
		nuevo = new nodo();
		cout << "Entre clave del nodo a agregar" << endl;
		cin >> nuevo->dato;
		if (inicial == NULL)
		{
			//Agregar el primer nodo a la lista
			inicial = nuevo;
			nuevo->ant = NULL;
			nuevo->sig = NULL;
		}
		else
		{
			//Agrega a una lista que contiene al menos un nodo
			anterior = buscarLista(nuevo->dato);
			if (anterior == NULL)
			{
				//Agregar un nodo que queda de primero
				//en unal ista que no estaba vacia
				if (nuevo->dato == inicial->dato) cout << "El nodo a agregar ya existe" << endl;
				else
				{
					nuevo->sig = inicial;
					nuevo->ant = inicial->ant;
					inicial->ant = nuevo;
					inicial = nuevo;
				}
			}
			else
			{
				//
				if (anterior->sig != NULL)
				{
					//Agregs un nodo que queda entre el
					//primero y el ultimo
					if (nuevo->dato == anterior->sig->dato) cout << "El nodo a agregar ya existe" << endl;
					else
					{
						nuevo->sig = anterior->sig;
						nuevo->ant = anterior;
						anterior->sig->ant = nuevo;
						anterior->sig = nuevo;
					}
				}
				else
				{
					//Agregar un nodo que queda de ultimo
					//[...]
					nuevo->sig = anterior->sig;
					nuevo->ant = anterior;
					anterior->sig = nuevo;
				}
			}
		}
		cout << "Desea agregar otro nodo? (s/n)" << endl;
		cin >> resp;
		resp = tolower(resp);
	} while (resp == 's');
}

void main()
{
	Lde l;
	l.agregar();
	l.desplegarLista();
	char resp;
	int codigo;
	do
	{
		cout << endl;
		cout << "Entre codigo clave (Digite codigo a eliminar)" << endl;
		cin >> codigo;
		l.eliminar(codigo);
		cout << "Desea eliminar otro nodo (s/n)" << endl;
		cin >> resp;
		resp = tolower(resp);
	} while (resp == 's');
	l.desplegarLista();

	system("Pause");
}
