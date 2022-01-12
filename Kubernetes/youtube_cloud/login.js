$(document).ready(main)
function main(){
    
}
function login(user,pass){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {username: user, password : pass, namefunction: "login_youtube"},
        function(data){
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            if(resultado.estado == 'correct'){
                window.location.replace(resultado.redirect);
            }else if(resultado.estado == 'username_notfound'){
                alert('[ERROR] User does not exists')
            }else if(resultado.estado == 'incorrect_password'){
                alert('[ERROR] Incorrect password')
            }
        }
    )
    
}

function register(user,name,apellido,emaill,pass,passhint){
    var fullname = name+" "+apellido
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {nombrecompleto: fullname, username:user,email:emaill,password : pass, passwordhint:passhint,namefunction: "register_youtube"},
        function(data){
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            if(resultado.estado == 'user_created'){
                window.location.reload();
            }else if(resultado.estado == 'user_alredy_exists'){
                alert('[ERROR] User exists')
            }
        }
    )
    
}