const express = require("express");
const app = express();

// Use the data model
const stocks = require("./stocks");

// Use the EJS template engine
app.set("view engine", "ejs")

// Handle the get request
app.get("/", async (req, res) => {
    const stock = await stocks.getStock("AAPL");
    res.render("view", { stock });
});

// Use a web server to listen at port 8000
app.listen(8000);
