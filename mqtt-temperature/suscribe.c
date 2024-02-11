#include "suscribe.h"
#include "publish.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MQTT_TOPIC_CELSIUS "temperature/celsius"
#define MQTT_TOPIC_FARENTHEIT "temperature/fahrenheit"

/* Callback called when the client knows to the best of its abilities that a
 * PUBLISH has been successfully sent. For QoS 0 this means the message has
 * been completely written to the operating system. For QoS 1 this means we
 * have received a PUBACK from the broker. For QoS 2 this means we have
 * received a PUBCOMP from the broker. */
void on_message(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message) {
    
   
    double temp_celsius, temp_fahrenheit;
    char buf[51];
    if (message->payloadlen) {
        printf("Received message on topic %s: %s\n", message->topic, (char*)message->payload);
        if (!strcmp((char*) message->topic, MQTT_TOPIC_CELSIUS)) {
            memset(buf, 0, 51 * sizeof(char));
        
            /* Copy N-1 bytes to ensure always 0 terminated. */
            memcpy(buf, message->payload, 50 * sizeof(char));
            temp_celsius = atof(buf);
            temp_fahrenheit = temp_celsius * 9.0 / 5.0 + 32.0;
            snprintf(buf, 50, "%f", temp_fahrenheit);
            publish_message(mosq, MQTT_TOPIC_FARENTHEIT, buf);

        }
    }
    else {
        printf("Received empty message on topic %s\n", message->topic);
    }
}

void subscribe_to_topic(struct mosquitto* mosq) {

    if (mosquitto_subscribe(mosq, NULL, MQTT_TOPIC_CELSIUS, 0) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to subscribe to topic.\n");
        exit(EXIT_FAILURE);
    }
}

  