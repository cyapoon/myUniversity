<?php
$method = $_SERVER["REQUEST_METHOD"];
$path = $_SERVER["PATH_INFO"];
$path_parts = explode("/", $path);

switch ($_SERVER["REQUEST_METHOD"]) {
case "GET":
    if ($path == "/books") {
        // Read the books database 
        $books = json_decode(file_get_contents("books.json"), true); 
        
        // Return all books
        header("Content-Type: application/json");
        echo json_encode($books);
        exit();
    }

    if (count($path_parts) == 3 &&
        $path_parts[0] == "" && $path_parts[1] == "books") {
        // Get the book id
        $book_id = intval($path_parts[2]);

        // Read the books database 
        $books = json_decode(file_get_contents("books.json"), true); 

        // Find and return the book
        foreach ($books as $book) {
            if ($book["id"] == $book_id) {
                // Return the book
                header("Content-Type: application/json");
                echo json_encode($book);
                exit();
            }
        }

        // Book not found
        http_response_code(404);
        exit();
    }
    break;

case "POST":
    if ($path == "/books") {
        // Get the new book
        $new_book = json_decode(file_get_contents("php://input"), true);

        // Read the books database 
        $books = json_decode(file_get_contents("books.json"), true); 

        // Find the maximum id
        $id = 0;
        foreach ($books as $book) {
            if ($id < $book["id"]) $id = $book["id"];
        }
        $id = $id + 1;

        // Save the new book
        $new_book["id"] = $id;
        array_push($books, $new_book);
        file_put_contents("books.json", json_encode($books, JSON_PRETTY_PRINT));
        
        // Return success
        http_response_code(201);
        header("Content-Type: application/json");
        echo json_encode($new_book);
        exit();
    }
    break;

case "PUT":
    if (count($path_parts) == 3 &&
        $path_parts[0] == "" && $path_parts[1] == "books") {
        // Get the book id
        $book_id = intval($path_parts[2]);

        // Get the book
        $updated_book = json_decode(file_get_contents("php://input"), true);

        // Read the books database 
        $books = json_decode(file_get_contents("books.json"), true); 

        // Find and update the book
        for ($i = 0; $i < count($books); $i++) {
            if ($books[$i]["id"] == $book_id) {
                // Update the book
                $updated_book["id"] = $book_id;
                $books[$i] = $updated_book;
                file_put_contents("books.json", json_encode($books, JSON_PRETTY_PRINT));

                // Return success
                header("Content-Type: application/json");
                echo json_encode($updated_book);
                exit();
            }
        }
        
        // Book not found
        http_response_code(404);
        exit();
    }
    break;

case "DELETE":
    if (count($path_parts) == 3 &&
        $path_parts[0] == "" && $path_parts[1] == "books") {
        // Get the book id
        $book_id = intval($path_parts[2]);

        // Read the books database 
        $books = json_decode(file_get_contents("books.json"), true); 

        // Find and delete the book
        for ($i = 0; $i < count($books); $i++) {
            if ($books[$i]["id"] == $book_id) {
                // Delete the book
                array_splice($books, $i, 1);
                file_put_contents("books.json", json_encode($books, JSON_PRETTY_PRINT));

                // Return success
                exit();
            }
        }

        // Book not found
        http_response_code(404);
        exit();
    }
    break;
}

http_response_code(404);
?>
