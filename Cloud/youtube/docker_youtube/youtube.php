<?php
$servername = "localhost";
$database = "youtube";
$username = "admin";
$password = "password";

function _switch($op,$op1,$op2)
{

	switch($op){
		case "+":
			return $op1+$op2;
		break;
		case "-":
			return $op1-$op2;
		break;
	}
	return -1;
}


	//$metodo=$_GET["method"];
	$op1=floatval($_GET["op1"]);
	$op2=floatval($_GET["op2"]);
	$op=$_GET["op"];
	$result=0;
	$result=_switch($op, $op1, $op2);
        $redirectPage="";
	$mysqli = new mysqli($servername, $username, $password, $database);

        /* check connection */
        if ($mysqli->connect_errno) {
                error_log("Connect failed:". $mysqli->connect_error . "\n");
        }else{
                $mysqli->query('INSERT INTO resultados values(' . $op1 .','. $op2 .',"' . $op. '",'. $result .')');

                // Select queries return a resultset 
                if ($query = $mysqli->query("select pagename from webpages where type='success'")) {
                        //printf("Select returned %d rows.\n", $result->num_rows);
			$obj=$query->fetch_object();
        		$redirectPage=$obj->pagename;
                //free result set 
                        $query->close();
                }
        }
	header('Access-Control-Allow-Origin: *');
	$json= ['res' => $result , 'redirect' => $redirectPage ];

	echo json_encode(json_encode($json));
?>
