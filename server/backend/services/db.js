const Sequelize = require('sequelize');
const log = require('winston');

const sequelize = new Sequelize(
	process.env.POSTGRES_DB,
	process.env.POSTGRES_USER,
	process.env.POSTGRES_PASSWORD,
	{
		host: process.env.POSTGRES_URL,
		dialect: 'postgres',

		pool: {
			max: 5,
			min: 0,
			idle: 10000
		},
	}
);

sequelize
	.authenticate()
	.then(() => {
		log.info('Connection has been established successfully.');
	})
	.catch(err => {
		log.info('Unable to connect to the database: ', err);
	});

module.exports =  sequelize;
