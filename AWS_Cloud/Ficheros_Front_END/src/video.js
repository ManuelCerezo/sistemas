var ids_video = 0
var cant_rows = 0
var cant_cols = 0
const max_col = 5

var cantidad = 0
var usuarios_comentarios = []
var comentarios = []




$(document).ready(main)
function main(){
    init()
}

function init(){
    //alert(session.usuario) 
    sessionStorage.checkLike = 'false'
    sessionStorage.checkDisLike = 'false'
    
    $('#Usuario').html(sessionStorage.usuario_video)
    $('#titulo').html(sessionStorage.titulo_video)
    $('#videoUser').attr('src',sessionStorage.url_video)
    $('#fechaPublicacion').html(sessionStorage.fecha_video)
    send_nameVideo()
    get_comentarios()
}

function send_nameVideo(){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {titulovideo: sessionStorage.titulo_video,namefunction:'info_video'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            console.log(resultado)
            sessionStorage.likes = resultado.likes
            sessionStorage.dislikes = resultado.dislikes
            $('#likes').html(sessionStorage.likes)
            $('#dislikes').html(sessionStorage.dislikes)
        }
    )
}
function botonLike(){
    if(sessionStorage.checkLike == 'false'){
        if(sessionStorage.checkDisLike == 'true'){//quitamos
            $('#dislikes').html(sessionStorage.dislikes = parseInt(sessionStorage.dislikes)-1)
            sessionStorage.checkDisLike = 'false'
            send_voto(0,-1)
            $('#botonDisLike').attr('class','bi bi-hand-thumbs-down-fill')
        }
        $('#likes').html((sessionStorage.likes = parseInt(sessionStorage.likes)+1))
        sessionStorage.checkLike = 'true'
        send_voto(1,0)
        $('#botonLike').attr('class','bi bi-hand-thumbs-up-fill text-primary')
    }
    else if(sessionStorage.checkLike == 'true'){
        $('#likes').html((sessionStorage.likes = parseInt(sessionStorage.likes)-1))
        sessionStorage.checkLike = 'false'
        send_voto(-1,0)
        $('#botonLike').attr('class','bi bi-hand-thumbs-up-fill')
    }
}
function botonDisLike(){
    if(sessionStorage.checkDisLike == 'false'){
        if(sessionStorage.checkLike == 'true'){//quitamos
            $('#likes').html(sessionStorage.likes = parseInt(sessionStorage.likes)-1)
            sessionStorage.checkLike = 'false'
            send_voto(-1,0)
            $('#botonLike').attr('class','bi bi-hand-thumbs-down-fill')
        }
        $('#dislikes').html((sessionStorage.dislikes = parseInt(sessionStorage.dislikes)+1))
        sessionStorage.checkDisLike = 'true'
        send_voto(0,1)
        $('#botonDisLike').attr('class','bi bi-hand-thumbs-up-fill text-primary')
    }
    else if(sessionStorage.checkDisLike == 'true'){
        console.log("Entro")
        $('#dislikes').html((sessionStorage.dislikes = parseInt(sessionStorage.dislikes)-1))
        sessionStorage.checkDisLike = 'false'
        send_voto(0,-1)
        $('#botonDisLike').attr('class','bi bi-hand-thumbs-up-fill')
    }
}

function send_voto(aa,bb){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {titulovideo: sessionStorage.titulo_video,likes:aa,dislikes:bb,namefunction:'subir_voto'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            console.log(resultado)
        }
    )
}



function send_comentario(comentario){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {username: sessionStorage.usuario,titulovideo:sessionStorage.titulo_video,comentario:comentario,namefunction:'subir_comentario'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            
        }
    )
}

function get_comentarios(){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {titulovideo: sessionStorage.titulo_video,namefunction:'get_comentarios'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            sessionStorage.cantidad_comentarios = resultado.cantidad
            sessionStorage.usuarios_comentarios = resultado.usuarios
            sessionStorage.comentarios = resultado.comentarios
        }
    )
    init_comentarios()
}
function set_div_coment(){
    cantidad++
    $('#tablon_comentarios').append('<div id="comentario-'+(cantidad-1).toString()+'" ></div>')
}
function init_comentarios(){
    var i = 0
    for(i = 0;i<sessionStorage.cantidad_comentarios;i++){
        $('#tablon_comentarios').append('<div id="comentario-'+i.toString()+'" ></div>')
    }
    cantidad = parseInt(sessionStorage.cantidad_comentarios)
}

function get_name(string){
    var name = string.split('\\')
    return name[name.length -1]
}

