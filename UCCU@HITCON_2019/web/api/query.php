<?php
/* Congratulation! */
/* SSID & PASSWORD in /uccu_hacker/secret_AP/list.txt */

$input = file_get_contents('php://input');
$sxe = new SimpleXMLElement($input, 2);
$result["queryResult"] = array();

foreach ($sxe->query as $str) {
    array_push($result["queryResult"], array(
        "query" => "$str",
        "value" => "Not Found", // There's nothing in the UCCU database :D
    ));
}

echo json_encode($result);
