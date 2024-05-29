// Init de sequelize
const { Trajet } = require('../db/sequelize.js')
// J'importe le middleware d'authentification
const auth = require('../auth/auth.js')

module.exports = (app) => {
    // J'ajoute un trajet à la base de donnée
    // Je créé le endpoint pour ajouter
    app.post('/api/trajets', auth, (req, res) => {
        // J'utilise la méthode create() de sequelize
        Trajet.create(req.body)
            .then(temperature => {
                const message = `La température ${req.id} a été créée`
                res.json({ message, data: temperature })
            })
            .catch(error => {
                const message = ' La température n\'a pas pu être ajoutée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour supprimer un trajet
    app.delete('/api/trajets/:id', auth, (req, res) => {
        Trajet.findByPk(req.params.id).then(trajet => {
            if (trajet === null) {
                const message = 'Le trajet demandé n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            const trajetDeleted = trajet;
            return Trajet.destroy({
                where: { id: trajet.id }
            })
                .then(_ => {
                    const message = `Le trajet ${trajet.name} a été supprimé`
                    res.json({ message, data: trajetDeleted })
                })
        })
            .catch(error => {
                const message = 'Le trajet n\'a pas pu être supprimé.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour modifier un trajet
    app.put('/api/trajets/:id', auth, (req, res) => {
        Trajet.findByPk(req.params.id).then(trajet => {
            if (trajet === null) {
                const message = 'Le trajet demandé n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            trajet.trajet = req.body.trajet;
            trajet.save()
                .then(_ => {
                    const message = `Le trajet ${trajet.trajet} a été modifié`
                    res.json({ message, data: trajet })
                })
        })
            .catch(error => {
                const message = 'Le trajet n\'a pas pu être modifié.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer tous les trajets
    app.get('/api/trajets', auth, (req, res) => {
        Trajet.findAll().then(trajets => {
            res.json(trajets)
        })
    })
    // Je créé un endpoint pour récupérer un trajet
    app.get('/api/trajets/:id', auth, (req, res) => {
        Trajet.findByPk(req.params.id).then(trajet => {
            if (trajet === null) {
                const message = 'Le trajet demandé n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            res.json(trajet)
        })
    })
}