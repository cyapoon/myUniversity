const express = require("express");
const app = express();

// Handle any GET requests for the path '/welcomemessage'
app.get("/welcomemessage", (req, res) => {
    const welcomeMessage = "Hi!";

    res.send(`<html><body>${welcomeMessage}</body></html>`);
});

// Use a web server to listen at port 8000
app.listen(8000);
