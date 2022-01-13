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
    try:
        with conn.cursor() as cur:
            
            cur.execute("UPDATE usuarios SET Habilitada = 0  WHERE nombreUsuario = '"+userName+"'")
            conn.commit()
            
                
    except pymysql.MySQLError as e:    
        print (e)
#      

