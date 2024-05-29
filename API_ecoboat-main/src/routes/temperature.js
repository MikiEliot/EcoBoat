const { Temperature } = require('../db/sequelize.js')
const auth = require('../auth/auth.js')

module.exports = (app) => {
    // Je créé le endpoint pour ajouter
    app.post('/api/capteurs/capteur_temperature', auth, (req, res) => {
        // J'utilise la méthode create() de sequelize
        Temperature.create(req.body)
            .then(temperature => {
                const message = `La température ${req.id} a été créée`
                res.json({ message, data: temperature })
            })
            .catch(error => {
                const message = ' La température n\'a pas pu être ajoutée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour supprimer une température
    app.delete('/api/capteurs/capteur_temperature/:id', auth, (req, res) => {
        Temperature.findByPk(req.params.id).then(temperature => {
            if (temperature === null) {
                const message = 'La température demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            const temperatureDeleted = temperature;
            return Temperature.destroy({
                where: { id: temperature.id }
            })
                .then(_ => {
                    const message = `La température ${temperature.name} a été supprimée`
                    res.json({ message, data: temperatureDeleted })
                })
        })
            .catch(error => {
                const message = 'La température n\'a pas pu être supprimée.'
                res.status(500).json({ message, data: error })
            })
    })

    // Je créé un endpoint pour modifier une température
    app.put('/api/capteurs/capteur_temperature/:id', auth, (req, res) => {
        Temperature.findByPk(req.params.id).then(temperature => {
            if (temperature === null) {
                const message = 'La température demandée n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            temperature.value = req.body.value;
            temperature.temperature = req.body.temperature;
            temperature.date = req.body.date;
            temperature.save()
                .then(_ => {
                    const message = `La température ${temperature.value} a été modifiée`
                    res.json({ message, data: temperature })
                })
        })
            .catch(error => {
                const message = 'La température n\'a pas pu être modifiée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer toutes les températures
    app.get('/api/capteurs/capteur_temperature', auth, (req, res) => {
        Temperature.findAll().then(temperature => {
            const message = 'La liste des températures a bien été récupérée.'
            res.json({ message, data: temperature })
        })
            .catch(error => {
                const message = 'La liste des températures n\'a pas pu être récupérée.'
                res.status(500).json({ message, data: error })
            })
    })
    // Je créé un endpoint pour récupérer une température
    app.get('/api/capteurs/capteur_temperature/:id', auth, (req, res) => {
        Temperature.findByPk(req.params.id)
            .then(temperature => {
                if (temperature === null) {
                    const message = 'La température demandée n\'éxiste pas.'
                    return res.status(404).json({ message })
                }
                const message = 'La température a bien été récupérée.'
                res.json({ message, data: temperature })
            })
            .catch(error => {
                const message = 'La température n\'a pas pu être récupérée.'
                res.status(500).json({ message, data: error })
            })
    })
}