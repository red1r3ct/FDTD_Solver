const express = require('express');

const jobsRouter = express.Router();

jobsRouter.get('/', (req, res) => {
    res.json([]);
});

module.exports = jobsRouter;
