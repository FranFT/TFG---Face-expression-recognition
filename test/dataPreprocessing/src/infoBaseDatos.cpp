#include "infoBaseDatos.h"

void infoBaseDatos::insertar_expresion(String expresion){
	this->expresiones.push_back(expresion);
}

infoBaseDatos::infoBaseDatos(int _ns, int _ne, const char* _nombre){
	this->nombre = _nombre;
	this->num_sujetos = _ns;
	this->num_expresiones = _ne;
}

void infoBaseDatos::imprime_info() const {
	cout << "-Nombre de la base de datos: " << this->nombre << endl;
	cout << "--Num. de sujetos: " << this->num_sujetos << endl;
	cout << "--Num. de expresiones: " << this->num_expresiones << endl;
	cout << "--Expresiones registradas: ";
	for(vector<String>::const_iterator it = this->expresiones.begin(); it!=this->expresiones.end(); ++it)
		(it+1==this->expresiones.end()) ? cout << (*it) << endl : cout << (*it) << ", ";
}

int infoBaseDatos::get_num_sujetos() const{
	return this->num_sujetos;
}

int infoBaseDatos::get_num_expresiones() const{
	return this->num_expresiones;
}

String infoBaseDatos::get_expresion(int _indice) const{
	return this->expresiones.at(_indice);
}
