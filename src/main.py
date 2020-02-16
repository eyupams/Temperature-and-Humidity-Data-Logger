import urequests as requests
import dht
import machine
import time
from machine import Pin
import ujson

url = "https://restgo.herokuapp.com/api/weather/add"

headers = {'Content-Type': 'application/json'}

def run():
    try:
        while True:
            my_dht = dht.DHT22(Pin(0, Pin.IN, Pin.PULL_UP))

            # Read and show the data from DHT
            my_dht.measure()
            temp = my_dht.temperature()
            humid = my_dht.humidity()

            message = {
                'temp': temp,
                'humid':humid
            }
            data = ujson.dumps(message)
            
            r = requests.post(url, data=data, headers=headers)
            results = r.json()
            print(results)
            print(message)
            time.sleep(30)
    except(Exception) as error:
        print(error)
        
if __name__ == '__main__':
    print("Starting up main")
    run()