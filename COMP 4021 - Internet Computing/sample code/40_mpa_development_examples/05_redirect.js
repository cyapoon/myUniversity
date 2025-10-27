const express = require("express");
const app = express();

// Handle any GET requests for the path '/'
app.get("/", (req, res) => {
    res.redirect("http://money.com");
});

// Use a web server to listen at port 8000
app.listen(8000);
