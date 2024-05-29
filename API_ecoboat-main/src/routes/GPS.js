// Définition des routes pour la table capteur_GPS
const { GPS } = require('../db/sequelize.js')
// J'importe le middleware d'authentification
const auth = require('../auth/auth.js')
// Je créé le endpoint pour ajouter
module.exports = (app) => {
    // Je créé le endpoint pour ajouter
    app.post('/api/capteurs/capteur_GPS', auth, (req, res) => {
        // J'utilise la méthode create() de sequelize
        GPS.create(req.body)
        // Je retourne le résultat
            .then(gps => {
                const message = `Le relevé ${req.body.id} a été créée`
                res.json({ message, data: gps })
            })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être ajoutée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour supprimer une relevé du capteurs de GPS
    app.delete('/api/capteurs/capteur_GPS/:id', auth, (req, res) => {
        GPS.findByPk(req.params.id).then(gps => {
            if (gps === null) {
                const message = 'Le relevé demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            const gpsDeleted = gps;
            return GPS.destroy({
                where: { id: gps.id }
            })
                .then(_ => {
                    const message = `Le relevé ${gps.id} a été supprimée`
                    res.json({ message, data: gpsDeleted })
                })
        })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être supprimée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour modifier une relevé du capteurs de GPS
    app.put('/api/capteurs/capteur_GPS/:id', auth, (req, res) => {
        GPS.findByPk(req.params.id).then(gps => {
            if (gps === null) {
                const message = 'Le relevé demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            gps.id = req.body.id;
            gps.latitude = req.body.latitude;
            gps.longitude = req.body.longitude;
            gps.date = req.body.date;
            gps.save(gps.id)
                .then(_ => {
                    const message = `Le relevé ${gps.id} a été modifiée`
                    res.json({ message, data: gps })
                })
        })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être modifiée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer un relevé du capteurs de GPS
    app.get('/api/capteurs/capteur_GPS', auth, (req, res) => {
        GPS.findAll().then(gps => {
            res.json(gps)
        })
            .catch(error => {
                const message = 'Les relevés n\'ont pas pu être récupérées.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer les relevés du capteurs de GPS
    app.get('/api/capteurs/capteur_GPS/:id', auth, (req, res) => {
        GPS.findByPk(req.params.id)
            .then(gps => {
                if (gps === null) {
                    const message = 'Le relevé demandée n\'éxiste pas.'
                    return res.status(404).json({ message })
                }
                res.json(gps)
            })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être récupérée.'
                res.status(500).json({ message, data: error })
            })
    })
}

