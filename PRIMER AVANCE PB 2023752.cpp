#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<cstring>

using namespace std;

struct persona {
	char usuario[45] = "";
	char envios[30] = "";
	char producto[39] = "";
	long clave = 0;

};
int menu() {
	int x = 0;
	cout << "\tBienvenido a tienda digital, que desea hacer?\n\n";
	cout << "1.AGREGAR" << endl;
	cout << "2.LISTA" << endl;
	cout << "3.BUSCAR" << endl;
	cout << "4.ELIMINAR" << endl;
	cout << "5.MODIFICAR" << endl;
	cout << "6.SALIR" << endl;
	cout << "OPCION";
	cin >> x;
	return x;
}

long getLong(string mjs) {
	long m;
	cout << mjs << endl;
	cin >> m;
	return m;

}

string getString(string mjs) {
	string m;
	cout << mjs << endl;
	return m;

}

persona getPersona(long ced) {
	fstream e("archivo personas.bin", ios::binary | ios::trunc | ios::out);
	persona aux;
	if (e.is_open()) {
		e.seekg((ced - 1) * sizeof(persona));
		e.read((char*)&aux, sizeof(persona));
		e.close();
	}
	return aux;
}


void AGREGARusuario() {
	persona p;
	cin.ignore();
	strcpy_s(p.usuario, getString("ingresar usuario").c_str());
	strcpy_s(p.envios, getString("ingresar envios"). c_str());
	strcpy_s(p.producto, getString("ingresar producto").c_str());
	p.clave = getLong("clave");
	persona aux = getPersona(p.clave);
	if (aux.clave != 0) {
		cout << "registro ya existe" << endl;
	}
	else {
		fstream e("archivo personas.bin", ios::binary | ios::trunc | ios::out);
		if (e.is_open()) {
			e.seekp((p.clave - 1) * sizeof(persona));
			e.write((char*)&p, sizeof(persona));
			e.close();
		}
	}
}

void mostrar(persona p) {
	cout << "usuario---:" << p.usuario << endl;
	cout << "clave---:" << p.clave << endl;
	cout << "envios---:" << p.envios << endl;
	cout << "producto---:" << p.producto << endl;
	cout << "--------------------------" << endl;
}


void listaRegistro() {
	fstream e("archivo personas.bin", ios::binary | ios::trunc | ios::out);
	persona aux;
	if (e.is_open()) {
		e.read((char*)&aux, sizeof(persona));
		while (!e.eof()) {
			mostrar(aux);
			e.read((char*)&aux, sizeof(persona));
		}
		e.close();
	}
}

void buscarRegistro() {
	int long ced = getLong("digite el numero de la clave");
	persona aux = getPersona(ced);
	if (aux.clave == 0) {
		cout << "no existe registro" << endl;
	}
	else {
		mostrar(aux);
	}
}

void EliminarRegistro() {
	int long ced = getLong("digite el numero de la clave para eliminar");
	persona aux = getPersona(ced);
	if (aux.clave == 0) {
		cout << "no existe registro" << endl;
	}
	else {
		cout << "registro eliminado" << endl;
	}
}

void modicargistro() {
	int long ced = getLong("dijite la clave");
	persona aux = getPersona(ced);
	cin.ignore();
	if (aux.clave == 0) {
		cout << "no existe registro" << endl;
	}
	else {
		mostrar(aux);
		strcpy_s(aux.usuario, getString("ingresar usuario").c_str());
		strcpy_s(aux.envios, getString("ingresar envios").c_str());
		strcpy_s(aux.producto, getString("ingresar producto").c_str());
		fstream e("archivo personas.bin", ios::binary | ios::trunc | ios::out);
		if (e.is_open()) {
			e.seekp((aux.clave - 1) * sizeof(persona));
			e.close();
		}
	}
}


int main() {
	int x = 0;
	do {
		x = menu();
		switch (x) {
		case 1:
			AGREGARusuario();
			break;
		case 2:
			listaRegistro();
			break;
		case 3:
			buscarRegistro();
			break;
		case 4:
			EliminarRegistro();
			break;
		case 5:
			modicargistro();
			break;

		}
	} while (x != 6);
	return 0;
}

