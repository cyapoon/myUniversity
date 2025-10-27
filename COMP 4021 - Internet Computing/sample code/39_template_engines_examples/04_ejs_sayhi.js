const express = require("express");
const app = express();

// Use the EJS template engine
app.set("view engine", "ejs")

// Handle any GET requests for the path '/sayhi'
app.get("/sayhi", (req, res) => {
    res.render("sayhi", { name: "Paul" });
});

// Use a web server to listen at port 8000
app.listen(8000);
