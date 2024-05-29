// Définition des routes pour la table capteur_magnetometre
const { Magnetometre } = require('../db/sequelize.js')
// J'importe le middleware d'authentification
const auth = require('../auth/auth.js')

// Je créé le endpoint pour ajouter
module.exports = (app) => {
    // Je créé le endpoint pour ajouter
    app.post('/api/capteurs/capteur_magnetometre', auth, (req, res) => {
        // J'utilise la méthode create() de sequelize
        Magnetometre.create(req.body)
        // Je retourne le résultat
            .then(magnetometre => {
                const message = `Le relevé ${req.body.id} a été créée`
                res.json({ message, data: magnetometre })
            })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être ajoutée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour supprimer une relevé du capteurs de magnetometre
    app.delete('/api/capteurs/capteur_magnetometre/:id', auth, (req, res) => {
        Magnetometre.findByPk(req.params.id).then(magnetometre => {
            if (magnetometre === null) {
                const message = 'Le relevé demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            const magnetometreDeleted = magnetometre;
            return Magnetometre.destroy({
                where: { id: magnetometre.id }
            })
                .then(_ => {
                    const message = `Le relevé ${magnetometre.id} a été supprimée`
                    res.json({ message, data: magnetometreDeleted })
                })
        })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être supprimée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour modifier une relevé du capteurs de magnetometre
    app.put('/api/capteurs/capteur_magnetometre/:id', auth, (req, res) => {
        Magnetometre.findByPk(req.params.id).then(magnetometre => {
            if (magnetometre === null) {
                const message = 'Le relevé demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            magnetometre.id = req.body.id;
            magnetometre.x = req.body.x;
            magnetometre.y = req.body.y;
            magnetometre.z = req.body.z;
            magnetometre.date = req.body.date;
            magnetometre.save(magnetometre.id)
                .then(_ => {
                    const message = `Le relevé ${magnetometre.id} a été modifiée`
                    res.json({ message, data: magnetometre })
                })
        })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être modifiée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer un relevé du capteurs de magnetometre
    app.get('/api/capteurs/capteur_magnetometre/:id', auth, (req, res) => {
        Magnetometre.findByPk(req.params.id)
            .then(magnetometre => {
                if (magnetometre === null) {
                    const message = 'Le relevé demandée n\'éxiste pas.'
                    return res.status(404).json({ message })
                }
                const message = `Le relevé ${magnetometre.id} a été trouvé.`
                res.json({ message, data: magnetometre })
            })
            .catch(error => {
                const message = 'Le relevé n\'a pas pu être récupérée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer tous les relevés du capteurs de magnetometre
    app.get('/api/capteurs/capteur_magnetometre', auth, (req, res) => {
        Magnetometre.findAll()
            .then(magnetometre => {
                const message = 'La liste des relevés du capteurs de magnetometre a bien été récupérée.'
                res.json({ message, data: magnetometre })
            })
            .catch(error => {
                const message = 'La liste des relevés du capteurs de magnetometre n\'a pas pu être récupérée.'
                res.status(500).json({ message, data: error })
            })
    })
}