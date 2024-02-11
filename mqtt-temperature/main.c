#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include "connect.h"
#include "suscribe.h"
#include "publish.h"

#define MQTT_TOPIC "temperature/topic"

struct mosquitto *mosq = NULL;
int main() {

    /* Required before calling other mosquitto functions */
    mosquitto_lib_init();

    /* Create a new client instance.
    * id = NULL -> ask the broker to generate a client id for us
    * clean session = true -> the broker should remove old sessions when we connect
    * obj = NULL -> we aren't passing any of our private data for callbacks
    */
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Out of memory.\n");
        exit(EXIT_FAILURE);
    }

    /* Configure callbacks. This should be done before connecting ideally. */
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    connect_to_mqtt(mosq);

    // Suscribe to temperature topòc
    subscribe_to_topic(mosq);


    const char* message = "mqtt-temperature start!";
    publish_message(mosq, MQTT_TOPIC, message);

    // Send starting event
    mosquitto_loop_forever(mosq, -1, 1);
  
    mosquitto_lib_cleanup();
    return EXIT_SUCCESS;
}
