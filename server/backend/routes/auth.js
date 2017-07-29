const express = require('express');
const passport = require('passport');
const GitHubStrategy = require('passport-github').Strategy;
const User = require('../models/user');
const authRouter = express.Router();

const allowedGithubUsersId =['12786230'];

passport.use(new GitHubStrategy({
	clientID: process.env.GITHUB_CLIENT_ID,
	clientSecret: process.env.GITHUB_SECRET_KEY,
	callbackURL: "http://localhost:3000/api/auth/github/callback"
}, async function (accessToken, refreshToken, profile, cb) {
	if (!allowedGithubUsersId.includes(profile.id)) {
		cb(new Error("User not allowed"), null)
	}
	User.model.findOrCreate({
		where: {githubId: profile.id},
		defaults: {
			githubId: profile.id,
			avatarUrl: profile._json.avatar_url,
			username: profile.username,
		}
	}).spread((model) => {
		cb(null, model.dataValues)
	}).catch((err) => {
		cb(err, null)
	});
}));

authRouter.get('/github', passport.authenticate('github'));

authRouter.get('/github/callback',
	passport.authenticate('github', {failureRedirect: '/auth'}),
	function (req, res) {
		res.redirect('/tasks');
	}
);

authRouter.delete('/', function (req, res) {
	req.session.destroy();
	req.logout();
	res.redirect('/auth');
});

authRouter.get('/', function (req, res) {
	if (req.user) {
		res.status(200).json(req.user);
	} else {
		res.redirect('/auth');
	}
});

passport.serializeUser(function (user, done) {
	try {
		const userJSON = JSON.stringify({
			role: user.role,
			githubId: user.githibId,
			username: user.username,
			avatarUrl: user.avatarUrl,
		});
		done(null, userJSON);
	} catch (err) {
		done(err, null);
	}
});

passport.deserializeUser(function (userJSON, done) {
	try {
		done(null, JSON.parse(userJSON));
	} catch (err) {
		done(err, null)
	}
});

module.exports = authRouter;
