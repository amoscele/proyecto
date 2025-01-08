#ifndef CONSULTAS_H
#define CONSULTAS_H

#include <mariadb/mysql.h>

// Estructura que representa una conexión a la base de datos
typedef struct {
    MYSQL *conn;  // Puntero a la conexión de MySQL
} ConexionDB;

// Prototipos de funciones

/**
 * @brief Establece una conexión con la base de datos.
 * @return Un puntero a la estructura ConexionDB si la conexión es exitosa, NULL en caso contrario.
 */
ConexionDB* conexion_bd();

/**
 * @brief Cierra la conexión a la base de datos y libera la memoria asociada.
 * @param conexion Puntero a la estructura ConexionDB a cerrar.
 */
void cerrar_conexion(ConexionDB *conexion);

/**
 * @brief Inserta datos en la tabla "estudiantes".
 * @param conexion Puntero a la estructura ConexionDB con la conexión activa.
 * @param nombre Nombre del estudiante.
 * @param edad Edad del estudiante.
 * @param matricula Matrícula del estudiante.
 * @param grado Grado del estudiante.
 * @param materia Materia del estudiante.
 * @return 0 si la operación fue exitosa, -1 en caso de error.
 */
int insertar_datos(ConexionDB *conexion, const char *nombre, int edad, int matricula, int grado, const char *materia);

#endif
