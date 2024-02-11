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

void connect_to_mqtt(struct mosquitto* mosq) {
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }

    mosquitto_connect_callback_set(mosq, on_connect);

    if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to connect to MQTT broker.\n");
        exit(EXIT_FAILURE);
    }

    mosquitto_loop_start(mosq);
}

void on_message(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message) {
    if (message->payloadlen) {
        printf("Received message on topic %s: %s\n", message->topic, (char*)message->payload);
    }
    else {
        printf("Received empty message on topic %s\n", message->topic);
    }
}

void subscribe_to_topic(struct mosquitto* mosq) {
    if (mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to subscribe to topic.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    struct mosquitto* mosq = NULL;

    connect_to_mqtt(mosq);
    subscribe_to_topic(mosq);

    mosquitto_message_callback_set(mosq, on_message);

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return EXIT_SUCCESS;
}