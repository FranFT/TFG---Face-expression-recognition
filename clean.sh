#! /bin/bash

source data/info.sh

####################################################
# Descripción: Limpia todos los ficheros generados.#
####################################################

# Directorios de Build
for i in ${BUILD_DIR[@]}
do
	if [ -d $i ];
	then
		echo "Borrando el directorio '$i'..."
		rm -r $i
	fi
done

# Archivos log: Si hay ficheros en el directorio 'log' correspondiente, se borran.
for i in ${LOG_DIR[@]}
do
	if [ `ls $i | wc -l` -gt "0" ];
	then
		echo "Borrando archivos 'log' en '$i'..."
		rm $i*
	fi
done
