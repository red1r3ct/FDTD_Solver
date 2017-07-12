const express = require('express');

const authRouter = express.Router();

authRouter.get((req, res) => {
    console.log('GET api/auth')
});

module.exports = authRouter;
