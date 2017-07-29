const express = require('express');
const apiRouter = require('./backend/routes');
const db = require('./backend/services/db');
const passport = require('passport');

const app = express();

app.use(express.static('static'));
app.use(require('morgan')('combined'));
app.use(require('express-session')({
	secret: process.env.SECRET_SEED,
	resave: true,
	saveUninitialized: true
}));
app.use(passport.initialize());
app.use(passport.session());
app.use('/api', apiRouter);

app.get('*', function (req, res) {
	res.sendFile(__dirname + '/static/index.html');
});

db.init().then(() => {
	app.listen(3000, function () {
		console.log('Server listening on port 3000');
	});
});

