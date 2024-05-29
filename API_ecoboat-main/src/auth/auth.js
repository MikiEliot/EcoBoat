// Middleware de sécurité
const jwt = require('jsonwebtoken')
const privateKey = require('../auth/private_key')

module.exports = (req, res, next) => {
    // Je récupère l'entête car c'est par là que transite le token
    const authorizationHeader = req.headers.authorization
    // Je vérifie sie le jeton a été fourni
    if (!authorizationHeader) {
        const message = `Vous n'avez pas fourni de jeton d'authentification.`
        return res.status(401).json({ message })
    }
    // Je split le nom "bearer" 
    const token = authorizationHeader.split(' ')[1]
    // La méthode verify() vérifie la validité du token
    jwt.verify(token, privateKey, (error, decodedToken) => {

        if (error) {
            const message = `Vous n'êtes pas autorisé à accéder à cette ressource`
            return res.status(401).json({ message, data: error })
        }

        const userId = decodedToken.userId
        if (req.body.userId && req.body.userId !== userId) {
            const message = `L'identifiant est invalide.`
            res.status(401).json({ message })
        } else {
            next()
        }
    })
}