<?php

$connection=mysqli_connect('localhost','root','','arduino');

    $request_method=$_SERVER["REQUEST_METHOD"];
    
	switch($request_method)
	{
		case 'GET':
			// Retrive Products
			get_data();
			break;
		case 'POST':
			// Insert Product
			insert_data();
			break;
		default:
			// Invalid Request Method
			header("HTTP/1.0 405 Method Not Allowed");
			break;
	}

    function get_data()
	{
		global $connection;
		$query="SELECT * FROM sensor_data";
		$response=array();
		$result=mysqli_query($connection, $query);
		while($row=mysqli_fetch_array($result))
		{
			$response[]=$row;
		}
		header('Content-Type: application/json');
		echo json_encode($response);
	}

    function insert_data()
	{
        global $connection;
        $content = trim(file_get_contents("php://input"));
        
       //Attempt to decode the incoming RAW post data from JSON.
        $decoded = json_decode($content, true);
		$temp=$decoded["temperatura"];
		$umid=$decoded["umidade"];
		$query="INSERT INTO sensor_data SET TEMP='{$temp}', UMID={$umid}";
		if(mysqli_query($connection, $query))
		{
			$response=array(
				'status' => 1,
				'status_message' =>'Product Added Successfully.'
			);
		}
		else
		{
			$response=array(
				'status' => 0,
				'status_message' =>'Product Addition Failed.'
			);
		}
		header('Content-Type: application/json');
		echo json_encode($response);
	}

?>