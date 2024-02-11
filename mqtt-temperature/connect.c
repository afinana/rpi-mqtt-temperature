#include "connect.h"
#include <stdio.h>
#include <stdlib.h>




/* Callback called when the client receives a CONNACK message from the broker. */
void on_connect(struct mosquitto* mosq, void* obj, int reason_code)
{
    /* Print out the connection result. mosquitto_connack_string() produces an
     * appropriate string for MQTT v3.x clients, the equivalent for MQTT v5.0
     * clients is mosquitto_reason_string().
     */
    printf("on_connect: %s\n", mosquitto_connack_string(reason_code));
    if (reason_code != 0) {
        /* If the connection fails for any reason, we don't want to keep on
         * retrying in this example, so disconnect. Without this, the client
         * will attempt to reconnect. */
        mosquitto_disconnect(mosq);
        fprintf(stderr, "Failed to connect to MQTT broker: %s\n", mosquitto_connack_string(reason_code));
        exit(EXIT_FAILURE);
    }

    /* You may wish to set a flag here to indicate to your application that the
     * client is now connected. */
    printf("Connected to MQTT broker: \n");
}

void connect_to_mqtt(struct mosquitto* mosq) {
   
    int rc;

    /* Connect to test.mosquitto.org on port 1883, with a keepalive of 60 seconds.
     * This call makes the socket connection only, it does not complete the MQTT
     * CONNECT/CONNACK flow, you should use mosquitto_loop_start() or
     * mosquitto_loop_forever() for processing net traffic. */
    rc = mosquitto_connect(mosq, "localhost", 1883, 60);
    if ( rc!= MOSQ_ERR_SUCCESS) {
        mosquitto_destroy(mosq);
        fprintf(stderr, "Unable to connect to MQTT broker.\n");
        exit(EXIT_FAILURE);
    }
    /* Run the network loop in a background thread, this call returns quickly. */
    rc = mosquitto_loop_start(mosq);
    if ( rc!= MOSQ_ERR_SUCCESS) {
        mosquitto_destroy(mosq);
        fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
        exit(EXIT_FAILURE);
    }

}
