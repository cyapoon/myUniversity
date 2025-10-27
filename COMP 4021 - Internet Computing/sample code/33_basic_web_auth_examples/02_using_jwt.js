const express = require("express");
const jwt = require('jsonwebtoken');
const cookieParser = require("cookie-parser");
const app = express();

// Use the 'public' folder to serve static files
app.use(express.static("public"));

// Use cookie parser to enable cookies
app.use(cookieParser());

// Use the json middleware to get JSON data
app.use(express.json());

// Generate a secret key
const secretKey = require("crypto").randomBytes(48).toString("hex");

// Handle any GET requests for the path '/getname'
app.get("/getname", (req, res) => {
    if (req.cookies.token) {
        const { name } = jwt.verify(req.cookies.token, secretKey);
        res.json({ name });
    }
    else
        res.json({ });
});

// Handle any POST requests for the path '/setname'
app.post("/setname", (req, res) => {
    const { name } = req.body;
    if (name) {
        const token = jwt.sign({ name }, secretKey, { expiresIn: "5m" });
        res.cookie("token", token);
    }
    res.json({ name });
});

// Handle any GET requests for the path '/deletename'
app.get("/deletename", (req, res) => {
    if (req.cookies.token)
        res.clearCookie("token");
    res.json({ });
});

// Use a web server to listen at port 8000
app.listen(8000);
