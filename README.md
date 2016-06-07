# WhosIn
********************** NOTE: while it isn't strictly necessary to have a Raspberry Pi for this to work, you must have a bluetooth enabled computer that can act as a server - I just use a pi because they're easier to work with. **********************

These are the instructions to set up your raspberry pi in order to work with the Who's In? app on your iPhone. 

I HIGHLY recommend setting up port forwarding on your router and a dynamic dns and hostname for your pi in order to actually be able to use the app to its full potential (otherwise you'd only be able to use it if you're on the same network as your pi, which, let's face it, is pretty useless). To set it up just follow the instructions over at https://pimylifeup.com/raspberry-pi-port-forwarding/.

For the Pi:

1. From your pi's terminal (ssh or monitor), type git clone https://github.com/cristobalwee/WhosIn
2. Go to the WhosIn folder by typing cd WhosIn
3. If you are planning on using the app with 4 devices, skip this step. Otherwise, edit the data.txt file to have the same number of lines as you do user devices; i.e. if you want to track whether 3 user devices are in the house, delete one of the lines in data.txt to have a total of 3 lines
4. In line 24 of inoutboard.py (where it reads "users = ["user1", ...]"), change the elements of the array to include your users' names
5. If you have set up bluetooth on your pi, skip this step. Otherwise, visit https://www.raspberrypi.org/learning/robo-butler/bluetooth-setup/ for instructions
6. Once setup, type hcitool scan to scan for nearby devices (NOTE: your devices have to be in discoverable mode for them to be found by the scanner, i.e. on an iPhone, simply go to the bluetooth tab in settings and your phone will become discoverable).
7. Copy the bluetooth id's (in the form XX:XX:XX:XX:XX:XX) of all the devices you intend to use and edit line 30 of inoutboard.py (where it reads "bids = ['D4:F4:6F:32:B0:AF', ...]") to include these id's
8. At this point, in order to start the server and bluetooth board processes, I recommend having two terminals open and running the following commands from the first terminal: gcc server.c -o server -lpthread and ./server, and from the second: python inoutboard.py. I've also included short bash scripts to start and end the respective processes, but I'm quite new to scripting so I wouldn't recommend using these (but feel free to edit them). If you do, simply run bash startall.sh to start and bash endall.sh to finish; but be cautious: the first script runs the server in the background, so there's a possibility, however slight, that it won't be so easy to kill the process.
9. Now, download the app on your phone, input your pi's hostname and port, and enjoy (check out the app instructions below).

For non-Pi/non-linux computers: (replace these steps for 6-7 above)

1. Install pip from https://packaging.python.org/en/latest/installing/ and pybluez from https://github.com/karulis/pybluez
2. Run bluetoothscanner.py with 'python bluetoothscanner.py' from your computer's terminal (NOTE: your devices have to be in discoverable mode for them to be found by the scanner, i.e. on an iPhone, simply go to the bluetooth tab in settings and your phone will become discoverable).

For the app:
![Setup](https://cloud.githubusercontent.com/assets/8813763/15724280/63a46514-2814-11e6-9043-bb5709338e30.png)
![Manage](https://cloud.githubusercontent.com/assets/8813763/15724294/6b2f45b0-2814-11e6-93f8-199d4e561f5f.png)
![Home](https://cloud.githubusercontent.com/assets/8813763/15724852/fc95d440-2816-11e6-9c0a-4dd650e06cae.png)
