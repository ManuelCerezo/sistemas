var minombre= "Manuel"
var cantidad  = 0
var titulos = []
var urls = []
var usuarios = []
var cantidad_anterior = 0
var fechas = []

function mostrar(usuario,titulo,categoria,fecha,url){ //GUARDAR DATOS EN CACHÉ
    alert("usuario:"+usuario)
    alert("titulo: "+titulo)
    
    sessionStorage.usuario_video = usuario
    sessionStorage.titulo_video = titulo
    sessionStorage.categoria_video = categoria
    sessionStorage.fecha_video = fecha
    sessionStorage.url_video = url

    window.location.replace("video.html");
}


function create_spin(){

    
    $('#mostrador').append(
        '<div id="spin" class="ratio ratio-1x1 bg-light">'+
  '<div  class="d-flex justify-content-center">'+
    '<div class="spinner-border" role="status">'+
      '<span class="visually-hidden">Loading...</span>'+
    '</div>'+
  '</div>'+
  '</div>')
}

function remove_spin(){
    $('#spin').remove()
}
function remove_divs(){
    var p = 0;
    for(p=0;p<cantidad;p++){
        $('#tablero-'+p.toString()).remove()
    }
}

function set_divs(){
    var i = 0;
    
    for(i=0;i<sessionStorage.cantidad_videos;i++){
        $('#mostrador').append('<div id="tablero-'+i.toString()+'" class="container-fluid" style="text-align:left; padding-left:6px"></div>');
    }

}
function conversion(){
    cantidad = sessionStorage.cantidad_videos
    titulos = sessionStorage.titulos.split(',')
    urls = sessionStorage.urls.split(',')
    usuarios = sessionStorage.usuarios.split(',')
    fechas = sessionStorage.fecha.split(',')
}

function get_videos(tagg){

    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {tag:tagg,namefunction:'busar_videos'},
        function(data){ //Devulve: usuario, titulo, url, cantidad, fecha
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            sessionStorage.cantidad_videos = resultado.cantidad
            sessionStorage.usuarios = resultado.usuario
            sessionStorage.titulos = resultado.titulo
            sessionStorage.urls = resultado.url
            sessionStorage.fecha = resultado.fecha
            console.log(sessionStorage.cantidad_videos)
            console.log(sessionStorage.titulos)
            conversion()
            set_divs()
        }
    )
}