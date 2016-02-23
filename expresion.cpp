#include "expresion.h"

expresion::expresion(){
	tipo = static_cast<tipo_expresion>(0);
	size_training = 0.8;
	color = 0;
	ruta = "yalefaces/subject";
	formato = ".png";
}

expresion::expresion(tipo_expresion _tipo, float _size_training){
	tipo = static_cast<tipo_expresion>(_tipo);
	(_size_training >= 0.1 && _size_training < 1.0) ? size_training = _size_training : size_training = 0.8;
}

expresion::expresion(tipo_expresion _tipo, float _size_training, String _ruta, String _formato){
	tipo = static_cast<tipo_expresion>(_tipo);
	(_size_training >= 0.1 && _size_training < 1.0) ? size_training = _size_training : size_training = 0.8;
	ruta = _ruta;
	formato = _formato;
}

expresion::expresion(const expresion& obj){
	imagenes = obj.imagenes;
	muestra_training = obj.muestra_training;
	muestra_test = obj.muestra_test;
	tipo = obj.tipo;
	size_training = obj.size_training;
	color = obj.color;
	ruta = obj.ruta;
	formato = obj.formato;
}

String expresion::tipo_expresion2String(tipo_expresion _tipo){
	String salida;

	switch (_tipo)
	{
	case centerlight:
		salida = "centerlight";
		break;
	case glasses:
		salida = "glasses";
		break;
	case happy:
		salida = "happy";
		break;
	case leftlight:
		salida = "leftlight";
		break;
	case noglasses:
		salida = "noglasses";
		break;
	case normal:
		salida = "normal";
		break;
	case rightlight:
		salida = "rightlight";
		break;
	case sad:
		salida = "sad";
		break;
	case sleepy:
		salida = "sleepy";
		break;
	case surprised:
		salida = "surprised";
		break;
	case wink:
		salida = "wink";
		break;
	default:
		salida = "happy";
		break;
	}

	return salida;
}


bool expresion::cargar_expresion(tipo_expresion _tipo, bool _color, bool _salida){
	String _expresion = tipo_expresion2String(_tipo);
	String ruta_aux;
	Mat img_aux;
	bool exito = true;


	color = _color;
	for (int i = 1; i <= NUM_SUJETOS; i++){
		if (i<10)
			ruta_aux = ruta + "0" + to_string(i) + "." + _expresion + formato;
		else
			ruta_aux = ruta + to_string(i) + "." + _expresion + formato;

		img_aux = leeimagen(ruta_aux, color).clone();
		imagenes.push_back(img_aux);

		if (img_aux.data == NULL && _salida){
			cerr << "Error leyendo imagen correspondiente al sujeto " << i << endl;
			exito = false;
		}
		else if (img_aux.data != NULL & _salida)
			cout << "Leyendo imagen: " << ruta_aux << ", Dimensiones" << img_aux.cols << "-" << img_aux.rows << endl;			
	}


	return exito;
}