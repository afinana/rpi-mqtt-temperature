#include "publish.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void publish_message(struct mosquitto* mosq, const char* topic, const char* message) {

     const int qos = 0; // Quality of Service
     const bool retain = false;

    
    fprintf(stdout, "strlen of publish message: %d.\n", (int) strlen(message));
    int result = mosquitto_publish(mosq, NULL, topic, (int) strlen(message), message, qos, retain);
    if ( result!= MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to publish message. error code: %d.\n", result);
        return;
    }


}
  