package repository

import (
	"backend/model"
	"context"
	"fmt"
	"strings"

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

func (cr CrudRepository) InsertInfoData(ctx context.Context, req model.ModelInfo) (NewId string, err error) {
	datareq := bson.M{
		"Volume":                   req.Volume,
		"Batch_No":                 req.Batch_No,
		"Meet_MOI_Spec":            req.Meet_MOI_Spec,
		"Sump_No":                  req.Sump_No,
		"Treatment_Date":           req.Treatment_Date,
		"Raw_Waste_Water_Analysis": req.Raw_Waste_Water_Analysis,
		"Treat_Water_Analysis":     req.Treat_Water_Analysis,
		"Process_Reagent":          req.Process_Reagent,
	}

	result, err := cr.mongoDB.Collection("wastewaterdata").InsertOne(ctx, datareq)

	NewID := fmt.Sprintf("%v", result.InsertedID)
	formatObject := strings.Split(NewID, "ObjectID(")
	formatNewID := strings.Split(formatObject[1], `"`)

	return formatNewID[1], err
}
