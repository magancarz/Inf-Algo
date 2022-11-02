from flask import Flask
from flask import render_template
import jyserver.Flask as jsf

app = Flask(__name__)

@jsf.use(app)
class App:
    def __init__(self):
        self.result = 0

    def add(self):
        self.result += 5
        self.js.document.getElementById('result').innerHTML = self.result

@app.route('/')
def index():
    return App.render(render_template('index.html'))

if __name__ == '__main__':
    app.run()