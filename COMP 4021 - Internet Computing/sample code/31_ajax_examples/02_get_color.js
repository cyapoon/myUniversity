const express = require("express");
const app = express();

// Use the 'public' folder to serve static files
app.use(express.static("public"));

// Use the json middleware to get JSON data
app.use(express.json());

// Make some data
const colors = {
    Happy: { color: "yellow" },
    Sad: { color: "blue" },
    Angry: { color: "red" },
    Fear: { color: "gray" }
};

// Handle any POST requests for the path '/getcolor'
app.post("/getcolor", (req, res) => {
    // Get the name
    const { name } = req.body;

    // Return the color if found
    if (name && colors[name])
        res.json(colors[name]);
    else
        res.json("Colour not found");
});

// Use a web server to listen at port 8000
app.listen(8000);
