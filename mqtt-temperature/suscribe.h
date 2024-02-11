#ifndef SUSCRIBE_H
#define SUSCRIBE_H

#include <mosquitto.h>

void subscribe_to_topic(struct mosquitto* mosq);
void on_message(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message);

#endif  // SUSCRIBE_H
