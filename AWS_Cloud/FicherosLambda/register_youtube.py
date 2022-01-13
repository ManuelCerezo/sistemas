import sys
import logging
import pymysql
import json

rds_host = "52.5.234.126"

username = "admin"
password ="password"
dbname = "youtube"

try:
    conn = pymysql.connect(rds_host, user=username, passwd=password, db=dbname, connect_timeout=10, port=3306)
except pymysql.MySQLError as e:
    print (e)
    sys.exit()


def lambda_handler(event , context):
    nombreCompleto=str(event["queryStringParameters"]["nombrecompleto"]);
    userName=str(event["queryStringParameters"]["username"]);
    email=str(event["queryStringParameters"]["email"]);
    passwd=str(event["queryStringParameters"]["password"]);
    passwordHint=str(event["queryStringParameters"]["passwordhint"]);
    #habilitada=event["queryStringParameters"]["habilitada"];
    
    
    redirectPage="login.html";
    
    try:
        with conn.cursor() as cur:
            cur.execute("select NombreUsuario as name, password as pass from usuarios where nombreUsuario like '"+userName+"'")
            conn.commit()
            correct_credential = cur.fetchone()
            if correct_credential == None:#Si no existe el usuario
                cur.execute("insert into usuarios (nombreCompleto,nombreUsuario,email,password,passwordHint) values ('"+nombreCompleto+"','"+userName+"','"+email+"','"+passwd+"','"+passwordHint+"')")
                conn.commit()
                return {
                    'statusCode': 200,
                    'headers': { 'Access-Control-Allow-Origin' : '*' },
                    'body' : json.dumps( { 'estado': 'user_created','redirect':'redirectPage'})
                }
            elif correct_credential[0] == userName:
                return {
                    'statusCode': 200,
                    'headers': { 'Access-Control-Allow-Origin' : '*' },
                    'body' : json.dumps( { 'estado': 'user_already_exists'})
                }

    except pymysql.MySQLError as e:    
        print (e)
