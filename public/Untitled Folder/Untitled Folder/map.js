

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
    var myCenter = new google.maps.LatLng(13.659613,100.296392);
    var gps1 = new google.maps.LatLng(51.508742,-0.120850);
    var gps2 = new google.maps.LatLng(40.508742,-0.120850); 
    var mapOptions = {center: myCenter, zoom: 5};
    var map = new google.maps.Map(mapCanvas,mapOptions);
    // var map = new google.maps.Map(mapCanvas,mapOptions);

    map.setZoom(15);
//    
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

            console.log(i);
              
            marker[i] = new google.maps.Marker({
                position: gps[i],
                icon: flag+".png",
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

   
function refrsh() {
     console.log("click");
     firebase.database().ref("settingID").once('value').then(function(dataSnapshot){
        // document.getElementById("unit").value = dataSnapshot.val();
        // var id_val = dataSnapshot.val();
       // var snapChild = snapshot.child();
        //console.log(snapChild);

        
        firebase.database().ref().child("id/A03/pLine").set(0);
        
        
        



    });

}


window.onload = startInterval;
function startInterval()
{
    setInterval("startTime();",20000);
}
var k = 1;
function startTime()
  {
    document.getElementById('time').innerHTML = Date(); 
    console.log(k);
    

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
      if(k == 1){
        
        k = 0;
      }
      // var map = new google.maps.Map(mapCanvas,mapOptions);
  
      // map.setZoom(15);
  //    

      var unit,temp,humid,flag,status,time,lat,long,infowindow;
      
      snapshot.forEach(function(childSnapshot) {       
          var key = childSnapshot.key;
          var childData = childSnapshot.val();       
          console.log(key);
          console.log(i);
     
          firebase.database().ref('id/'+key).once('value').then(function(snapshot) {
              console.log(i);
              unit = (snapshot.val() && snapshot.val().unit);
              temp = (snapshot.val() && snapshot.val().temp);
              humid = (snapshot.val() && snapshot.val().humid);
              flag = (snapshot.val() && snapshot.val().flag);
              status = (snapshot.val() && snapshot.val().status);
              time = (snapshot.val() && snapshot.val().time);
              lat = (snapshot.val() && snapshot.val().lat);
              long = (snapshot.val() && snapshot.val().long);
              // console.log(temp);
              // console.log(flag);
              
              document.getElementById("unit"+i).innerHTML= unit;
              document.getElementById("temp"+i).innerHTML = temp;
              document.getElementById("humid"+i).innerHTML = humid;
              document.getElementById("flag"+i).innerHTML= flag;
              document.getElementById("status"+i).innerHTML = status;
              document.getElementById("lastData"+i).innerHTML = time;
  
              i++;
              // console.log(humid);
              // console.log(long);
              gps[i] = new google.maps.LatLng(lat,long);
  
                
              marker[i] = new google.maps.Marker({
                  position: gps[i],
                  icon: flag+".png",
              });

              console.log(unit);
              console.log(temp);
              console.log(humid);
              console.log(flag);
                
              infowindow = new google.maps.InfoWindow({
                  content: '<div align=left><strong>'+"Unit: "+unit+'</strong><br>'+
                           "Temp: "+temp+'°C'+'<br>'+
                           "Humid: "+humid+"%"+'<br>'+
                           "Flag: "+flag+'</div>'
                          //  "Temp: "+temp+'<br>
                          //  "Temp: "+temp+'<br>'+ //"Hello World!"
              });

              // console.log(infowindow);
  
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


  }