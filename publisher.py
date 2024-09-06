#install required libraries
#sudo apt-get install python3-pip
#pip3 install paho-mqtt

import time
import random  # To simulate temperature data
import paho.mqtt.client as mqtt

MQTT_BROKER = "e5f352a0.ala.eu-central-1.emqxsl.com"
MQTT_PORT = 8883
MQTT_TOPIC = "hotel/room/temp_data"

# we are generating random temperature sensor values as we dont have physical sensor right now
def read_temperature():
    return round(random.uniform(20.0, 30.0), 2)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print(f"Failed to connect, return code {rc}\n")

def publish_temperature():
    client = mqtt.Client()
    client.on_connect = on_connect

    client.tls_set()  
    client.tls_insecure_set(True)

    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    client.loop_start()

    while True:
        temperature = read_temperature()
        result = client.publish(MQTT_TOPIC, f"Temperature: {temperature}")
        status = result[0]
        if status == 0:
            print(f"Sent `{temperature}` to topic `{MQTT_TOPIC}`")
        else:
            print(f"Failed to send message to topic {MQTT_TOPIC}")
        time.sleep(60)

if __name__ == "__main__":
    publish_temperature()
