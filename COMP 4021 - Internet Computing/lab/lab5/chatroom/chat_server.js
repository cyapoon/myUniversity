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
    users[username] = {avatar,name,hash};
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

    if(!bcrypt.compareSync(password,users[username]["hash"])) {
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
//


// Use a web server to listen at port 8000
app.listen(8000, () => {
    console.log("The chat server has started...");
});
