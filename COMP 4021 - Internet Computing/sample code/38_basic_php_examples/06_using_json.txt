<?php
header("Content-Type: application/json");

$user = [
    "username" => "Peter",
    "name" => "Peter Pan",
    "password" => "PeterP"
];

echo json_encode($user);
?>
