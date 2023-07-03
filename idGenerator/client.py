import random
import requests
import time

ids = []

while True:
    try:
        port = random.randint(8000, 8002)
        url = "http://127.0.0.1:{}/".format(port)
        r = requests.get(url)
        newId = r.json()["id"]

        if newId in ids:
            raise Exception("Existing ID in list ERROR!")
        else:
            ids.append(newId)
        
        print("ID: {}".format(newId))

        time.sleep(0.01)

    except KeyboardInterrupt:
        break

    except Exception as e:
        print(e)