const db = require('../services/db');
const Sequelize = require('sequelize');
const crypto = require('crypto');

const roles = {
	admin: 'ADMIN',
	viewer: 'VIEWER',
	runner: 'RUNNER',
};

const model = db.conn.define('user', {
	githubId: {
		type: Sequelize.INTEGER,
		allowNull: false,
	},
	username: {
		type: Sequelize.STRING,
		allowNull: false,
	},
	avatarUrl: {
		type: Sequelize.STRING,
		allowNull: false,
		defaultValue: '/images/default-avatar.png',
	},
	role: {
		type: Sequelize.STRING,
		allowNull: false,
		defaultValue: roles.admin,
	},
});

model.sync({force: true}).then(() => {
	console.log('Users table synced');
});

module.exports = {
	model,
	roles,
};

