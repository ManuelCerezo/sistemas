$(document).ready(main)
function main(){
    
}

function bloquear_account(user,pass){
    
    incorrect_password= 0;
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {username: user, namefunction: "block_account"},
        function(data){
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
        }
    )
}
function set_passhint(str){
    passwordhint = str;
}
function login(user,pass){
    
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {username: user, password : pass, namefunction: "login_youtube"},
        function(data){
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            if(resultado.estado == 'correct' && resultado.estadoCuenta=='1'){
                sessionStorage.usuario = user //Guardamos el nombre de usuario correspondiente en la caché de sesion.
                window.location.replace(resultado.redirect);
            }else if(resultado.estado =='correct' && resultado.estadoCuenta == '0'){
                set_login_flag(2)
            }else if(resultado.estado == 'username_notfound'){
                set_login_flag(0)
            }else if(resultado.estado == 'incorrect_password'){
                set_login_flag(1)
                set_passhint(resultado.passwordHint)
            }
        }
    )
}
function set_login_flag(num){
    login_flag = num
}
function set_flag(num){
    register_flag = num
}

function register(user,name,apellido,emaill,pass,passhint){
    var fullname = name+" "+apellido
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {nombrecompleto: fullname, username:user,email:emaill,password : pass, passwordhint:passhint,namefunction: "register_youtube",habilitada:true},
        function(data){
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            if(resultado.estado == 'user_created'){
                set_flag(0)
            }else if(resultado.estado == 'user_already_exists'){
                set_flag(1)
            }
        }
    );
    
}