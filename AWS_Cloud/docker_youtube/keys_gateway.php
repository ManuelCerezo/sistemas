<?php
$aws_access_key_id='ASIAXI3U6I5B34YL2QFJ';
$aws_secret_access_key='aPr4xxDQ4o4q5ZAiA9mTiJ7tjNJl++g87JGJTZKi';
$aws_session_token='FwoGZXIvYXdzEHQaDMeeIfBFsI+ISZ7fESK/AUBpz8vWOXXruMfgs7o/idbH/Vm3VVQ4YZFE2ED9sjoQ8aT4TuoNV14iTYacQHHNGoNn1eMmVxC6kk/w3oXunjkTfXiszhinvW/RSTVh5/SoD7UisV1A6TEaIhF5Oagb87AxKEe+xKSqkdoBYMTKPvOaOBMB8tx8/NzfZPtAboOSuUXdb+gMSBQqL1nqcT95ayCvsMiyYGSPIyQ1j2d69yYUtAg/O7VARTQP5+UZH5dNoviW3tW2zuedK09IUBLLKJT/ho8GMi3aeAlk7zhPfaiE58JPSdhZC/agAVdlzU65Ch0QbzpO04/zP3XAQ5gs4V0mJUY=';
   $lambda_func='s3Keys';
        $payload='{"queryStringParameters": { "ak":"' . $aws_access_key_id . 
                    '", "sk":"' .$aws_secret_access_key .
                    '", "st":"' . $aws_session_token . '" }}';

        $cmd=' AWS_ACCESS_KEY_ID='. $aws_access_key_id .

             ' AWS_SECRET_ACCESS_KEY='. $aws_secret_access_key .

             ' AWS_SESSION_TOKEN='. $aws_session_token . ' aws lambda invoke --region us-east-1 --function-name '. $lambda_func . ' --payload \''. $payload . '\' /tmp/resp.json 2>&1';

        exec( $cmd,$result,$result2);

        header('Access-Control-Allow-Origin: *');

        $result=file_get_contents("/tmp/resp.json");

        $json=json_decode($result,true);

        echo json_encode($json['body']);
//      echo $payload;
?>

