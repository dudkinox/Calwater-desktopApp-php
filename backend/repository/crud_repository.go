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
	fmt.Println(crudResp)
	return crudResp, err
}
func (cr CrudRepository) InfoData(ctx context.Context) (crudResp model.GetInfoResponse, err error) {
	Response := make([]model.ModelInfo, 0)
	query, err := cr.mongoDB.Collection("wastewaterdata").Find(ctx, bson.D{})
	fmt.Println(query)
	if err != nil {
		return model.GetInfoResponse{}, err
	}
	defer query.Close(ctx)
	for query.Next(ctx) {
		var row model.ModelInfo
		err = query.Decode(&row)
		Response = append(Response, row)
	}
	crudResp = model.GetInfoResponse{Data: Response}
	fmt.Println(crudResp)
	return crudResp, err
}
