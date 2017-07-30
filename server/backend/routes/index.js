const express = require('express');
const jobsRouter = require('./jobs.js');
const authRouter = require('./auth.js');

const apiRouter = express.Router();

apiRouter.use('/jobs', jobsRouter);
apiRouter.use('/auth', authRouter);

module.exports = apiRouter;