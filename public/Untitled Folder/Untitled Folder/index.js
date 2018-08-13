

function saveData(){
    var username = document.getElementById('username');
    var password = document.getElementById('password');

    insertData(username.value,password.value)
}

function insertData(username,password){
    var firebaseRef = firebase.database().ref("users");
    firebaseRef.push({
        username: username,
        password: password,
    });
    console.log("Insert Success");
    signUp();

}



function signUp(){
    var email = document.getElementById('username').value;
    var password = document.getElementById('password').value;
    firebase.auth().createUserWithEmailAndPassword(email, password).catch(function (error){
        var errorCode = error.code;
        var errorMessage = error.message;
        if(errorCode === 'auth/weak-password'){
            alert('The password is too weak');
        }
        else{
            alert(errorMessage);

        }
        console.log(error);
    });
}

function signIn(){
    var email = document.getElementById('username').value;
    var password = document.getElementById('password').value;
    firebase.auth().signInWithEmailAndPassword(email, password).catch(function (error){
        var errorCode = error.code;
        var errorMessage = error.message;
        console.log(errorMessage);
        console.log(errorCode);
        
        if (errorCode === 'auth/wrong-password'){
            alert('Wrong password');
            
        }
        else{
            alert(errorMessage);
            
        }
        
        
     
    });
    // console.log("OKKKK");
    // alert('logged insscc');
    window.location = 'setting.html';
}



// window.location = 'index.html';