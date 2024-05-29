const { application } = require('express');
const { User } = require('../db/sequelize.js');
const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');
const privateKey = require('../auth/private_key.js');
const auth = require('../auth/auth.js');

module.exports = (app) => {
    // Je créé un endpoint pour la connection
    app.post('/api/login', (req, res) => {
        User.findOne({ where: { username: req.body.username } }).then(user => {
            if (!user) {
                const message = 'Ce nom d\'utilisateur n\'éxiste pas.'
                return res.status(404).json({ message })
            }
            // "compare" méthode qui permet à bcrypt de comparer les mdp
            bcrypt.compare(req.body.password, user.password).then(isPasswordValid => {
                if (!isPasswordValid) {
                    const message = `Le mot de passe est incorrect`;
                    return res.status(401).json({ message })
                }

                // JWT
                const token = jwt.sign(
                    { userId: user.id },
                    privateKey,
                    { expiresIn: '24h' }
                )
                const messsage = 'Vous êtes connecté(e).'
                return res.json({ messsage, data: user, token })
            })
        })
            .catch(error => {
                const message = `La connexion a échouée`
                return res.json({ message, data: error })
            })
    })
}
