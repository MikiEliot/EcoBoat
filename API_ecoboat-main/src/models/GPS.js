// L’API Rest et la Base de données : Créer un modèle Sequelize
module.exports = (sequelize, DataTypes) => {
    return sequelize.define('GPS', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        lat: {
            type: DataTypes.FLOAT,
            allowNull: false
        },
        N_S: {
            type: DataTypes.STRING,
            allowNull: false
        },
        long: {
            type: DataTypes.FLOAT,
            allowNull: false
        },
        E_W: {
            type: DataTypes.STRING,
            allowNull: false
        },
        alt: {
            type: DataTypes.FLOAT,
            allowNull: false
        },
        date: {
            type: DataTypes.DATE,
            allowNull: false
        },
        utcTime: {
            type: DataTypes.TIME,
            allowNull: false
        },
        speed: {
            type: DataTypes.FLOAT,
            allowNull: false
        },
        course: {
            type: DataTypes.FLOAT,
            allowNull: false
        }
    })
}