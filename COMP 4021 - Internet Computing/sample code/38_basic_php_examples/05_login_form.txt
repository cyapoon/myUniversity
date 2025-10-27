<!DOCTYPE html>
<html>
<head>
    <title>Login Form</title>
</head>
<body>
    <?php
    if (isset($_GET["username"]) &&
        isset($_GET["password"])) {
    ?>
    You have logged in successfully!
    <?php
    }
    else {
    ?>
    <form>
        <p>Username: <input name="username"></p>
        <p>Password: <input name="password" type="password"></p>
        <button type="submit">Sign In</button>
    </form>
    <?php
    }
    ?>
</body>
</html>
