#! /bin/bash

source ../data/info.sh

# Comprobación de parámetros de entrada.
if [ $# -ne 2 ]
then
	echo "El número de parámetros es incorrecto."
	echo "Sintaxis: ./build.sh <nombre_app> <STASM | TEST>"
	exit 1
fi

# Creo el directorio de salida y me sitúo en él.
mkdir -p ../${BUILD_DIR[$1]}
cd ../${BUILD_DIR[$1]}


# Se actua en función del segundo parámetro.
case $2 in

	STASM)
		# Compilo la build de la librería necesaria.
		cmake ${LIB_DIR[$1]} && make
		;;
	TEST)
		# Compilo la aplicación.
		cmake ${SOURCE_DIR[$1]} && make
		;;
	*) echo "Error en el segundo parámetro '$2' != [ STASM | TEST ]"
		exit 1
		;;
esac

# Acciones especiales a aplicar para algunas aplicaciones.
case $1 in

	STASM_hands|STASM_cars)
		# Entreno el modelo de puntos de los vehículos.
		./tasm -d ${LIB_DIR[$1]}/stasm/MOD_1 ${LIB_DIR[$1]}/tasm/shapes/${SHAPEFILE[$1]}
		# Vuelvo a compilar los ejecutables con el nuevo modelo.
		make
		;;

	asmlib-opencv)
		# Creo el scrip para ejecutar la demo.
		echo "./demo/demo -pc -m ../lib/asmlib-opencv-master/data/muct76.model -f -C ../data/haarcascade_frontalface_alt2.xml" > ejecutarDemo.sh
		chmod +x ejecutarDemo.sh
		;;

	*) echo ""
		;;
esac


#Ejemplo switch-case
#case $1 in

#	STASM) echo "$1"
#		;;
#	*) echo "Caso por defecto"
#		;;
#esac
