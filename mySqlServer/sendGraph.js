mysql = require('mysql');
var connection = mysql.createConnection({
    host: 'localhost',
    user: 'AnnaLe97',
    password: 'password',
    database: 'mydb'
})
connection.connect();


app.get('/graph', function (req, res) {
    var count = 256;
    if(req.query["count"] != null){
        count = parseInt(req.query.count, 10);
    }

    console.log('got app.get(graph)');
    var html = fs.readFile('./graph.html', function (err, html) {
    html = " "+ html
    console.log('read file');

    var qstr = 'select * from sensors ';
    connection.query(qstr, function(err, rows, cols) {
          if (err) throw err;

      var data = "";
      var comma = "";

      if(rows.length < count)
            count = rows.length;
      for (var i=0; i< count; i++) {
         r = rows[i];
         data += comma + "[new Date(2019,10-10,"+ r.id +",00,38),"+ r.value +"]";
         comma = ",";
      }
      var header = "data.addColumn('date', 'Date/Time');"
      header += "data.addColumn('number', 'Temp');"
      html = html.replace("<%HEADER%>", header);
      html = html.replace("<%DATA%>", data);

      res.writeHeader(200, {"Content-Type": "text/html"});
      res.write(html);
      res.end();
    });
  });
});

app.get('/dump', function(req, res){
        var count = 256;
        if(req.query["count"] != null){
                count = parseInt(req.query.count, 10);
        }

        var qstr = 'select * from sensors';
        connection.query(qstr, function(err, rows, cols){
                if(err){
                        throw err;
                        res.send('query error: '+qstr);
                        return;
                }

                var html = "";
                if(rows.length < count) {
                        count = rows.length;
                        html += "Max data num is "+count.toString()+"<br>";
                }
                console.log("Got "+rows.length+"records");
                for(var i=0; i<count; i++){
                        html += JSON.stringify(rows[i]);
                }
                res.send(html);
        });
});



var server = app.listen(8080, function () {
  var host = server.address().address
  var port = server.address().port
  console.log('listening at http://%s:%s', host, port)
});
