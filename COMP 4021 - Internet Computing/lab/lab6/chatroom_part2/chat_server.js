const express = require("express");

const bcrypt = require("bcrypt");
const fs = require("fs");
const session = require("express-session");

// Create the Express app
const app = express();

// Use the 'public' folder to serve static files
app.use(express.static("public"));

// Use the json middleware to parse JSON data
app.use(express.json());

// Use the session middleware to maintain sessions
const chatSession = session({
    secret: "game",
    resave: false,
    saveUninitialized: false,
    rolling: true,
    cookie: { maxAge: 300000 }
});
app.use(chatSession);

// This helper function checks whether the text only contains word characters
function containWordCharsOnly(text) {
    return /^\w+$/.test(text);
}

// Handle the /register endpoint
app.post("/register", (req, res) => {
    // Get the JSON data from the body
    const { username, avatar, name, password } = req.body;
    // console.log(req.body);

    //
    // D. Reading the users.json file
    const users = JSON.parse(fs.readFileSync("./data/users.json"));
    // console.log(users);
    //

    //
    // E. Checking for the user data correctness
    if(!username || !avatar || !name || !password) {
        res.json({
            status: "error",
            error: "Please fill in all fields."
        });
        return;
    }

    if(!containWordCharsOnly(username)) {
        res.json({
            status: "error", 
            error: "Username can only contain word characters."});
        return;
    }

    if(username in users){
        res.json({
            status: "error", 
            error: "Username has already existed."});
        return;
    }

    //

    //
    // G. Adding the new user account
    const hash = bcrypt.hashSync(password,10);
    users[username] = {avatar,name,"password":hash};
    //

    //
    // H. Saving the users.json file
    fs.writeFileSync("./data/users.json",JSON.stringify(users, null, "  "));
    //

    //
    // I. Sending a success response to the browser
    res.json({status:"success"});
    //

    // Delete when appropriate
    // res.json({ status: "error", error: "This endpoint is not yet implemented." });
});

// Handle the /signin endpoint
app.post("/signin", (req, res) => {
    // Get the JSON data from the body
    const { username, password } = req.body;

    //
    // D. Reading the users.json file
    const users = JSON.parse(fs.readFileSync("./data/users.json"));
    // console.log(users);
    //

    //
    // E. Checking for username/password
    if(!(username in users)) {
        // console.log(username);
        res.json({
            status: "error",
            error: "Incorrect username or password."
        });
        return;
    }

    if(!bcrypt.compareSync(password,users[username]["password"])) {
        res.json({
            status: "error",
            error: "Incorrect username or password."
        });
        return;
    }
    //

    //
    // G. Sending a success response with the user account
    req.session.user = {
        "username": username,
        "avatar": users[username]["avatar"],
        "name": users[username]["name"]
    };

    res.json({status: "success",
        user:{
            "username": username,
            "avatar": users[username]["avatar"],
            "name": users[username]["name"]
        }});
    //

    // Delete when appropriate
    // res.json({ status: "error", error: "This endpoint is not yet implemented." });
});

// Handle the /validate endpoint
app.get("/validate", (req, res) => {

    //
    // B. Getting req.session.user
    const user = req.session.user;
    // console.log(user);
    //

    //
    // D. Sending a success response with the user account
    if(user) {
        res.json({
            status: "success",
            user: user
        })
    }
    else {
        res.json({
            status: "error",
            error: "Session not exists."});
    }
    //
 
    // Delete when appropriate
    // res.json({ status: "error", error: "This endpoint is not yet implemented." });
});

// Handle the /signout endpoint
app.get("/signout", (req, res) => {

    //
    // Deleting req.session.user
    delete req.session.user;
    //

    //
    // Sending a success response
    res.json({status: "success"});
    //
 
    // Delete when appropriate
    // res.json({ status: "error", error: "This endpoint is not yet implemented." });
});


//
// ***** Please insert your Lab 6 code here *****
const {createServer} = require("http");
const {Server} = require("socket.io");
const httpServer = createServer(app);
const io = new Server(httpServer);

io.use((socket,next)=>{
    chatSession(socket.request,{},next);
});

const onlineUsers = {};

io.on("connect",(socket)=>{
    if(socket.request.session.user){
        const user = socket.request.session.user;
        const {username, avatar, name} = user;
        onlineUsers[username] = user;
        io.emit("add user",JSON.stringify(user));
        // console.log(onlineUsers);
    }
    // disconnect
    socket.on("disconnect",()=>{
        if(socket.request.session.user){
            const user = socket.request.session.user;
            const {username, avatar, name} = user;
            if(onlineUsers[username]){
                delete onlineUsers[username];
            }
            io.emit("remove user", JSON.stringify(user));
            // console.log(onlineUsers);
        }

    });

    // showing the online user list
    socket.on("get users",()=>{
        socket.emit("users",JSON.stringify(onlineUsers));
    });

    // getting the chatroom messages
    socket.on("get messages", ()=>{
        const chatroom = JSON.parse(fs.readFileSync("./data/chatroom.json","utf-8"));
        socket.emit("messages",JSON.stringify(chatroom));
    });

    //post message
    socket.on("post message", (content)=>{
        const user = socket.request.session.user;
        const datetime = new Date();
        const {username, avatar, name} = user;
        const message = {user,datetime,content};
        // message["user"] = user;
        // message["datetime"] = datetime;
        // message["content"] = content;

        // console.log(message)

        const chatroom = JSON.parse(fs.readFileSync("./data/chatroom.json","utf-8"));
        chatroom.push(message);
        fs.writeFileSync("./data/chatroom.json",JSON.stringify(chatroom,null,"  "));

        io.emit("add message", JSON.stringify(message));
    })

    socket.on("typing", (user)=>{
        const remote_user = socket.request.session.user;
        const {username, avatar, name} = remote_user;
        io.emit("typing name", JSON.stringify({"name": name}));
    })
    
});

//


// Use a web server to listen at port 8000
httpServer.listen(8000, () => {
    console.log("The chat server has started...");
});
