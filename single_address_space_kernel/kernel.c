#include <stdint.h>
#include <stddef.h>

// Define a structure for system objects
typedef struct SystemObject {
    const char *name;
    void (*init)(void);
    void (*handle_message)(const char *message);
} SystemObject;

// Maximum number of system objects
#define MAX_OBJECTS 16

// Object bus to hold registered objects
static SystemObject *object_bus[MAX_OBJECTS];
static size_t object_count = 0;

// Function to register a system object
int register_object(SystemObject *obj) {
    if (object_count >= MAX_OBJECTS) {
        return -1; // Bus is full
    }
    object_bus[object_count++] = obj;
    return 0; // Success
}

// Function to deregister a system object
int deregister_object(const char *name) {
    for (size_t i = 0; i < object_count; ++i) {
        if (object_bus[i] && object_bus[i]->name && strcmp(object_bus[i]->name, name) == 0) {
            // Shift remaining objects
            for (size_t j = i; j < object_count - 1; ++j) {
                object_bus[j] = object_bus[j + 1];
            }
            object_bus[--object_count] = NULL;
            return 0; // Success
        }
    }
    return -1; // Object not found
}

// Function to send a message to a system object
int send_message(const char *name, const char *message) {
    for (size_t i = 0; i < object_count; ++i) {
        if (object_bus[i] && object_bus[i]->name && strcmp(object_bus[i]->name, name) == 0) {
            if (object_bus[i]->handle_message) {
                object_bus[i]->handle_message(message);
                return 0; // Success
            }
        }
    }
    return -1; // Object not found
}

// Example system object: Logger
void logger_init(void) {
    // Initialization code for logger
}

void logger_handle_message(const char *message) {
    // Print the message (placeholder for actual logging)
    printf("Logger: %s\n", message);
}

SystemObject logger = {
    .name = "logger",
    .init = logger_init,
    .handle_message = logger_handle_message
};

// Kernel entry point
void kernel_main(void) {
    // Initialize the logger
    register_object(&logger);
    logger.init();

    // Test sending a message to the logger
    send_message("logger", "Kernel initialized.");

    // Main loop (placeholder)
    while (1) {
        // Kernel idle
    }
}
