#include "client.h"

int main(void){
    /*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

    int conexion;
    char* ip;
    char* puerto;
    char* valor;

    t_log* logger;
    t_config* config;

    /* ---------------- LOGGING ---------------- */

    logger = iniciar_logger();

    log_info(logger, "Hola! Soy un log");

    /* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

    config = iniciar_config();

    ip = config_get_string_value(config, "IP");
    puerto = config_get_string_value(config, "PUERTO");
    valor = config_get_string_value(config, "CLAVE");

    log_info(logger, "CLAVE: %s", valor);

    /*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

    // ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

    // Creamos una conexión hacia el servidor
    conexion = crear_conexion(ip, puerto);

    // Enviamos al servidor el valor de CLAVE como mensaje
    enviar_mensaje(valor, conexion);

    // Armamos y enviamos el paquete
    t_paquete* paquete_a_enviar = crear_paquete();

    /* ---------------- LEER DE CONSOLA ---------------- */

    leer_consola(logger, paquete_a_enviar);

    enviar_paquete(paquete_a_enviar, conexion);
    eliminar_paquete(paquete_a_enviar);

    terminar_programa(conexion, logger, config);

    /*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
    // Proximamente

    return 0;
}

t_log* iniciar_logger(void){
    t_log* nuevo_logger;

    nuevo_logger = log_create("tp0.log", "cliente", true, LOG_LEVEL_INFO);

    return nuevo_logger;
}

t_config* iniciar_config(void){
    t_config* nuevo_config;

    nuevo_config = config_create("cliente.config");

    return nuevo_config;
}

void leer_consola(t_log* logger, t_paquete* paquete)
{
    char* leido;

    leido = readline("> ");

    while (strcmp(leido, "") != 0)
    {
        log_info(logger, "%s", leido);
        agregar_a_paquete(paquete, leido, strlen(leido) + 1);
        free(leido);
        leido = readline("> ");
    }

    free(leido);
}

void terminar_programa(int conexion, t_log* logger, t_config* config){
    liberar_conexion(conexion);
    log_destroy(logger);
    config_destroy(config);
}
