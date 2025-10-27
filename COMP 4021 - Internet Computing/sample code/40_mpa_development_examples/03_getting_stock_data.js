// Use the data model
const stocks = require("./stocks");

// Get the Apple Inc. stock data
stocks.getStock("AAPL")
    .then((stock) => {
        console.log(JSON.stringify(stock, null, "  "));
    })
    .catch((error) => {
        console.log(error.message);
    });
