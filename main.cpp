#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "utilidades.h"
#include "expresion.h"
//#include <opencv2\objdetect\objdetect.hpp>


#define NUM_IMAGES 165


// Fase de entrenamiento.
vector<expresion> inicializar_expresiones(const float _size_training, bool _salida=false){
	vector<expresion> expresiones;
	expresion aux;
	for (int i = 0; i < NUM_EXPRESIONES; i++){
		if (aux.cargar_expresion(static_cast<tipo_expresion>(i), true, false))
			expresiones.push_back(aux);
		else if (_salida)
			cerr << "ERROR: No se ha podido cargar la expresion facial - " << static_cast<tipo_expresion>(i) << endl;
	}

	return expresiones;
}

void create_samples(){
	PROCESS_INFORMATION informacion_proceso;
	STARTUPINFO informacion_arranque;
	LPCTSTR lpApplicationName = "C:\\Windows\\System32\\cmd.exe";
	LPTSTR lpCommandLine = "/c createsamples.bat";

	ZeroMemory(&informacion_arranque, sizeof(informacion_arranque));
	informacion_arranque.cb = sizeof(informacion_arranque);
	ZeroMemory(&informacion_proceso, sizeof(informacion_proceso));

	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms682425(v=vs.85).aspx
	//https://msdn.microsoft.com/en-us/library/ms682512(VS.85).aspx
	// Iniciamos el proceso que crea los ficheros .vec
	if (!CreateProcess(lpApplicationName, lpCommandLine, NULL, NULL, TRUE, 0, NULL, NULL, &informacion_arranque, &informacion_proceso)){
		cerr << "ERROR: No se pudo iniciar el proceso - opencv_createsamples.exe" << endl;
	}
	// Esperamos hasta que el proceso creado finalice.
	WaitForSingleObject(informacion_proceso.hProcess, INFINITE);

	// Se cierra el proceso.
	CloseHandle(informacion_proceso.hProcess);
	CloseHandle(informacion_proceso.hThread);
}

int main(){
	const float size_training = 0.8;

	inicializar_expresiones(size_training);
	create_samples();
	
	return 0;
}