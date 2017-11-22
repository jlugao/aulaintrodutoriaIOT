from flask import Flask, request
app = Flask(__name__)

@app.route("/home", methods=["GET","POST"])
def hello():
    if request.method == 'POST':
        print(request.get_json())
    return "Hello World!"

app.run(host="0.0.0.0")
