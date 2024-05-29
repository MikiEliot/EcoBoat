/* L’API Rest et la Base de données : Créer un modèle Température Sequelize */
const { Sequelize, DataTypes } = require('sequelize')
// Je récupère mes models
const UserModel = require('../models/user.js')
const TemperatureModel = require('../models/capteur_temperature.js')
const AciditeModel = require('../models/capteur_acidite.js')
const MagnetometreModel = require('../models/capteur_magnetometre.js')
const GPSModel = require('../models/GPS.js')
const TrajetModel = require('../models/Trajet.js')
// Je récupère mes données
const Trajets = require('./Trajet_db.js')
const capteurs_temperature = require('./capteur_temperature_db.js')
const capteurs_acidite = require('./capteur_acidite_db.js')
const capteurs_magnetometre = require('./capteur_magnetometre_db.js')
const capteurs_GPS = require('./GPS_db.js')
const bcrypt = require('bcrypt')

const sequelize = new Sequelize('julien', 'julien', 'julien2024', {
    host: 'localhost',
    dialect: 'mariadb',
    dialectOptions: {
        allowPublicKeyRetrieval: true,
        timezone: 'Etc/GMT-2',
    },
    logging: false
})
// Je declare mes models 
const Temperature = TemperatureModel(sequelize, DataTypes)
const Acidite = AciditeModel(sequelize, DataTypes)
const Magnetometre = MagnetometreModel(sequelize, DataTypes)
const GPS = GPSModel(sequelize, DataTypes)
const User = UserModel(sequelize, DataTypes)
const Trajet = TrajetModel(sequelize, DataTypes)

const initDb = () => {
    return sequelize.sync({ force: true }).then(_ => {
        console.log('INIT DB')
        // Je créé des données de temperature
        capteurs_temperature.map(temperature => {
            Temperature.create({
                temperature: temperature.temperature,
            }).then(temperature => console.log(temperature.toJSON()))
        })
        // Je créé des données d'acidité
        capteurs_acidite.map(acidite => {
            Acidite.create({
                pH: acidite.ph,
            }).then(acidite => console.log(acidite.toJSON()))
        })
        // Je créé des données de magnetometre
        capteurs_magnetometre.map(magnetometre => {
            Magnetometre.create({
                x: magnetometre.x,
                y: magnetometre.y,
                z: magnetometre.z,
            }).then(magnetometre => console.log(magnetometre.toJSON()))
        })
        // Je créé des données GPS
        capteurs_GPS.map(gps => {
            GPS.create({
                lat: gps.lat,
                N_S: gps.N_S,
                long: gps.long,
                E_W: gps.E_W,
                alt: gps.alt,
                date: gps.date,
                utcTime: gps.utcTime,
                speed: gps.speed,
                course: gps.course
            }).then(GPS => console.log(GPS.toJSON()))
        })
        // Je créé des données de trajet
        Trajets.map(trajet => {
            Trajet.create({
                trajet: trajet.trajet,
            }).then(trajet => console.log(trajet.toJSON()))
        })

        bcrypt.hash('jurol', 10)
            .then(hash => {
                User.create({
                    username: 'jurol',
                    password: hash
                })
                    .then(user => console.log(user.toJSON()))
            })
        console.log('La base de donnée a bien été initialisée !')
    })
}

module.exports = {
    initDb, Temperature, User, Acidite, Magnetometre, GPS, Trajet
}