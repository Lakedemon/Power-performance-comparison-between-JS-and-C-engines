from http.server import HTTPServer, SimpleHTTPRequestHandler
import webbrowser
import threading
import os.path

PORT = 8000
RequestScene = "Scenario1"

ChromePath = "/usr/bin/google-chrome-stable"
ChromeFlags = "--disable-gpu-vsync --disable-frame-rate-limit"

class CORSRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
    	#Allow CORS(cross-origin)
        self.send_header('Set-Cookie', 'pathToDemo=' + RequestScene)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        
        #Disable caching
        #self.send_header("Cache-Control", "no-cache, no-store, must-revalidate")
        #self.send_header("Pragma", "no-cache")
        #self.send_header("Expires", 0)
        SimpleHTTPRequestHandler.end_headers(self)

    def do_GET(self):
        if self.path == '/shutdown':
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            # this is not the way to do it, but it works...
            print("-------------------------------- CLOSING SERVER --------------------------------")
            self.server.shutdown()
        else:
            SimpleHTTPRequestHandler.do_GET(self)

server = HTTPServer(('localhost', PORT), CORSRequestHandler)
def run():
    server.serve_forever()

thr = threading.Thread(target=run, daemon=True)
thr.start()

webbrowser.get(ChromePath + " %s " + ChromeFlags).open('http://localhost:{PORT}/src/a_demo/Stranichka.html'.format(PORT=PORT))
