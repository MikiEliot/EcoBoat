const { Acidite } = require('../db/sequelize.js')
const auth = require('../auth/auth.js')

module.exports = (app) => {
    // Je créé le endpoint pour ajouter
    app.post('/api/capteurs/capteur_acidite', auth, (req, res) => {
        // J'utilise la méthode create() de sequelize
        Acidite.create(req.body)
            .then(acidite => {
                const message = `Le relevé ${req.body.name} a été créée`
                res.json({ message, data: acidite })
            })
            .catch(error => {
                const message = ' La température n\'a pas pu être ajoutée.'
                res.status(500).json({ message, data: error })
            })
    })

    // Je créé un endpoint pour supprimer une relevé du capteurs d'acidité
    app.delete('/api/capteurs/capteur_acidite/:id', auth, (req, res) => {
        Acidite.findByPk(req.params.id).then(acidite => {
            if (acidite === null) {
                const message = 'L\'acidité demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            const aciditeDeleted = acidite;
            return Acidite.destroy({
                where: { id: acidite.id }
            })
                .then(_ => {
                    const message = `L\'acidité ${acidite.name} a été supprimée`
                    res.json({ message, data: aciditeDeleted })
                })
        })
            .catch(error => {
                const message = 'L\'acidité n\'a pas pu être supprimée.'
                res.status(500).json({ message, data: error })
            })
    })

    // Je créé un endpoint pour modifier une relevé du capteurs d'acidité
    app.put('/api/capteurs/capteur_acidite/:id', auth, (req, res) => {
        Acidite.findByPk(req.params.id).then(acidite => {
            if (acidite === null) {
                const message = 'L\'acidité demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            acidite.name = req.body.name;
            acidite.value = req.body.value;
            acidite.date = req.body.date;
            acidite.save(acidite.id)
                .then(_ => {
                    const message = `L\'acidité ${acidite.name} a été modifiée`
                    res.json({ message, data: acidite })
                })
        })
            .catch(error => {
                const message = 'L\'acidité n\'a pas pu être modifiée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer un relevé du capteurs d'acidité
    app.get('/api/capteurs/capteur_acidite/:id', auth, (req, res) => {
        Acidite.findByPk(req.params.id)
            .then(acidite => {
                if (acidite === null) {
                    const message = 'L\'acidité demandée n\'éxiste pas.'
                    return res.status(404).json({ message })
                }
                const message = 'L\'acidité a été trouvée.'
                res.json({ message, data: acidite })
            })
            .catch(error => {
                const message = 'L\'acidité n\'a pas pu être récupérée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer toutes les relevés du capteurs d'acidité
    app.get('/api/capteurs/capteur_acidite', auth, (req, res) => {
        Acidite.findAll().then(acidite => {
            const message = 'La liste des relevés d\'acidité a bien été récupérée.'
            res.json({ message, data: acidite })
        })
            .catch(error => {
                const message = 'La liste des relevés d\'acidité n\'a pas pu être récupérée.'
                res.status(500).json({ message, data: error })
            })
    })
}