Overview
This project simulates an IoT system that monitors room temperature and sends data to a cloud MQTT broker. The system is divided into three main components:

Publisher (Raspberry Pi): Simulates or reads temperature data from a sensor and publishes it to an MQTT broker every 60 seconds.
Subscriber (ESP32): Subscribes to the MQTT topic, monitors the temperature, raises an alarm if the temperature exceeds a certain threshold continuously for 5 minutes, and stores the data.
Server (Laptop): A Flask-based HTTP server that exposes an API endpoint to retrieve the latest temperature reading.
The goal is to ensure optimal room conditions by continuously monitoring the temperature and raising alarms when necessary.

Project Components
1. Publisher (Raspberry Pi)
The Raspberry Pi simulates or reads temperature data from a temperature sensor and publishes it to an MQTT broker every 60 seconds.

Steps to Set Up the Publisher:
Install the Required Libraries on Raspberry Pi:

bash
Copy code
sudo apt-get install python3-pip
pip3 install paho-mqtt
Run the Publisher Program:

Save the publisher.py file on your Raspberry Pi.
Run the program:
bash
Copy code
python3 publisher.py
The publisher will start sending temperature data to the specified MQTT topic at regular intervals.

2. Subscriber (ESP32)
The ESP32 subscribes to the MQTT topic and checks the temperature against a predefined threshold. If the temperature exceeds this threshold (28°C in this case) continuously for 5 minutes (i.e., 5 data points), the ESP32 raises an alarm.

Steps to Set Up the Subscriber:
Install the PubSubClient Library in the Arduino IDE (go to Tools > Manage Libraries and search for "PubSubClient").
Upload the Subscriber Code (subscriber.ino) to the ESP32 using the Arduino IDE.
Monitor the ESP32 Output:
The ESP32 will print the received temperature and raise an alarm if the threshold is crossed continuously.
3. Server (Laptop)
The Flask server runs on your laptop and exposes an HTTP API endpoint to access the latest temperature readings from the subscriber. The subscriber can save data either to a file (sensor_data.txt) or send it via serial communication to the server.

Steps to Set Up the Server:
Install the Required Libraries:

bash
Copy code
pip3 install Flask
Run the Flask Server:

Save the server.py file on your laptop.
Run the server:
bash
Copy code
python3 server.py
Access the API Endpoint:

Open your browser and go to the following URL to get the latest temperature reading:
arduino
Copy code
http://<your-laptop-ip>:5000/temperature
The server will return the last recorded temperature as a JSON response.

Project Structure
bash
Copy code
📂 IoT-Temperature-Monitoring-System
 ┣ 📜 publisher.py             # Publisher program for Raspberry Pi
 ┣ 📜 subscriber.ino            # Subscriber program for ESP32
 ┣ 📜 server.py                 # Flask-based server to expose temperature data via API
 ┣ 📜 requirements.txt          # Python dependencies
 ┗ 📜 README.md                 # Project documentation
Usage
Publisher: The Raspberry Pi continuously publishes temperature data to the MQTT broker every 60 seconds.
Subscriber: The ESP32 monitors the MQTT topic for temperature data, raises alarms if the threshold is exceeded, and stores the data.
Server: A Flask API running on the laptop exposes an endpoint to retrieve the latest temperature readings.
Installation and Setup
Raspberry Pi Setup (Publisher):

Ensure that Python 3 and paho-mqtt are installed on the Raspberry Pi.
Save and run publisher.py on the Raspberry Pi.
ESP32 Setup (Subscriber):

Upload subscriber.ino to the ESP32 using the Arduino IDE.
Ensure the WiFi credentials are correct in the code for network connection.
Laptop Setup (Server):

Ensure that Python 3 and Flask are installed on your laptop.
Save server.py and run it to start the API server.
Dependencies
Ensure that the following dependencies are installed on the respective devices:

Raspberry Pi (Publisher):
Python 3.x
paho-mqtt
ESP32 (Subscriber):
PubSubClient (Install via Arduino IDE)
Laptop (Server):
Python 3.x
Flask (Install via pip):
bash
Copy code
pip3 install Flask
MQTT Broker Details
Broker Address: e5f352a0.ala.eu-central-1.emqxsl.com
MQTT Port: 8883
Topic: hotel/temperature
