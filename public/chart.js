

// document.getElementById("unit") = "pppppppppp";

// document.getElementById("unit_").innerHTML = "ngParagraph chaedasv!";

// firebase.database().ref("id/A01/unit").once('value').then(function(dataSnapshot){
//     document.getElementById("unit").innerHTML = dataSnapshot.val();       
// });
// firebase.database().ref("temp").once('value').then(function(dataSnapshot){
//     document.getElementById("temp1").innerHTML = dataSnapshot.val();       
// });
// firebase.database().ref("humid").once('value').then(function(dataSnapshot){
//     document.getElementById("humid1").innerHTML = dataSnapshot.val();       
// });
// firebase.database().ref("flag").once('value').then(function(dataSnapshot){
//     document.getElementById("flag1").innerHTML = dataSnapshot.val();       
// });
//firebase.database().ref("settingID").once('value').then(function(dataSnapshot){
//    console.log(dataSnapshot.val());



            
            


firebase.database().ref("id").orderByKey().once("value").then(function(snapshot) {
    var i=1;
    var marker = [];
    var gps = [];
              var mapCanvas = document.getElementById("map");
              var myCenter = new google.maps.LatLng(13.661732,100.298855);
              var gps1 = new google.maps.LatLng(51.508742,-0.120850);
              var gps2 = new google.maps.LatLng(40.508742,-0.120850); 
              var mapOptions = {center: myCenter, zoom: 5};
              var map = new google.maps.Map(mapCanvas,mapOptions);

              map.setZoom(15);

              
    console.log(i)
    snapshot.forEach(function(childSnapshot) {
        
        var key = childSnapshot.key;
        var childData = childSnapshot.val();
        
        console.log(key);
    
    firebase.database().ref('id/'+key).once('value').then(function(snapshot) {
        var unit = (snapshot.val() && snapshot.val().unit);
        var temp = (snapshot.val() && snapshot.val().temp);
        var humid = (snapshot.val() && snapshot.val().humid);
        var flag = (snapshot.val() && snapshot.val().flag);
        var status = (snapshot.val() && snapshot.val().status);
        var time = (snapshot.val() && snapshot.val().time);
        var lat = (snapshot.val() && snapshot.val().lat);
        var long = (snapshot.val() && snapshot.val().long);
        console.log(lat);
        console.log(long);
        
        document.getElementById("unit"+i).innerHTML= unit;
        document.getElementById("temp"+i).innerHTML = temp;
        document.getElementById("humid"+i).innerHTML = humid;
        document.getElementById("flag"+i).innerHTML= flag;
        document.getElementById("status"+i).innerHTML = status;
        document.getElementById("lastData"+i).innerHTML = time;

        

        i++;
        console.log(lat);
        console.log(long);
        gps[i] = new google.maps.LatLng(lat,long);


        // ...
             // var f = "sasvasv";
              

              console.log(i);
              //-----------------------------------------
                marker[i] = new google.maps.Marker({
                position: gps[i],
                // animation: google.maps.Animation.BOUNCE
                icon: flag+"ball.png",
                
              });
              
              var infowindow = new google.maps.InfoWindow({
                content: '<div align=left><strong>'+"Unit: "+unit+'</strong><br>'+
                         "Temp: "+temp+'°C'+'<br>'+
                         "Humid: "+humid+"%"+'<br>'+
                         "Flag: "+flag+'</div>'
                        //  "Temp: "+temp+'<br>
                        //  "Temp: "+temp+'<br>'+ //"Hello World!"
              });
              infowindow.open(map,marker[i]);
              marker[i].setMap(map);

              // Zoom to 9 when clicking on marker
              google.maps.event.addListener(marker[i],'click',function() {
                map.setZoom(20);
                map.setCenter(marker[i].getPosition());
              });

              //-----------------------------------------
            //   var marker1 = new google.maps.Marker({
            //     position: gps2,
            //     // animation: google.maps.Animation.BOUNCE
            //     icon: "pinkball.png",
                
            //   });
            //   var infowindow = new google.maps.InfoWindow({
            //     content: "xxxxxxxxx"  //"Hello World!"
            //   });
            //   infowindow.open(map,marker1);
            //   marker1.setMap(map);

            //   // Zoom to 9 when clicking on marker
            //   google.maps.event.addListener(marker1,'click',function() {
            //     map.setZoom(9);
            //     map.setCenter(marker1.getPosition());
            //   });
              //------------------------------------------


        //..
        });
        
    });
 
});

setTimeout(function() {
   // window.location.reload();//your code to be executed after 1 second
}, 5000);



// document.getElementById("unit_").innerHTML = unit;



   

    window.addEventListener("load", getData(genFunction));

    function getData(callbackIN) {
    //   var ref = firebase.database().ref("data");
      var ref = firebase.database().ref("id/A02/logDHT");
      ref.once('value').then(function (snapshot) {
        callbackIN(snapshot.val())
        console.log(snapshot.val());
      });
    }

    function genFunction(data) {
      var cdata = [];
      var len = data.length;
      for(var i=1; i<len; i++) {
        cdata.push({
          label: data[i]['time'],
          value: data[i]['temp']
        });
        console.log(cdata);
      }


    var firebaseChart = new FusionCharts({
        type: 'area2d',
        renderAt: 'chart-container',
        width: '650',
        height: '400',
        dataFormat: 'json',
        dataSource: {
            "chart": {
                "caption": "Website Visitors Trend",
                "subCaption": "Last 7 Days{br}ACME Inc.",
                "subCaptionFontBold": "0",
                "captionFontSize": "20",
                "subCaptionFontSize": "17",
                "captionPadding": "15",
                "captionFontColor": "#8C8C8C",
                "baseFontSize": "14",
                "baseFont": "Barlow",
                "canvasBgAlpha": "0",
                "bgColor": "#FFFFFF",
                "bgAlpha": "100",
                "showBorder": "0",
                "showCanvasBorder": "0",
                "showPlotBorder": "0",
                "showAlternateHGridColor": "0",
                "usePlotGradientColor": "0",
                "paletteColors": "#6AC1A5",
                "showValues": "0",
                "divLineAlpha": "5",
                "showAxisLines": "1",
                "drawAnchors": "0",
                "xAxisLineColor": "#8C8C8C",
                "xAxisLineThickness": "0.7",
                "xAxisLineAlpha": "50",
                "yAxisLineColor": "#8C8C8C",
                "yAxisLineThickness": "0.7",
                "yAxisLineAlpha": "50",
                "baseFontColor": "#8C8C8C",
                "toolTipBgColor": "#FA8D67",
                "toolTipPadding": "10",
                "toolTipColor": "#FFFFFF",
                "toolTipBorderRadius": "3",
                "toolTipBorderAlpha": "0",
                "drawCrossLine": "1",
                "crossLineColor": "#8C8C8C",
                "crossLineAlpha": "60",
                "crossLineThickness": "0.7",
                "alignCaptionWithCanvas": "1"
            },
            "data": cdata
        }
    });

    firebaseChart.render();

    }

    
   
function myclick3() {
     console.log("click");

    
}

