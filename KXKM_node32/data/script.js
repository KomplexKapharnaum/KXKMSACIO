var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener('load', onload);

function onload(event) {
    initWebSocket();
}

function getValues(){
    websocket.send("getValues");
}

function getConf(){
  websocket.send("getConf");
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
    getValues()
    getConf()
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    console.log("WS rcv: " + event.data)

    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj);

    for (var i = 0; i < keys.length; i++){
        var key = keys[i];
        console.log(key + " " + myObj[key])
        
        if (key.startsWith("slider")){
            document.getElementById(key).innerHTML = myObj[key];
            document.getElementById("slider"+ (i+1).toString()).value = myObj[key];
        }
        else {
            document.getElementById(key).value = myObj[key];
        }
    }
}

function updateConf(element) {
  var data = {};
  data[element.id] = document.getElementById(element.id).value;
  data = JSON.stringify(data);
  
  console.log("conf update: " + data);
  websocket.send("conf" + data);
}


function updateSliderPWM(element) {
  var sliderNumber = element.id.charAt(element.id.length-1);
  var sliderValue = document.getElementById(element.id).value;
  document.getElementById("sliderValue"+sliderNumber).innerHTML = sliderValue;
  console.log(sliderValue);
  websocket.send(sliderNumber+"s"+sliderValue.toString());
}