# index.html must put floder into templates
# Accessing URL is http://IP_address:8080/ 
from flask import Flask, render_template

app = Flask(__name__)

@app.route("/",methods=["GET","POST"])
def index():
	return render_template("./index.html")
	
if __name__ == "__main__":
	app.debug = True
	app.run(host="0.0.0.0",port=8080)
