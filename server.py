import requests
import os
import subprocess
import time

API = 'http://localhost:9000/task'

while True:
    r = requests.get(API + '/assign')
    
    if (r.json() == {}):
        print('Empty')
    else:
        data = r.json()
        file_path = './code/' + data['_id'] + '.cpp'
        f = open(file_path, 'w')
        f.write(data['code'])
        f.close()
        print("received: " + data['_id'] + '\n') 

        reply = subprocess.run(['g++', file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        if len(reply.stderr) != 0:
            data['err'] = reply.stderr.decode('utf-8')
        else:
            inp = bytes(data['input'], 'ascii')
            try:
                reply = subprocess.run(['./a.out'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, input=inp, timeout=2)
                data['stdout'] = reply.stdout.decode('utf-8')
                data['stderr'] = reply.stderr.decode('utf-8')
            except subprocess.TimeoutExpired:
                data['stdout'] = 'timeout'
        data['id'] = str(data['_id'])
        r = requests.post(API + '/submit', json=data)
        print(r.json())
    time.sleep(1)

