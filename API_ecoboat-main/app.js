const express = require('express')
const morgan = require('morgan')
const favicon = require('serve-favicon')
const bodyParser = require('body-parser')
const sequelize = require('./src/db/sequelize.js')
const cors = require('cors');

const app = express();
const port = 4000;
const host = "julien.lamy.mobi";

app
    .use(favicon(__dirname + '/favicon.ico'))
    .use(morgan('dev'))
    .use(bodyParser.json())
    .use(cors())

sequelize.initDb()

// je place tous les endpoints ici
require('./src/routes/temperature.js')(app)
require('./src/routes/acidite.js')(app)
require('./src/routes/user.js')(app)
require('./src/routes/magnetometre.js')(app)
require('./src/routes/GPS.js')(app)
require('./src/routes/trajets.js')(app)

// J'ajoute la gestion des erreurs 404
app.use(({ res }) => {
    const message = 'Impossible de trouver la ressource demandée'
    res.status(404).json({ message })
})

app.listen(port, host, () => console.log("Application démarée"));