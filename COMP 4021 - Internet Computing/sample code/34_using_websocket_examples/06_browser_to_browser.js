const express = require("express");
const app = express();
const { createServer } = require("http");
const { Server } = require("socket.io");
const httpServer = createServer(app);
const io = new Server(httpServer);

// Use the 'public' folder to serve static files
app.use(express.static("public"));

// Storage for the ids and sockets
const sockets = {};

// Prepare the WebSocket
io.on("connection", (socket) => {
    // Save the socket information
    sockets[socket.id] = socket;

    // Send the socket id to the browser
    socket.emit("id", socket.id);
    
    // Send the connected socket ids
    io.emit("sockets", JSON.stringify(Object.keys(sockets)));

    // Wait for messages
    socket.on("message", (data) => {
        const { to, message } = JSON.parse(data);
        if (sockets[to]) {
            sockets[to].emit("message", JSON.stringify({
                from: socket.id, message}));
        }
    });

    // Wait for disconnect
    socket.on("disconnect", (reason) => {
        delete sockets[socket.id];

        // Send the connected socket ids
        io.emit("sockets", JSON.stringify(Object.keys(sockets)));
    });
});

// Use a web server to listen at port 8000
httpServer.listen(8000);
