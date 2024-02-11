#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "example/topic"

void on_connect(struct mosquitto* mosq, void* userdata, int rc) {
    if (rc == 0) {
        printf("Connected to MQTT broker\n");
    }
    else {
        fprintf(stderr, "Failed to connect to MQTT broker: %s\n", mosquitto_connack_string(rc));
        exit(EXIT_FAILURE);
    }
}

int main() {
    struct mosquitto* mosq = NULL;

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
        return EXIT_FAILURE;
    }

    mosquitto_connect_callback_set(mosq, on_connect);

    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to connect to MQTT broker.\n");
        return EXIT_FAILURE;
    }

    const char* message = "Hello, MQTT!";
    if (mosquitto_publish(mosq, NULL, MQTT_TOPIC, (int) strlen(message), message, 0, false) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to publish message.\n");
        return EXIT_FAILURE;
    }

    mosquitto_loop_start(mosq);

    while (1) {
        // Keep the program running
    }

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return EXIT_SUCCESS;
}
