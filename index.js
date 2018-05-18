var unit = document.getElementById("unit");
var ssid = document.getElementById("ssid");
var pass = document.getElementById("pass");
var line = document.getElementById("line");
var line2 = document.getElementById("line2");

var button = document.getElementById("button");
var button2 = document.getElementById("button2");
var head = document.getElementById("head");

myclick2();

function myclick() {
    var unit_val = unit.value;
    var ssid_val = ssid.value;
    var pass_val = pass.value;
    var line_val = line.value;
    var line2_val = line2.value;

    window.alert("update success");
    var firebaseRef = firebase.database().ref();

    //firebaseRef.set(val);
    //firebaseRef.child(val).set("ssssss");

    //firebaseRef.set("xx");
    firebaseRef.child("unit").set(unit_val);
    firebaseRef.child("ssid1").set(ssid_val);
    firebaseRef.child("pass1").set(pass_val);
    firebaseRef.child("line").set(line_val);
    firebaseRef.child("line2").set(line2_val);
    firebaseRef.child("pub").set(1);
       
}

function myclick1() {
    document.getElementById("unit").value = "";
    document.getElementById("ssid").value = "";
    document.getElementById("pass").value = "";
    document.getElementById("line").value = "";
    document.getElementById("line2").value = "";
    


    
}

function myclick2() {
    
    firebase.database().ref("unit").once('value').then(function(dataSnapshot){
        document.getElementById("unit").value = dataSnapshot.val();       
    });
    firebase.database().ref("ssid1").once('value').then(function(dataSnapshot){
        document.getElementById("ssid").value = dataSnapshot.val();       
    });
    firebase.database().ref("pass1").once('value').then(function(dataSnapshot){
        document.getElementById("pass").value = dataSnapshot.val();       
    });
    firebase.database().ref("line").once('value').then(function(dataSnapshot){
        document.getElementById("line").value = dataSnapshot.val();       
    });
    firebase.database().ref("line2").once('value').then(function(dataSnapshot){
        document.getElementById("line2").value = dataSnapshot.val();       
    });

}

