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
    userName=str(event["queryStringParameters"]["username"]);
    passwd=str(event["queryStringParameters"]["password"]);
    redirectPage="dashboard.html";
    
    try:
        with conn.cursor() as cur:
            try:
                cur.execute("select Habilitada from usuarios where NombreUsuario like '"+userName+"'")
                conn.commit()
                estadoCuenta = str(cur.fetchone()[0])
            except:
                pass
            #print(estadoCuenta)
            try:
                cur.execute("select passwordHint from usuarios where NombreUsuario like '"+userName+"'")
                conn.commit()
                passwordHint=str(cur.fetchone()[0])
            except:
                pass
            #print(passwordHint)
            cur.execute("select NombreUsuario as name, password as pass from usuarios where nombreUsuario like '"+userName+"'")
            conn.commit()
            correct_credential = cur.fetchone()
            if correct_credential == None:
                return {
                    'statusCode': 200,
                    'headers': { 'Access-Control-Allow-Origin' : '*' },
                    'body' : json.dumps( { 'estado': 'username_notfound'})
                }
            elif correct_credential[1] != passwd:
                return {
                    'statusCode': 200,
                    'headers': { 'Access-Control-Allow-Origin' : '*' },
                    'body' : json.dumps( { 'estado': 'incorrect_password','estadoCuenta':estadoCuenta,'passwordHint':passwordHint})
                }
            elif correct_credential[0] == userName and correct_credential[1] == passwd:
                return {
                    'statusCode': 200,
                    'headers': { 'Access-Control-Allow-Origin' : '*' },
                    'body' : json.dumps( { 'estado': 'correct','estadoCuenta':estadoCuenta,'redirect': redirectPage})
                }
                
    except pymysql.MySQLError as e:    
        print (e)
    return {
        'statusCode': 200,
        'headers': { 'Access-Control-Allow-Origin' : '*' },
        'body' : json.dumps( { 'res': 'ok', 'redirect': redirectPage} )
    }
#      

