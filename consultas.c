#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consultas.h"

// Función para establecer la conexión a la base de datos
ConexionDB* conexion_bd() {
    ConexionDB *conexion = (ConexionDB *) malloc(sizeof(ConexionDB));
    if (conexion == NULL) {
        fprintf(stderr, "Error al asignar memoria para la conexión.\n");
        return NULL;
    }

    conexion->conn = mysql_init(NULL);
    if (conexion->conn == NULL) {
        fprintf(stderr, "Error al inicializar MYSQL: %s\n", mysql_error(conexion->conn));
        free(conexion);
        return NULL;
    }

    if (mysql_real_connect(conexion->conn, "localhost", "celiydann", "123", "mosquito_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error al conectar a la base de datos: %s\n", mysql_error(conexion->conn));
        mysql_close(conexion->conn);
        free(conexion);
        return NULL;
    }

    printf("Conexión exitosa a la base de datos.\n");
    return conexion;
}

// Función para cerrar la conexión a la base de datos
void cerrar_conexion(ConexionDB *conexion) {
    if (conexion != NULL) {
        mysql_close(conexion->conn);
        free(conexion);
        printf("Conexión cerrada.\n");
    }
}

// Función para insertar datos en la tabla
int insertar_datos(ConexionDB *conexion, const char *nombre, int edad, int matricula, int grado, const char *materia) {
    if (conexion == NULL || conexion->conn == NULL) {
        fprintf(stderr, "Conexión no válida.\n");
        return -1;
    }

    char query[512];
    snprintf(query, sizeof(query),
             "INSERT INTO estudiantes (nombre, edad, matricula, grado, materia) VALUES ('%s', %d, %d, %d, '%s')",
             nombre, edad, matricula, grado, materia);

    if (mysql_query(conexion->conn, query)) {
        fprintf(stderr, "Error al insertar datos: %s\n", mysql_error(conexion->conn));
        return -1;
    }

    printf("Datos insertados correctamente.\n");
    return 0;
}
