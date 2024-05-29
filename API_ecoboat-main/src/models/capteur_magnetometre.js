// Création du modele sequelize pour la table magnetometre
module.exports = (sequelize, DataTypes) => {
    return sequelize.define('capteur_magnetometre', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        x: {
            type: DataTypes.FLOAT,
            allowNull: false
        },
        y: {
            type: DataTypes.FLOAT,
            allowNull: false
        },
        z: {
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