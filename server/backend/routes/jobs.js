const express = require('express');

const jobsRouter = express.Router();

jobsRouter.get('/', (req, res) => {
    console.log('GET api/jobs');
    res.json([]);
});

module.exports = jobsRouter;
