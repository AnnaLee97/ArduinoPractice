const express = require('express');
const app = express();

app.get('/', (req, res) => res.send('Hello World!'));


var fs = require("fs");

app.get('/update', function(req, res) {
        var d = new Date();
        if(req.query.api_key == '92Z8J256C052XR8W'){
                fs.appendFile('temperature.txt', d.toString() + ', temp: '+req.query.field1+'\n', function(err){
                if(err) throw err;});
                res.send('Data '+req.query.field1+'ºC has sent!');
                console.log(req.query.field1+' has reached.');
        }
        else res.send('Wrong api!');
});

app.get('/dump', function(req, res) {
        var count = parseInt(req.query.count, 10);

        fs.readFile('temperature.txt','utf8', function(err, temp) {
                if(err) throw err;
                var arr = temp.toString().split('\n');
                var line = arr.length-1;

                if(count<0 || count > line){
                        res.send('[Error] Check your count number!<br>Max data number: '+ line +'</br>');
                        console.log('Error: Wrong count number.');
                }
                else{
                        for(i=0;i<count;i++){
                                res.write('<br>'+arr[i]+'</br>');
                        }
                        res.end();
                }
        });
});


app.listen(8000, () => console.log('Port 8000: listening!'));
