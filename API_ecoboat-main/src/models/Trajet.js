module.exports = (sequelize, DataTypes) => {
    return sequelize.define('Trajet', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        trajet: {
            type: DataTypes.JSON,
            allowNull: false
        }
    })
}