/* L’API Rest et la Base de données : Créer un modèle Sequelize */
module.exports = (sequelize, DataTypes) => {
    return sequelize.define('capteur_temperature', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        temperature: {
            type: DataTypes.FLOAT,
            allowNull: false
        }
    },
        {
            timestamps: true,
            createdAt: 'created',
            updatedAt: false
        })
}