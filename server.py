from flask import Flask, jsonify
import os

app = Flask(__name__)

# Load the latest temperature from a file where the subscriber saves it
def get_last_temperature():
    if os.path.exists("sensor_data.txt"):
        with open("sensor_data.txt", "r") as file:
            return file.read().strip()
    else:
        return "No data available"

@app.route('/temperature', methods=['GET'])
def temperature():
    temperature = get_last_temperature()
    return jsonify({"temperature": temperature})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
