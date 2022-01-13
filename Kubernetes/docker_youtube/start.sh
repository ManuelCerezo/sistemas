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
mariadb -D youtube -e "create table usuarios(NombreCompleto varchar(50), nombreUsuario varchar(50) PRIMARY KEY, email varchar(100), password varchar(100), passwordHint varchar(100), Habilitada boolean not null default true);"
mariadb -D youtube -e "create table videos(usuario varchar(10), etiquetasBusquedas varchar(50), size int, rutaVideoEnS3 varchar(100) PRIMARY KEY, fechaSubida DATETIME, FOREIGN KEY (usuario) REFERENCES usuarios (nombreUsuario) ON DELETE CASCADE);"
mariadb -D youtube -e "create table estadosCuenta(usuario varchar(10), intentosInicioSesion int, Habilitada boolean not null default true ,FOREIGN KEY (usuario) REFERENCES usuarios (nombreUsuario) ON DELETE CASCADE, FOREIGN KEY (Habilitada) REFERENCES usuarios (Habilitada) ON DELETE CASCADE);"

mariadb -D youtube -e "create table comentarios(usuario varchar(10), rutaVideoEnS3 varchar(100), contenido varchar(100), idComentario int PRIMARY KEY, FOREIGN KEY (usuario) REFERENCES usuarios (nombreUsuario) ON DELETE CASCADE, FOREIGN KEY (rutaVideoEnS3) REFERENCES videos (rutaVideoEnS3) ON DELETE CASCADE );"
mariadb -D youtube -e "create table votos(usuario varchar(10), rutaVideoEnS3 varchar(100), valor boolean, FOREIGN KEY (usuario) REFERENCES usuarios (nombreUsuario) ON DELETE CASCADE, FOREIGN KEY (rutaVideoEnS3) REFERENCES videos (rutaVideoEnS3) ON DELETE CASCADE );"
mariadb -D youtube -e "create table webpages(type varchar(20), pagename varchar(100));"
mariadb -D youtube -e "insert into  webpages values('success','success.html');"
mariadb -D youtube -e "commit;"
apachectl -DFOREGROUND

