## JavaScript Engine environment setup (Linux)

Install google-chrome-stable for the WebGL context:
```shell
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt install ./google-chrome-stable_current_amd64.deb
```

Change the instalation path in **server.py** file if different from "/usr/bin/google-chrome-stable"
```
ChromePath = "/path/to/your/google-chrome-stable"
```

Test the setup with following:
```
python3 server.py
```
To confirm correct setup programm must: 
1. Launch an html page in a new google chrome window
2. ~30-60 seconds later close the google chrome window
3. Exit the terminal thread