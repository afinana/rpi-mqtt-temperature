

# MQTT C Example

This example demonstrates a simple MQTT program in C using the Mosquitto library. The functionality is divided into three files: `main.c`, `connect.c`, and `publish.c`. Header files (`connect.h` and `publish.h`) are used to declare function prototypes.

## Files

- **main.c**: Contains the main program logic. It initializes the MQTT connection and publishes a message to the specified topic.

- **connect.c**: Manages the MQTT connection, including initialization and handling connection callbacks.

- **publish.c**: Handles message publishing to the MQTT broker on a specified topic.

- **suscribe.c**: Handles message consuming to the MQTT broker on a specified topic.

- **connect.h** and **publish.h**: Header files containing function declarations.

- **Makefile**: Makefile for compilation.

## Compilation

To compile the program, use the provided Makefile. Run the following commands in the terminal:

```bash
make main
```

## Dependencies
This example relies on the Mosquitto library, which can be installed on Ubuntu using:

```bash

sudo apt-get update
sudo apt-get install mosquitto
sudo apt-get install libmosquitto-dev

```

## Test application

Send data to temperature/celsius topic

```bash
 mosquitto_pub -h localhost -t "temperature/celsius" -m "100"
 ```

Receive farenheith temperature conversion


```bash
 mosquitto_sub -h localhost -t "temperature/fahrenheit"
 ```