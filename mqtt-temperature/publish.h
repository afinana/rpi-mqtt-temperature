#ifndef PUBLISH_H
#define PUBLISH_H

#include <mosquitto.h>


void publish_message(struct mosquitto* mosq, const char* topic, const char* message);

#endif  // PUBLISH_H
