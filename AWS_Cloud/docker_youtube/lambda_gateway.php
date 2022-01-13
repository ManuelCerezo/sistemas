

<?php

	$aws_access_key_id='';

	$aws_secret_access_key='';

	$aws_session_token='';

	$lambda_func=$_GET['namefunction'];
	$payload='{"queryStringParameters": {';

	foreach ($_GET as $key => $value) {

		$payload .= '"' . $key . '":"' . $value .'",';

	}

	$payload=substr($payload, 0, -1);

	$payload.='}}';

	$cmd=' AWS_ACCESS_KEY_ID='. $aws_access_key_id .

	     ' AWS_SECRET_ACCESS_KEY='. $aws_secret_access_key .

             ' AWS_SESSION_TOKEN='. $aws_session_token . ' aws lambda invoke --function-name --region us-east-1 '. $lambda_func . ' --payload \'' . $payload . '\' /tmp/resp.json 2>&1';

	exec( $cmd,$result,$result2);

	header('Access-Control-Allow-Origin: *');

	$result=file_get_contents("/tmp/resp.json");

	$json=json_decode($result,true);

        echo json_encode($json['body']);
?>



