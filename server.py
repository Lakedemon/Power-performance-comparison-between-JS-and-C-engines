from http.server import HTTPServer, SimpleHTTPRequestHandler
import webbrowser
import threading

PORT = 8000



class CORSRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        SimpleHTTPRequestHandler.end_headers(self)

    def do_GET(self):
        if self.path == '/shutdown':
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            # this is not the way to do it, but it works...
            print("-------------------- CLOSING SERVER IGNORE FOLLOWING EXEPTION ----------------------")
            self.server.server_close()
        else:
            SimpleHTTPRequestHandler.do_GET(self)

server =HTTPServer(('localhost', PORT), CORSRequestHandler)
def run():
    server.serve_forever()

thr = threading.Thread(target=run)
thr.start()
webbrowser.open('http://localhost:{PORT}/src/a_demo/Stranichka.html'.format(PORT=PORT))