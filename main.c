#include <stdio.h> // Entrada y salida y colores
#include <sys/stat.h>
#include <dirent.h>

#define ANSI_COLOR_BLUE    "\x1b[34m" // Definir el color azul
#define ANSI_COLOR_RESET   "\x1b[0m" // Hacer que el texto ya no se imprima en azul


// Leer directorios
void showdir(char *path) {

	DIR *dir = opendir(path); // opendir(path) devuelve la direccion de memoria de un objeto DIR
	struct dirent *entry; // Almacena los metadatos de dirent


	while ((entry = readdir(dir)) != NULL) {
	
		printf("%s\n", entry->d_name); // d_name es un campo de entry

	}


	closedir(dir);
	printf("\n"); // Deja un espacio en blanco al final

}







// Leer archivos
void showfile(char *path) {

	FILE *file = fopen(path, "r"); // opendir(path) devuelve la direccion de memoria de un objeto FILE

	char buffer[1024]; // Almacenas 1024 bytes del archivo sin procesar
	size_t n; // size_t es un entero sin signo que dice el numero de bytes leidos en cada bloque
		  // Se lee al final de cada iteracion del bucle y si no da 1024 es que el archivo se ha acabado


    	while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        	fwrite(buffer, 1, n, stdout); // imprimir en pantalla
    	}


	// fread() lee datos del archivo y los almacena temporalmente en el buffer.
		// - buffer: dirección de memoria donde se guardarán los datos leídos.
		// - 1: tamaño de cada elemento a leer (1 byte).
		// - sizeof(buffer): cantidad máxima de bytes que se intentarán leer (1024 bytes en este caso).
		// - file: puntero al archivo desde donde se van a leer los datos.
		// fread() devuelve la cantidad real de bytes leídos, que se almacena en 'n'.
		// Si fread() devuelve 0, significa que ya no hay más datos (EOF) o que ocurrió un error.
		// El operador '> 0' mantiene el bucle activo mientras se sigan leyendo datos del archivo
	
		
	// fwrite() escribe en la salida estándar (stdout) los 'n' bytes que acabamos de leer en el buffer.
    		// - buffer: dirección del bloque de datos a escribir
    		// - 1: tamaño de cada elemento (1 byte)
    		// - n: cantidad de elementos a escribir
    		// - stdout: destino de la escritura (la terminal)
	


	fclose(file);


}







// Flujo principal del programa
int main(int argc, char *argv[]) { // Necesario para pasar argumentos


	char *path = argv[1]; // Tomamos el parametro como path
	struct stat PathStat; // Almacenara metadatos del path luego de hacer el stat
	


	if (stat(path, &PathStat) != 0) { // stat: descubrir informacion sobre rutas y guardar metadatos en la direccion de PathStat

		return 1;
	
	}


	// st_mode: Metadato con el tipo de archivo


	if (S_ISDIR(PathStat.st_mode)) { // Lee el metadato y determina si es un directorio
	
		printf(ANSI_COLOR_BLUE"\n [+] Directorio \n\n"ANSI_COLOR_RESET);
		showdir(path);

	} else if (S_ISREG(PathStat.st_mode)) {
	
		printf(ANSI_COLOR_BLUE"\n [+] Archivo \n\n"ANSI_COLOR_RESET);
		showfile(path);
	
	} else {
	
		return 1;
	
	}
		

	return 0; // Si llega al final todo bien :)		
	

}
