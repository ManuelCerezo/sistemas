#!/bin/bash
mysql_install_db --user=root
mysqld --user=root & 
sleep 5
mariadb -e " CREATE USER 'admin'@'localhost' IDENTIFIED BY 'password';"
mariadb -e "CREATE USER 'admin'@'%' IDENTIFIED BY 'password';"
mariadb -e "GRANT ALL ON *.* TO 'admin'@'localhost';"
mariadb -e "GRANT ALL ON *.* TO 'admin'@'%';"
mariadb -e "flush privileges;"
mariadb -e "CREATE DATABASE youtube;"
mariadb -D youtube -e "create table usuarios(NombreCompleto varchar(100), nombreUsuario varchar(100) PRIMARY KEY, email varchar(100), password varchar(100), passwordHint varchar(100), Habilitada boolean default true);"
mariadb -D youtube -e "create table videos(usuario varchar(100), tituloVideo varchar(100) PRIMARY KEY, etiquetasBusquedas varchar(100), rutaVideoEnS3 varchar(100) , fechaSubida varchar(100), FOREIGN KEY (usuario) REFERENCES usuarios (nombreUsuario) ON DELETE CASCADE);"
mariadb -D youtube -e "create table estadosCuenta(usuario varchar(100), intentosInicioSesion varchar(100), Habilitada boolean Not Null default true ,FOREIGN KEY (usuario) REFERENCES usuarios (nombreUsuario) ON DELETE CASCADE );"
mariadb -D youtube -e "create table comentarios(usuario varchar(100), tituloVideo varchar(100), comentario varchar(100), FOREIGN KEY (usuario) REFERENCES usuarios (nombreUsuario) ON DELETE CASCADE,Foreign key (tituloVideo) references videos (tituloVideo ) ON DELETE CASCADE);"
mariadb -D youtube -e "create table votos(tituloVideo varchar(100), likes int, dislikes int, Foreign key (tituloVideo) references videos (tituloVideo ) ON DELETE CASCADE);"
mariadb -D youtube -e "create table webpages(type varchar(100), pagename varchar(100));"
mariadb -D youtube -e "insert into  webpages values('success','success.html');"
mariadb -D youtube -e "commit;"
apachectl -DFOREGROUND
