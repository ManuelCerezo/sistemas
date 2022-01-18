var ids_video = 0
var cant_rows = 0
var cant_cols = 0
const max_col = 5

$(document).ready(main)
function main(){
    init()
}

function init(){
    //alert(session.usuario) 
    sessionStorage.checkLike = 'undefined'
    sessionStorage.checkDisLike = 'undefined'

    $('#Usuario').html(sessionStorage.usuario_video)
    $('#titulo').html(sessionStorage.tituloVideo)
    $('#videoUser').attr('src',sessionStorage.url)
    $('#fechaPublicacion').html(sessionStorage.fechaVideo)
    send_nameVideo()
}
function send_nameVideo(){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {titulovideo: sessionStorage.tituloVideo,namefunction:'info_video'},
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
    if (sessionStorage.checkLike == 'undefined'){
        sessionStorage.checkLike = 'false'
    }
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
    console.log("entro aquii")
    if (sessionStorage.checkDisLike == 'undefined'){
        console.log("entroo")
        sessionStorage.checkDisLike = 'false'
    }
    if(sessionStorage.checkDisLike == 'false'){

        if(sessionStorage.checkLike == 'true'){//quitamos like
            $('#likes').html((sessionStorage.likes = parseInt(sessionStorage.likes)-1))
            sessionStorage.checkLike = 'false'
            send_voto(-1,0)
            $('#botonLike').attr('class','bi bi-hand-thumbs-up-fill')

        $('#dislikes').html(sessionStorage.dislikes = parseInt(sessionStorage.dislikes)+1)
        sessionStorage.checkDisLike = 'true'
        send_voto(0,1)
        $('#botonDisLike').attr('class','bi bi-hand-thumbs-down-fill text-primary')
        }
    }
    else if(sessionStorage.checkDisLike == 'true'){
        console.log("te lo quito")
        $('#dislikes').html(sessionStorage.dislikes = parseInt(sessionStorage.dislikes)-1)
        sessionStorage.checkDisLike = 'false'
        send_voto(0,-1)
        $('#botonDisLike').attr('class','bi bi-hand-thumbs-down-fill')
    }
}

function send_voto(aa,bb){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {titulovideo: sessionStorage.tituloVideo,likes:aa,dislikes:bb,namefunction:'subir_voto'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            console.log(resultado)
        }
    )
}

function create_comentario(user,coment){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {username: sessionStorage.usuario,titulovideo:sessionStorage.tituloVideo,comentario:coment,namefunction:'subir_comentario'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            console.log(resultado)
        }
    )
}

function get_comentarios(){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {titulovideo: sessionStorage.tituloVideo,namefunction:'get_comentarios'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            sessionStorage
            console.log(resultado)
        }
    )
}
function get_name(string){
    var name = string.split('\\')
    return name[name.length -1]
}