function line(){
    var moment = require('moment');
    require('moment-precise-range-plugin');
    var request = require('request');
    
    const token = "I4mD7RAD8c76FQTSqphq834ooD5dJZv2COKNB8pCqTh";
    const date_travel = {'year':'2017', 'month':'04', 'date':'22'};
    // Set the headers
    var headers = {
        'User-Agent':       'Super Agent/0.0.1',
        'Content-Type':     'application/x-www-form-urlencoded'
    }
    // Configure the request
    var options = {
        'url': 'https://notify-api.line.me/api/notify',
        'method': 'POST',
        'headers': headers,
        'auth': {
           'bearer': token
        },
        'form': {
           'message': ''
        }
    }
    
    // Test
    console.log('Test');
    options.form.message = 'อีก '+countDown(date_travel)+' วัน จะเริ่มต้นทริปเที่ยวกระบี่';
    
    // Check Alert Coundown
    if(checkCountDownEnd(date_travel)){
        console.log('Check Alert Coundown: '+moment().utcOffset('+0700').format());
        if(moment().utcOffset('+0700').format("HH") == '07'){
            options.form.message = 'อีก '+countDown(date_travel)+' วัน จะเริ่มต้นทริปเที่ยวกระบี่';
            console.log('Alert Coundown');
            request(options);
        }
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017041308'){
        options.form.message = 'สุขสันต์วันสงกรานต์ เล่นน้ำอย่างมีความสุขนะครับ แต่อย่าเล่นจนเพลินจนไม่สบายนะครับ เดี๋ยวไม่มีแรงเที่ยวทริปกระบี่ด้วยกัน ด้วยความหวังดีจาก NineFern Robot';
        request(options);
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017041713'){
        options.form.message = 'เตรียมหาข้อมูลเที่ยวกระบี่กัน';
        request(options);
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017042118'){
        options.form.message = 'อย่าลืมเตรียมเอกสารขึ้นเครื่องบินอย่าง เช่น บัตรประชาชน, บอร์ดดิ้งพาส, QR-Code, Booking-Number, ใบเช่ารถ, วงเงินบัตรเครดิต';
        request(options);
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017042119'){
        options.form.message = 'อย่าลืม Check-in ผ่านเว็บไซต์นะครับ';
        request(options);
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017042206'){
        options.form.message = 'Check List';
        options.form.message += '\n+ บัตรประชาชน';
        options.form.message += '\n+ เอกสารขึ้นบิน Booking-Number และ บอร์ดดิ้งพาส หรือ QR-Code';
        options.form.message += '\n+ กล้องและเมมโมรี่';
        options.form.message += '\n+ ที่ชาร์แบตโทรศัพท์';
        options.form.message += '\n+ กระเป๋ากันน้ำ';
        options.form.message += '\n+ ทิ้งงาน ทิ้งสิ่งแย่ๆไว้ที่บ้าน พร้อมเที่ยวกระบี่อย่างมีความสุข';
        request(options);
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017042212'){
        options.form.message = 'รายละเอียดเที่ยวบิน กรุงเทพ-กระบี่';
        options.form.message += '\n+ Booking Number xxxxxx';
        options.form.message += '\n+ Flight FD xxxxxx';
        options.form.message += '\n+ เวลา 16.10 - 17.20 น.';
        options.form.message += '\n+ ควรโหลดกระเป๋าก่อน 15.25 น. (เผื่อเวลาไว้หน่อยนะ)';
        options.form.message += '\n+ ควรอยู่หน้าประตูขึ้นเครื่องบินก่อน 15.50 น.';
        options.form.message += '\n+ อย่าลืมซื้อหมากฝรั่งก่อนขึ้นเครื่องด้วยครับ';
        request(options);
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017042217'){
        options.form.message = 'ตารางสำหรับวันที่ 22';
        options.form.message += '\n17.20-18.00 น. เช่ารถ';
        options.form.message += '\n18.00-21.00 น. กินข้าว';
        options.form.message += '\n21.00-21.30 น. เข้าที่พักซื้อของกินง่ายสำหรับพรุ่งนี้เช้า';
        request(options);
    }
    
    if(moment().utcOffset('+0700').format("YYYYMMDDHH") == '2017042412'){
        options.form.message = 'รายละเอียดเที่ยวบิน กระบี่-กรุงเทพ';
        options.form.message += '\n+ Booking Number xxxxxx';
        options.form.message += '\n+ Flight FD xxxxxx';
        options.form.message += '\n+ เวลา 17.50 - 19.10 น.';
        options.form.message += '\n+ ควรโหลดกระเป๋าก่อน 17.05 น. (เผื่อเวลาไว้หน่อยนะ)';
        options.form.message += '\n+ ควรอยู่หน้าประตูขึ้นเครื่องบินก่อน 17.30 น.';
        options.form.message += '\n+ อย่าลืมซื้อหมากฝรั่งก่อนขึ้นเครื่องด้วยครับ';
        request(options);
    }
    
    function countDown(input){
        var data = input;
        var oneDay = 24*60*60*1000; // hours*minutes*seconds*milliseconds
        var firstDate = moment().format();
        var secondDate = moment(data.year+'-'+data.month+'-'+data.date);
        // {years : 0, months : 1, days : 2, hours : 3, minutes : 4, seconds : 5}
        var diffDays = moment.preciseDiff(firstDate,secondDate,true);
        if(diffDays.hours > 0 || diffDays.minutes > 0 || diffDays.seconds > 0){diffDays.days++;}
        return diffDays.days;
    }
    
    function checkCountDownEnd(input){
        var data = input;
        return moment(moment().format()).isBefore(moment(data.year+'-'+data.month+'-'+data.date));
    }

}



function pubID(){
    var id = document.getElementById("id").value;
    
    console.log("ok_pubID");
    console.log(id);
    
    var firebaseRef = firebase.database().ref("id").orderByKey();
    firebaseRef.once('value').then(function(dataSnapshot){
        var i = 0;
        // var childkey = ["a","b"];
        var childkey=[];
        dataSnapshot.forEach(function(childSnapshot){
            i++;
            
            // var childkey[i] = childSnapshot.key;
            // var childData[i] = childSnapshot.val();
            childkey.push(childSnapshot.key);
            // console.log(childkey[i]);
            // console.log(childData);
            console.log(i);
        });
        console.log(childkey[0]);
        if (childkey.indexOf !== undefined) 
            result = childkey.indexOf(id);
        else result = customSlowerSearch(childkey, target);

        console.log(result);
        if(result==-1){
            alert("NO Device ID..");
        }
        else{
            var firebaseRef = firebase.database().ref();
            firebaseRef.child("settingID").set(id);
            console.log("ok!!!!");
            window.location = 'setting.html';
        }
    });
}

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