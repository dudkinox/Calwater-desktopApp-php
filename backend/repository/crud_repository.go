package repository

import (
	"go.mongodb.org/mongo-driver/mongo"
)

type CrudRepository struct {
	mongoDB *mongo.Database
}

func NewCrudRepository(mongo *mongo.Database) CrudRepositoryI {
	return &CrudRepository{
		mongoDB: mongo,
	}
}
