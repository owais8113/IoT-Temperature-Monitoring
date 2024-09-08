This project simulates an IoT system that monitors hotel room temperature and sends data to a cloud EMQX MQTT broker. The system is divided into three main components:

Publisher (Raspberry Pi): Reads temperature data from a sensor and publishes it to an MQTT broker every 60 seconds
Subscriber (ESP32): Subscribes to the MQTT topic, monitors the temperature, raises an alarm if the temperature exceeds a certain threshold continuously for 5 minutes, and stores the data
Server (Laptop): A Flask-based HTTP server that exposes an API endpoint to retrieve the latest temperature reading.

publisher.py file is to be uploaded on Raspberry Pi so that it could read the temperature sensor data. In this project we dont have physical sensor that's why we are generating some random values to simulate that.

subsciber.ino file is to uploaded on ESP32 which is being used to monitor the temperature and raise alams whenever required, buzzer is working as alarm.

server.py is flask based API endpoint used to retrieve data
