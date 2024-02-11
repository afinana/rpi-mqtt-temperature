#ifndef CONNECT_H
#define CONNECT_H

#include <mosquitto.h>

void on_connect(struct mosquitto* mosq, void* userdata, int rc);
void connect_to_mqtt(struct mosquitto* mosq);

#endif  // CONNECT_H
