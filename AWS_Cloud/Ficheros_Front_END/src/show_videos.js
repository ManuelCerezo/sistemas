var minombre= "Manuel"
var cantidad  = 0
var titulos = []
var urls = []
var usuarios = []
var cantidad_anterior = 0
var fechas = []

function mostrar(){ //GUARDAR DATOS EN CACHÉ
    window.location.replace('comentario_voto.html');
}

function create_spin(){
    
    $('#mostrador').append(
        '<div id="spin" className="row">'+
            '<div className="col"></div>'+
                '<div className="col-9 bg-white p-5 bg-light">'+
                    '<div class="ratio ratio-4x3 ">'+
                        '<div  class="d-flex justify-content-center">'+
                            '<div class="spinner-border" role="status">'+
                                '<span class="visually-hidden">Loading...</span>'+
                            '</div>'+
                        '</div>'+
                    '</div>'+
                '</div>'+
            '<div className="col"></div>'+
        '</div>')
}
function removetablero(){
    $('#tablero').remove()
}
function settablero(){
    $('#mostrador').append('<div id="tablero" class="container-fluid" style="text-align:left; padding-left:6px"></div>')
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