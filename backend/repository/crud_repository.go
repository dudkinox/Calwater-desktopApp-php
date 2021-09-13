package repository

import (
	"backend/model"
	"context"
	"fmt"

	"go.mongodb.org/mongo-driver/bson"
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

func (cr CrudRepository) GetNameData(ctx context.Context) (crudResp model.GetNameResponse, err error) {
	Response := make([]model.ModelSave, 0)
	query, err := cr.mongoDB.Collection("table").Find(ctx, bson.D{})
	fmt.Println(query)
	if err != nil {
		return model.GetNameResponse{}, err
	}
	defer query.Close(ctx)
	for query.Next(ctx) {
		var row model.ModelSave
		err = query.Decode(&row)
		Response = append(Response, row)
	}
	crudResp = model.GetNameResponse{Data: Response}
	return crudResp, err
}
