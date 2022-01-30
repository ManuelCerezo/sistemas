var ids_video = 0
var cant_rows = 0
var cant_cols = 0
const max_col = 5

$(document).ready(main)
function main(){
    init()
}

function init(){
    //alert(localStorage.usuario)
    $('#titulo').html(sessionStorage.usuario+"'s videos")
    create_videos_user()
}
function asler(){
    var a = 1
    alert(a)
}
function create_videos_user(){
    setTimeout(create_divs,2000)
    send_user()
}

function create_divs(){
    var campo = $('#misvideos')
    if (sessionStorage.cantidad != 0){
        var i = 0
        var p = 0
        var index = sessionStorage.cantidad / 5
        var aux = 0
        var h= 5

        if (Math.floor(index) < (sessionStorage.cantidad / 5 )){
            cant_rows = Math.ceil(index)
        }else if(((sessionStorage.cantidad / 5 ) / (sessionStorage.cantidad / 5 )) == 1){
            cant_rows = (sessionStorage.cantidad / 5 )
        }
        cant_cols = sessionStorage.cantidad
        if (sessionStorage.cantidad != undefined){
            console.log(sessionStorage.urls.split(',')[0])
            for(p=0;p<cant_rows;p++){
                campo.append('<div id="row-'+p+'"class="row"></div>')
            }
            for(i=0;i<cant_rows;i++){
                //alert("rellenando")
                for(p=0;p<5;p++){
                    $('#row-'+i.toString()).append('<div id="col-'+aux+'"class="col col-md "></div>')
                    aux++;
                }
            }
            p = 0
            i = 0
            aux = 0
            for(i=0;i<cant_cols;i++){
                if( i < h){
                    $('#col-'+i.toString()).append('<div class="ratio ratio-16x9 shadow-lg p-3">'+
                        '<iframe id="frame-'+aux+'"class="embed-responsive-item" src="'+sessionStorage.urls.split(',')[aux]+'"></iframe>'
                    +'</div>'
                    +'<h4 class="mt-2">'+sessionStorage.titulos.split(',')[aux]+'</h4>')
                    aux++;
                    console.log(p)
                    console.log(h)
                }else{
                    p++
                    h = h + h
                    console.log(p)
                    i--;
                }
            }
        }else{
            alert("error servidor")
        }
    }else{
        campo.append('<h1 class="text-secondary text-center"> Upload videos <span> <svg xmlns="http://www.w3.org/2000/svg" width="50" height="50" fill="currentColor" class="bi bi-cloud-upload-fill" viewBox="0 0 16 16">'
        +'<path fill-rule="evenodd" d="M8 0a5.53 5.53 0 0 0-3.594 1.342c-.766.66-1.321 1.52-1.464 2.383C1.266 4.095 0 5.555 0 7.318 0 9.366 1.708 11 3.781 11H7.5V5.707L5.354 7.854a.5.5 0 1 1-.708-.708l3-3a.5.5 0 0 1 .708 0l3 3a.5.5 0 0 1-.708.708L8.5 5.707V11h4.188C14.502 11 16 9.57 16 7.773c0-1.636-1.242-2.969-2.834-3.194C12.923 1.999 10.69 0 8 0zm-.5 14.5V11h1v3.5a.5.5 0 0 1-1 0z"/>'
      +'</svg></span></h1>')
    }
    getAWSKeys()
}
function send_user(){
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {username: sessionStorage.usuario,namefunction:'showUser_videos'},
        function(data){
            var aux =""
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
            sessionStorage.cantidad = resultado.cantidad
            sessionStorage.titulos = resultado.titulo
            sessionStorage.urls = resultado.url
            console.log(resultado)
        }
    )
}

function getAWSKeys(){
	var asd=$.get(
 			"http://52.5.234.126/keys_gateway.php",
		    {},
		    function(data) {

		       var json=JSON.parse(data);
                       json=JSON.parse(json);
		       document.getElementById("Policy").value = json.stringToSign;
		       document.getElementById("X-Amz-Credential").value = json.xAmzCredential;		
		       document.getElementById("X-Amz-Date").value = json.amzDate;		
		       document.getElementById("X-Amz-Signature").value = json.stringSigned;	
		       document.getElementById("X-Amz-Security-Token").value = json.securityToken;	
			
		    }
		)
  
}
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }

function sleepFor(sleepDuration){

    var now = new Date().getTime();

    while(new Date().getTime() < now + sleepDuration){ 

        /* Do nothing */ 

    }

}
function setKeyFilename(){
    var bucket = 'http://bucketutadpsdib028.s3-website-us-east-1.amazonaws.com/'
    var title = document.getElementById('title').value
    var date = document.getElementById('date').value
    var tag = document.getElementById('tag').value
    bucket = bucket + get_name(document.getElementById('input_file').value)
    document.getElementById("key").value = document.getElementById("input_file").value.substring(document.getElementById("input_file").value.lastIndexOf('\\')+1);
    send_data_video(title,tag.toLowerCase(),bucket,date)
    sleepFor(5000)
}



function get_name(string){
    var name = string.split('\\')
    return name[name.length -1]
}

function send_data_video(title,etiqueta,link,fecha){
    //username, titulo, tag, url, datetime
    var peticion = $.get(
        "http://52.5.234.126/lambda_gateway.php",
        {username: sessionStorage.usuario,titulo:title,tag:etiqueta,url:link,datetime:fecha,namefunction:'upload_videos'},
        function(data){
            var json = JSON.parse(data)
            resultado = JSON.parse(json)
        }
    )
}