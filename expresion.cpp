#include "expresion.h"

expresion::expresion(){
	tipo = static_cast<tipo_expresion>(0);
	size_training = 0.8;
	color = false;
	salida = false;
	ruta = "yalefaces/subject";
	formato = ".png";
}

expresion::expresion(tipo_expresion _tipo, float _size_training, String _ruta, String _formato){
	tipo = static_cast<tipo_expresion>(_tipo);
	(_size_training >= 0.1 && _size_training < 1.0) ? size_training = _size_training : size_training = 0.8;
	color = false;
	salida = false;
	ruta = _ruta;
	formato = _formato;

	cargar_expresion(tipo, color);
}

expresion::expresion(const expresion& obj){
	imagenes = obj.imagenes;
	muestra_training = obj.muestra_training;
	muestra_test = obj.muestra_test;
	tipo = obj.tipo;
	size_training = obj.size_training;
	color = obj.color;
	salida = obj.salida;
	ruta = obj.ruta;
	formato = obj.formato;
}

void expresion::set_salida_por_pantalla(bool _salida){
	salida = _salida;
}

void expresion::print_tipo_expresion(){
	cout << tipo_expresion2String(tipo) << endl;
}


void expresion::print_muestras(){
	cout << "Training: " << size_training * 100 << "% Test: " << 100 - (size_training * 100) << "%:" << endl;
	cout << "Training: ";
	for (int i = 0; i < muestra_training.size(); i++)
		cout << muestra_training.at(i) << ", ";
	cout << endl << "Test: ";
	for (int i = 0; i < muestra_test.size(); i++)
		cout << muestra_test.at(i) << ", ";
	cout << endl;
}

String expresion::tipo_expresion2String(tipo_expresion _tipo){
	String cadena_salida;

	switch (_tipo)
	{
	case centerlight:
		cadena_salida = "centerlight";
		break;
	case glasses:
		cadena_salida = "glasses";
		break;
	case happy:
		cadena_salida = "happy";
		break;
	case leftlight:
		cadena_salida = "leftlight";
		break;
	case noglasses:
		cadena_salida = "noglasses";
		break;
	case normal:
		cadena_salida = "normal";
		break;
	case rightlight:
		cadena_salida = "rightlight";
		break;
	case sad:
		cadena_salida = "sad";
		break;
	case sleepy:
		cadena_salida = "sleepy";
		break;
	case surprised:
		cadena_salida = "surprised";
		break;
	case wink:
		cadena_salida = "wink";
		break;
	default:
		cadena_salida = "happy";
		break;
	}

	return cadena_salida;
}


bool expresion::cargar_expresion(tipo_expresion _tipo, bool _color){
	String _expresion = tipo_expresion2String(_tipo);
	String ruta_aux;
	Mat img_aux;
	bool exito = true;

	if (!imagenes.empty()){
		imagenes.clear();
		muestra_training.clear();
		muestra_test.clear();

		if (salida)
			cout << "Limpiando imagenes anteriores..." << endl;
	}

	tipo = _tipo;
	color = _color;

	for (int i = 1; i <= NUM_SUJETOS; i++){
		if (i<10)
			ruta_aux = ruta + "0" + to_string(i) + "." + _expresion + formato;
		else
			ruta_aux = ruta + to_string(i) + "." + _expresion + formato;

		img_aux = leeimagen(ruta_aux, color).clone();
		imagenes.push_back(img_aux);

		if (img_aux.data == NULL && salida){
			cerr << "Error leyendo imagen correspondiente al sujeto " << i << endl;
			exito = false;
		}
		else if (img_aux.data != NULL & salida)
			cout << "Leyendo imagen: " << ruta_aux << ", Dimensiones" << img_aux.cols << "-" << img_aux.rows << endl;			
	}

	exito = generar_muestras(size_training);
	generar_fichero_background_samples();

	return exito;
}

bool expresion::generar_muestras(float _size_training){
	
	if (imagenes.empty()){
		if (salida)
			cerr << "ERROR: No hay imagenes cargadas. Debe cargarse una expresion en primer lugar." << endl;
		return false;
	}
	else{
		muestra_training.clear();
		muestra_test.clear();

		srand(time(NULL));
		vector<int> lista_indices;

		size_training = _size_training;

		for (int i = 0; i < imagenes.size(); i++)
			lista_indices.push_back(i);

		random_shuffle(lista_indices.begin(), lista_indices.end());

		for (int i = 0; i < lista_indices.size(); i++)
			if (i < ceil(lista_indices.size()*size_training))
				muestra_training.push_back(lista_indices.at(i));
			else
				muestra_test.push_back(lista_indices.at(i));

		if (salida){
			cout << "Training: " << size_training * 100 << "% Test: " << 100 - (size_training * 100) <<"%:"<<endl;
			cout << "Training: ";
			for (int i = 0; i < muestra_training.size(); i++)
				cout << muestra_training.at(i) << ", ";
			cout << endl << "Test: ";
			for (int i = 0; i < muestra_test.size(); i++)
				cout << muestra_test.at(i) << ", ";
			cout << endl;
		}

	}

	return true;
}

void expresion::generar_fichero_background_samples(){
	ofstream fichero;
	String nombre_fichero = "bg_" + tipo_expresion2String(tipo) + ".txt";
	String nombre_muestra;
	fichero.open(nombre_fichero, ios::out | ios::trunc);

	for (int i = 0; i < NUM_EXPRESIONES; i++){
		if (i != static_cast<int>(tipo)){
			for (int j = 1; j <= NUM_SUJETOS; j++){
				if (j < 10)
					nombre_muestra = ruta + "0" + to_string(j) + "." + tipo_expresion2String(static_cast<tipo_expresion>(i))+".png";
				else
					nombre_muestra = ruta + to_string(j) + "." + tipo_expresion2String(static_cast<tipo_expresion>(i)) + ".png";

				fichero << nombre_muestra << endl;
			}
		}
	}

	fichero.close();
}