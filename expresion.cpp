#include "expresion.h"

expresion::expresion(){
	tipo = static_cast<tipo_expresion>(0);
	size_training = 0.8;
	color = false;
	salida = false;
	region_cara_defecto = Rect2i(0, 0, 0, 0);
	ruta = "yalefaces/subject";
	formato = ".png";
	ruta_clasificador_xml = "C:/opencv/sources/data/haarcascades/";
	clasificador_defecto = "haarcascade_frontalface_alt.xml";
}

expresion::expresion(tipo_expresion _tipo, float _size_training, String _ruta, String _formato){
	tipo = static_cast<tipo_expresion>(_tipo);
	(_size_training >= 0.1 && _size_training < 1.0) ? size_training = _size_training : size_training = 0.8;
	color = false;
	salida = false;
	region_cara_defecto = Rect2i(0, 0, 0, 0);
	ruta = _ruta;
	formato = _formato;
	ruta_clasificador_xml = "C:/opencv/sources/data/haarcascades/";
	clasificador_defecto = "haarcascade_frontalface_default.xml";


	cargar_expresion(tipo, color);
}

void expresion::set_salida_por_pantalla(bool _salida){
	salida = _salida;
}

void expresion::set_clasificador_defecto(String _nombre){
	clasificador_defecto = _nombre;
}

String expresion::get_clasificador_defecto(){
	return clasificador_defecto;
}

void expresion::print_tipo_expresion(){
	cout << tipo_expresion2String(tipo) << endl;
}

void expresion::print_muestras(){
	cout << "Training: " << size_training * 100 << "% Test: " << 100 - (size_training * 100) << "%:" << endl;
	cout << "Training: ";
	for (int i = 0; i < muestra_training.size(); i++)
		cout << muestra_training.at(i) << ", ";
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

bool expresion::cargar_expresion(tipo_expresion _tipo, bool _optimizar_region, bool _color){
	String _expresion = tipo_expresion2String(_tipo);
	String ruta_aux;
	Mat img_aux;
	bool exito = true;

	if (!imagenes.empty()){
		imagenes.clear();
		muestra_training.clear();
		region_cara.clear();
		region_cara_defecto = Rect2i(0, 0, 0, 0);

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
	region_cara_defecto = Rect2i(0, 0, img_aux.size().width, img_aux.size().height);

	exito = generar_muestras(size_training);
	if (_optimizar_region)
		optimizar_region_cara(clasificador_defecto);
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
		muestra_training = vector<int>(imagenes.size());

		//srand(time(NULL));
		srand(SEMILLA_ALEATORIA);
		vector<int> lista_indices;

		size_training = _size_training;

		for (int i = 0; i < imagenes.size(); i++)
			lista_indices.push_back(i);

		random_shuffle(lista_indices.begin(), lista_indices.end());		

		for (int i = 0; i < lista_indices.size(); i++)
			if (i < ceil(lista_indices.size()*size_training))
				muestra_training.at(lista_indices.at(i)) = 1;
			else
				muestra_training.at(lista_indices.at(i)) = 0;

		if (salida){
			cout << "Training: " << size_training * 100 << "% Test: " << 100 - (size_training * 100) <<"%:"<<endl;
			cout << "Training: ";
			for (int i = 0; i < muestra_training.size(); i++)
				cout << muestra_training.at(i) << ", ";
			cout << endl;
		}

	}

	return true;
}

// http://docs.opencv.org/master/d7/d8b/tutorial_py_face_detection.html#gsc.tab=0
void expresion::optimizar_region_cara(String xml_classifier){
	CascadeClassifier face_cascade;
	vector<Mat>::const_iterator it;
	vector<Rect> regiones;
	Rect region_provisional = region_cara_defecto;
	int contador;
	Mat aux;

	if (face_cascade.load(ruta_clasificador_xml + xml_classifier)){
		for (contador = 0, it = imagenes.begin(); it != imagenes.end(); ++it, contador++){
			aux = (*it).clone();

			if (aux.type() != CV_8U){
				cout << "CV_8U" << endl;
				aux.convertTo(aux, CV_8U);
			}
			if (aux.channels() == 3){
				cout << "Gray" << endl;
				cvtColor(aux, aux, COLOR_BGR2GRAY);
			}

			face_cascade.detectMultiScale(aux, regiones);

			if (!regiones.empty()){
				region_provisional.x = regiones.at(0).x;
				region_provisional.width = regiones.at(0).width;
				region_cara.push_back(region_provisional);
			}
			else{
				region_cara.push_back(region_cara_defecto);
			}

			regiones.clear();
		}
	}
	else if (salida){
		cerr << "ERROR: No se pudo cargar el clasificador '" << xml_classifier << "'";
	}
}

void expresion::generar_fichero_background_samples(){
	vector<int>::iterator it;
	ofstream fichero_casos_positivos;
	ofstream fichero_casos_negativos;
	String nombre_fichero_casos_positivos;
	String nombre_fichero_casos_negativos;

	String linea;

	nombre_fichero_casos_positivos = "samples/positive_samples/" + tipo_expresion2String(tipo) + ".info";
	nombre_fichero_casos_negativos = "samples/background_samples/bg_" + tipo_expresion2String(tipo) + ".txt";

	fichero_casos_positivos.open(nombre_fichero_casos_positivos, ios::out | ios::trunc);
	fichero_casos_negativos.open(nombre_fichero_casos_negativos, ios::out | ios::trunc);

	for (int indice_tipo = 0; indice_tipo < NUM_EXPRESIONES; indice_tipo++){
		for (int i = 1; i < NUM_SUJETOS; i++){
			// Si el sujeto pertenece a la muestra de entrenamiento.
			if (muestra_training.at(i-1) == 1){
				linea = "..\\..\\yalefaces\\subject";
				if (i < 10)
					linea = linea + "0";
				linea = linea + to_string(i) + "." + tipo_expresion2String(static_cast<tipo_expresion>(indice_tipo)) + formato;
				// Si se trata de la expresión para la que se va a entrenar el clasificador:
				if (indice_tipo == static_cast<int>(tipo)){
					// Si la región de la cara no está optimizada se usa la región por defecto.
					if (region_cara.empty()){
						linea = linea + " 1 " +
							to_string(region_cara_defecto.x) + " " +
							to_string(region_cara_defecto.y) + " " +
							to_string(region_cara_defecto.width) + " " +
							to_string(region_cara_defecto.height);
					}
					else{
						linea = linea + " 1 " +
							to_string(region_cara.at(i - 1).x) + " " +
							to_string(region_cara.at(i - 1).y) + " " +
							to_string(region_cara.at(i - 1).width) + " " +
							to_string(region_cara.at(i - 1).height);
					}

					fichero_casos_positivos << linea << endl;
				}
				else{
					fichero_casos_negativos << linea << endl;
				}
			}
		}
	}

	fichero_casos_positivos.close();
	fichero_casos_negativos.close();
}