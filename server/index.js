const express = require('express');
const apiRouter = require('./backend/routes');
const app = express();

app.use('/api', apiRouter);
app.use(express.static('static'));
app.get('*', function(req, res){
    res.sendFile(__dirname + '/static/index.html');
});

app.listen(3000, function () {
    console.log('Server listening on port 3000');
});