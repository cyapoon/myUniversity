const express = require("express");
const app = express();
const { createServer } = require("http");
const { Server } = require("socket.io");
const httpServer = createServer(app);
const io = new Server(httpServer);

// Use the 'public' folder to serve static files
app.use(express.static("public"));

// Set the connection event
io.on("connection", (socket) => {
    console.log("A browser has been connected: id=" + socket.id);
});

// Use a web server to listen at port 8000
httpServer.listen(8000);
